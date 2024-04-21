from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='py_pkg',
            executable='spawner',
            parameters=[
                {"spawn_freq": 1.0},
                {"turtle_name_prefix": "my_turtle"}
            ]
        ),
        Node(
            package='py_pkg',
            executable='controller',
            parameters=[
                {"catch_closest_turtle_first": True}
            ]
        ),
        Node(
            package='turtlesim',
            executable='turtlesim_node'
        )
    ])