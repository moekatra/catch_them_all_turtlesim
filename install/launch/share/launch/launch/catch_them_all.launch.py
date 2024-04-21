from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='py_pkg',
            executable='spawner'
        ),
        Node(
            package='py_pkg',
            executable='controller'
        ),
        Node(
            package='turtlesim',
            executable='turtlesim_node'
        )
    ])