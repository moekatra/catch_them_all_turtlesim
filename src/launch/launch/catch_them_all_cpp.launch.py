from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cpp_pkg',
            executable='spawner',
            parameters=[
                {"spawn_freq": 1.5},
                {"turtle_name_prefix": "my_turtle"}
            ]
        ),
        Node(
            package='cpp_pkg',
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