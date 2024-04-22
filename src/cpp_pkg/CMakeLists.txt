cmake_minimum_required(VERSION 3.8)
project(cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(turtle_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(spawner src/spawner_node.cpp)
ament_target_dependencies(spawner rclcpp turtlesim turtle_interfaces)

add_executable(controller src/controller_node.cpp)
ament_target_dependencies(controller rclcpp turtlesim turtle_interfaces geometry_msgs)


install(TARGETS
  spawner
  controller
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
