# Catch Them All - TurtleSim

## Overview
This project is part of a ROS2 course for beginners offered on Udemy. The objective is of the project utilizing the Turtlesim package to simulate a scenario where a main turtle catches other randomly spawned turtles. Three custom nodes will be created: turtle_spawner for turtle management, turtle_controller for controlling the main turtle using a P controller, and leveraging the existing turtlesim_node.

## Packages
The project workspace contains the following packages:

- **py_pkg**
  - Contains Python scripts for spawning turtles (`spawner`) and controlling the main turtle (`controller`).

- **cpp_pkg**
  - Contains C++ executables for spawning turtles (`spawner`) and controlling the main turtle (`controller`).

- **turtle_interfaces**
  - Custom ROS2 message and service definitions.

- **launch**
  - Launch files (`catch_them_all.launch.py`) or (`catch_them_all_cpp.launch.py`) for starting and configuring the ROS2 nodes.


## Usage

### Python Packages

1. **To Launch All Three Nodes**
   ```bash
   ros2 launch launch catch_them_all.launch.py
2. **Run Turtlesim**
   ```bash
   ros2 run turtlesim turtlesim_node
3. **To Spawn Turtles**
   ```bash
   ros2 run py_pkg spawner
4. **To Run Turtle Controller**
   ```bash
   ros2 run py_pkg controller
### CPP Packages

1. **To Launch All Three Nodes**
   ```bash
   ros2 launch launch catch_them_all_cpp.launch.py
2. **Run Turtlesim**
   ```bash
   ros2 run turtlesim turtlesim_node
3. **To Spawn Turtles**
   ```bash
   ros2 run cpp_pkg spawner
4. **To Run Turtle Controller**
   ```bash
   ros2 run cpp_pkg controller
## Parameters for `/controller`

- **`catch_closest_turtle_first`**
  - Description: Determines whether the turtle controller should prioritize catching the closest turtle first.
  - Type: Boolean (true/false)
  - Default Value: true

## Parameters for `/spawner`

- **`spawn_frequency`**
  - Description: Specifies the frequency (in Hz) at which new turtles are spawned.
  - Type: Float
  - Default Value: 1.0

- **`turtle_name_prefix`**
  - Description: Prefix to be used for naming newly spawned turtles.
  - Type: String
  - Default Value: "turtle"

