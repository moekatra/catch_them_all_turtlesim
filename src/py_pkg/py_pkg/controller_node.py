#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist
from turtle_interfaces.msg import Turtle, TurtleArray
from turtle_interfaces.srv import CatchTurtle
import math
from functools import partial

class HunterNode(Node):
    def __init__(self):
        super().__init__("hunter")

        #Subscribtions
        self.hunter_pose_ = self.create_subscription(Pose, "turtle1/pose", self.hunter_pose_callback, 10)
        self.alive_list_ = self.create_subscription(TurtleArray, "alive_turtles", self.alive_turtles_callback, 10)

        #Publishers
        self.hunter_hunt_ = self.create_publisher(Twist, "turtle1/cmd_vel", 10)
        self.timer_ = self.create_timer(0.01, self.pid_callback)

        #Clients
        self.client_catcher_ = self.create_client(CatchTurtle, "catch")

        self.desired_turtle = None

    def hunter_pose_callback(self, msg):
        self.hunter_x = msg.x
        self.hunter_y = msg.y
        self.hunter_theta = msg.theta
        self.get_logger().info(f"current pose of the hunter x={self.hunter_x}, y={self.hunter_y}, theta={self.hunter_theta}")

    def alive_turtles_callback(self, msg):
        if self.desired_turtle is None:
            return 
        self.desired_turtle = msg.turtle_array[0].name
        self.desired_pose_x = msg.turtle_array[0].pose_x
        self.desired_pose_y = msg.turtle_array[0].pose_y
        self.get_logger().info(f"recieved list of alive turtles, choosing first in the list x={self.desired_pose_x}, y={self.desired_pose_y}")

    def pid_callback(self):
        if self.desired_turtle is None:
            return 
        self.get_logger().info(f"Current x={self.hunter_x} current y={self.hunter_y} and current angle = {self.hunter_theta}")
        self.get_logger().info(f"Current x={self.desired_pose_x} current y={self.desired_pose_y}")
        # Calculate errors in position
        err_x = self.desired_pose_x - self.hunter_x
        err_y = self.desired_pose_y - self.hunter_y
        err_dist = (err_x**2+err_y**2)**0.5
        
        # Distance error (magnitude of the error vector)
        
        self.get_logger().info(f"Error in x {err_x} and error in y {err_y}")

        # Desired heading based on the position error
        desired_theta = math.atan2(err_y, err_x)
        
        # Error in heading
        err_theta = desired_theta - self.hunter_theta
       
        # Handle wrap-around issues (e.g., if error jumps from +pi to -pi)
        while err_theta > math.pi:
            err_theta -= 2.0 * math.pi
        while err_theta < -math.pi:
            err_theta += 2.0 * math.pi
        self.get_logger().info(f"Desired Angle = {desired_theta} current angle {self.hunter_theta} Error angle {err_theta}")
        # P (ID not required) for linear velocity (distance control)

        Kp_dist = 2
            


        # P (ID not required) constants for angular velocity (heading control)
        Kp_theta = 6
        

        # TODO: Add integral and derivative calculations for complete PID

        # PID control for linear velocity
        #l_v = Kp_dist * abs(err_x) # + Ki_dist * integral_dist + Kd_dist * derivative_dist
        l_v = Kp_dist * abs(err_dist) # + Ki_dist * integral_dist + Kd_dist * derivative_dist


        # PID control for angular velocity
        a_v = Kp_theta * err_theta  

        # Send the velocities
        self.my_velocity_cont(l_v, a_v)

    def my_velocity_cont(self, l_v, a_v):
        self.get_logger().info(f"Commanding liner ={l_v} and angular ={a_v}")
        my_msg = Twist()
        my_msg.linear.x = l_v
        my_msg.angular.z = a_v
        self.hunter_hunt_.publish(my_msg)
        err_x = self.desired_pose_x - self.hunter_x
        err_y = self.desired_pose_y - self.hunter_y
        if err_x < 0.5 and err_y < 0.5:
            self.call_catch_server(self.desired_turtle)

    def call_catch_server(self, name):
        req = CatchTurtle.Request()
        req.name = name
        future = self.client_catcher_.call_async(req)
        future.add_done_callback(partial(self.callback_call_catch, name=name))
    
    def callback_call_catch(self, future, name):
        try:
            response = future.result()
            self.get_logger().info(f'caught turtle with name: {name}')
        except Exception as e:
            self.get_logger().error("Service call failed %r" % (e,))


def main(args=None):
    rclpy.init(args=args)
    node = HunterNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()