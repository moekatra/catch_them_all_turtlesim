#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from turtlesim.srv import Spawn, Kill
from turtle_interfaces.msg import Turtle, TurtleArray
from turtle_interfaces.srv import CatchTurtle
import random 
import math
from functools import partial


class SpawnerClientNode(Node):
    def __init__(self):
        super().__init__("spawner_client")

        self.turtle_name_prefix_ = "turtle"
        self.turtle_counter_ = 0
        self.spawn_turtle_timer_ = self.create_timer(2.0, self.spawn_new_turtle)

        # self.client_spawn_ = self.create_client(Spawn, "spawn")

        # while not self.client_spawn_.wait_for_service(timeout_sec=1.0):
        #         self.get_logger().info('turtle_sim is not up')

        # timer_period = 1  # seconds

        # self.timer = self.create_timer(timer_period, self.timer_callback)

        # self.publisher_alive_ = self.create_publisher(TurtleArray, "alive_turtles", 10)

        # self.server_catcher_ = self.create_service(CatchTurtle, "catch", self.callback_catch)

        # self.client_kill_ = self.create_client(Kill, "kill")

        # self.alive_list = TurtleArray()

    def spawn_new_turtle(self):
        self.turtle_counter_ += 1
        name = self.turtle_name_prefix_ + str(self.turtle_counter_)
        x = random.uniform(0.0, 10.0)
        y = random.uniform(0.0, 10.0)
        theta =random.uniform(0.0, 2*math.pi)
        self.call_spawn_server(name, x, y, theta)

    def call_spawn_server(self, turtle_name, x, y, theta):
        client = self.create_client(Spawn, "spawn")
        while not client.wait_for_service(1.0):
                self.get_logger().info('turtle_sim is not up')
        req = Spawn.Request()
        req.x = x
        req.y = y
        req.theta = theta
        req.name = turtle_name
        future = client.call_async(req)
        future.add_done_callback(partial(self.callback_call_spawn, turtle_name=turtle_name, x=x, y=y, theta=theta))
    
    def callback_call_spawn(self, future, turtle_name, x, y, theta):
        try:
            response = future.result()
            if response.name != "":
                self.get_logger().info(f'new turtle spawned with name: {response.name}')
        except Exception as e:
            self.get_logger().error("Service call failed %r" % (e,))

    # def callback_catch(self,request, response):
    #     self.call_kill_server(request.name)
    #     return response

    # def call_kill_server(self, name):
    #     req = Kill.Request()
    #     req.name = name
    #     future = self.client_kill_.call_async(req)
    #     future.add_done_callback(partial(self.callback_call_kill, name=name))
    
    # def callback_call_kill(self, future, name):
    #     try:
    #         self.get_logger().info(f'turtle killed with name: {name}') 
    #         for turtle in self.alive_list.turtle_array:
    #             if turtle.name == name:
    #                 self.alive_list.turtle_array.remove(turtle)
    #                 break
    #     except Exception as e:
    #         self.get_logger().error("Service call failed %r" % (e,))
    
    # def timer_callback(self):
    #     x = float(random.randint(1,10))
    #     y = float(random.randint(1,10))
    #     self.call_spawn_server(x,y)
    #     self.publisher_alive_.publish(self.alive_list)

def main(args=None):
    rclpy.init(args=args)
    node = SpawnerClientNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()