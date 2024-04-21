#!/usr/bin/env python3
from functools import partial
import random 
import math
import rclpy
from rclpy.node import Node

from turtlesim.srv import Spawn, Kill
from turtle_interfaces.msg import Turtle, TurtleArray
from turtle_interfaces.srv import CatchTurtle


class SpawnerClientNode(Node):
    def __init__(self):
        super().__init__("spawner_client")
        self.declare_parameter("spawn_freq", 0.5)
        self.declare_parameter("turtle_name_prefix", "turtle")

        self.spawn_freq = self.get_parameter("spawn_freq").value
        self.turtle_name_prefix_ = self.get_parameter("turtle_name_prefix").value
        self.turtle_counter_ = 0
        self.alive_turtles_ = []
        self.alive_turtles_publisher_ = self.create_publisher(TurtleArray, "alive_turtles", 10)
        self.spawn_turtle_timer_ = self.create_timer(1.0/self.spawn_freq, self.spawn_new_turtle)
        self.server_catcher_ = self.create_service(CatchTurtle, "catch_turtle", self.callback_catch_turtle)

    def callback_catch_turtle(self, request, response):
        self.call_kill_server(request.name)
        response.success = True
        return response 
    
    def publish_alive_turtles(self):
        msg = TurtleArray()
        msg.turtle_array = self.alive_turtles_
        self.alive_turtles_publisher_.publish(msg)

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
                new_turtle = Turtle()
                new_turtle.name = response.name
                new_turtle.x = x
                new_turtle.y = y
                new_turtle.theta = theta
                self.alive_turtles_.append(new_turtle)
                self.publish_alive_turtles()
        except Exception as e:
            self.get_logger().error("Service call failed %r" % (e,))

    def call_kill_server(self, turtle_name):
        client = self.create_client(Kill, "kill")
        while not client.wait_for_service(1.0):
                self.get_logger().info('Waiting for server ...')
        req = Kill.Request()
        req.name = turtle_name
        future = client.call_async(req)
        future.add_done_callback(partial(self.callback_call_kill, turtle_name=turtle_name))
    
    def callback_call_kill(self, future, turtle_name):
        try:
            future.result()
            for (i, turtle) in enumerate(self.alive_turtles_):
                if turtle.name == turtle_name:
                    del self.alive_turtles_[i]
                    self.publish_alive_turtles()
                    break
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