#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from turtlesim.srv import Spawn, Kill
from turtle_interfaces.msg import Turtle, TurtleArray
from turtle_interfaces.srv import CatchTurtle
import random 
from functools import partial


class SpawnerClientNode(Node):
    def __init__(self):
        super().__init__("spawner_client")

        self.client_spawn_ = self.create_client(Spawn, "spawn")

        while not self.client_spawn_.wait_for_service(timeout_sec=1.0):
                self.get_logger().info('turtle_sim is not up')

        timer_period = 1  # seconds

        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.publisher_alive_ = self.create_publisher(TurtleArray, "alive_turtles", 10)

        self.server_catcher_ = self.create_service(CatchTurtle, "catch", self.callback_catch)

        self.client_kill_ = self.create_client(Kill, "kill")

        self.alive_list = TurtleArray()

    def call_spawn_server(self, x, y):
        req = Spawn.Request()
        req.x = x
        req.y = y
        future = self.client_spawn_.call_async(req)
        future.add_done_callback(partial(self.callback_call_spawn, x=x, y=y))
    
    def callback_call_spawn(self, future, x, y):
        try:
            response = future.result()
            self.get_logger().info(f'new turtle spawned with name{response.name}')
            turtle = Turtle()
            turtle.name = response.name
            turtle.pose_x = x
            turtle.pose_y = y
            self.alive_list.turtle_array.append(turtle)
        except Exception as e:
            self.get_logger().error("Service call failed %r" % (e,))

    def callback_catch(self,request, response):
        self.call_kill_server(request.name)
        return response

    def call_kill_server(self, name):
        req = Kill.Request()
        req.name = name
        future = self.client_kill_.call_async(req)
        future.add_done_callback(partial(self.callback_call_kill, name=name))
    
    def callback_call_kill(self, future, name):
        try:
            self.get_logger().info(f'turtle killed with name: {name}') 
            for turtle in self.alive_list.turtle_array:
                if turtle.name == name:
                    self.alive_list.turtle_array.remove(turtle)
                    break
        except Exception as e:
            self.get_logger().error("Service call failed %r" % (e,))
    
    def timer_callback(self):
        x = float(random.randint(1,10))
        y = float(random.randint(1,10))
        self.call_spawn_server(x,y)
        self.publisher_alive_.publish(self.alive_list)

def main(args=None):
    rclpy.init(args=args)
    node = SpawnerClientNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()