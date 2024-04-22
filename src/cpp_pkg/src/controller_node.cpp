#include "rclcpp/rclcpp.hpp"
#include <cmath>
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtle_interfaces/msg/turtle.hpp"
#include "turtle_interfaces/msg/turtle_array.hpp"
#include "turtle_interfaces/srv/catch_turtle.hpp"

class ControllerNode : public rclcpp::Node
{
public:
    ControllerNode() : Node("turtle_controller"), name_("turtle1"), turtlesim_up_(false)
    {
        this->declare_parameter("catch_closest_turtle_first", true);
        catch_closest_turtle_first_ = this->get_parameter("catch_closest_turtle_first").as_bool();

        cmd_vel_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(name_ + "/cmd_vel", 10);
        
        pose_subscriber_ = this->create_subscription<turtlesim::msg::Pose>(name_ + "/pose", 10, std::bind(&ControllerNode::callbackPose, this, std::placeholders::_1));
        
        turtles_to_catch_subscriber_ = this->create_subscription<turtle_interfaces::msg::TurtleArray>("alive_turtles", 10, std::bind(&ControllerNode::callbackTurtlesToCatch, this, std::placeholders::_1));

        control_loop_timer_ = this->create_wall_timer(std::chrono::milliseconds(10), std::bind(&ControllerNode::controlLoop, this));
    }

private:
    void callbackPose(const turtlesim::msg::Pose::SharedPtr pose)
    {
        pose_ = *pose.get();
        turtlesim_up_ = true;
    }

    double getDistanceFromCurrentPose(turtle_interfaces::msg::Turtle turtle)
    {
        double dist_x = turtle.x - pose_.x;
        double dist_y = turtle.y - pose_.y;
        return std::sqrt(dist_x * dist_x + dist_y * dist_y);
    }

    void callbackTurtlesToCatch(const turtle_interfaces::msg::TurtleArray::SharedPtr msg)
    {
        if (!msg->turtle_array.empty())
        {
            if (catch_closest_turtle_first_)
            {
                turtle_interfaces::msg::Turtle closest_turtle = msg->turtle_array.at(0);
                double closest_turtle_distance = getDistanceFromCurrentPose(closest_turtle);

                for (int i = 1; i < (int)msg->turtle_array.size(); i++)
                {
                    double distance = getDistanceFromCurrentPose(msg->turtle_array.at(i));
                    if (distance < closest_turtle_distance)
                    {
                        closest_turtle = msg->turtle_array.at(i);
                        closest_turtle_distance = distance;
                    }
                }

                turtle_to_catch_ = closest_turtle;
            }
            else
            {
                turtle_to_catch_ = msg->turtle_array.at(0);
            }
        }
    }

    void publishCmdVel(double x, double theta)
    {
        auto msg = geometry_msgs::msg::Twist();
        msg.linear.x = x;
        msg.angular.z = theta;
        cmd_vel_publisher_->publish(msg);
    }

    void controlLoop()
    {
        if (!turtlesim_up_ || turtle_to_catch_.name == "")
        {
            return;
        }

        double dist_x = turtle_to_catch_.x - pose_.x;
        double dist_y = turtle_to_catch_.y - pose_.y;
        double distance = std::sqrt(dist_x * dist_x + dist_y * dist_y);

        auto msg = geometry_msgs::msg::Twist();

        if (distance > 0.5)
        {
            // position
            msg.linear.x = 2 * distance;

            // orientation
            double steering_angle = std::atan2(dist_y, dist_x);
            double angle_diff = steering_angle - pose_.theta;
            if (angle_diff > M_PI)
            {
                angle_diff -= 2 * M_PI;
            }
            else if (angle_diff < -M_PI)
            {
                angle_diff += 2 * M_PI;
            }
            msg.angular.z = 6 * angle_diff;
        }
        else
        {
            // target reached!
            msg.linear.x = 0.0;
            msg.angular.z = 0.0;

            catch_turtle_threads.push_back(
                std::make_shared<std::thread>(
                    std::bind(&ControllerNode::callCatchTurtleService, this, turtle_to_catch_.name)));
            turtle_to_catch_.name = "";
        }

        cmd_vel_publisher_->publish(msg);
    }

    void callCatchTurtleService(std::string turtle_name)
    {
        auto client = this->create_client<turtle_interfaces::srv::CatchTurtle>("catch_turtle");
        while (!client->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for Service Server to be up...");
        }

        auto request = std::make_shared<turtle_interfaces::srv::CatchTurtle::Request>();
        request->name = turtle_name;

        auto future = client->async_send_request(request);

        try
        {
            auto response = future.get();
            if (!response->success)
            {
                RCLCPP_ERROR(this->get_logger(), "Failed to catch turtle");
            }
        }
        catch (const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Service call failed.");
        }
    }

    std::string name_;
    turtlesim::msg::Pose pose_;
    bool turtlesim_up_;
    bool catch_closest_turtle_first_;
    turtle_interfaces::msg::Turtle turtle_to_catch_;

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscriber_;
    rclcpp::Subscription<turtle_interfaces::msg::TurtleArray>::SharedPtr turtles_to_catch_subscriber_;
    rclcpp::TimerBase::SharedPtr control_loop_timer_;

    std::vector<std::shared_ptr<std::thread>> catch_turtle_threads;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ControllerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}