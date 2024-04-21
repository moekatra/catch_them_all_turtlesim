// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from turtle_interfaces:msg/Turtle.idl
// generated code does not contain a copyright notice

#ifndef TURTLE_INTERFACES__MSG__DETAIL__TURTLE__BUILDER_HPP_
#define TURTLE_INTERFACES__MSG__DETAIL__TURTLE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "turtle_interfaces/msg/detail/turtle__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace turtle_interfaces
{

namespace msg
{

namespace builder
{

class Init_Turtle_pose_y
{
public:
  explicit Init_Turtle_pose_y(::turtle_interfaces::msg::Turtle & msg)
  : msg_(msg)
  {}
  ::turtle_interfaces::msg::Turtle pose_y(::turtle_interfaces::msg::Turtle::_pose_y_type arg)
  {
    msg_.pose_y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::turtle_interfaces::msg::Turtle msg_;
};

class Init_Turtle_pose_x
{
public:
  explicit Init_Turtle_pose_x(::turtle_interfaces::msg::Turtle & msg)
  : msg_(msg)
  {}
  Init_Turtle_pose_y pose_x(::turtle_interfaces::msg::Turtle::_pose_x_type arg)
  {
    msg_.pose_x = std::move(arg);
    return Init_Turtle_pose_y(msg_);
  }

private:
  ::turtle_interfaces::msg::Turtle msg_;
};

class Init_Turtle_name
{
public:
  Init_Turtle_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Turtle_pose_x name(::turtle_interfaces::msg::Turtle::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_Turtle_pose_x(msg_);
  }

private:
  ::turtle_interfaces::msg::Turtle msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::turtle_interfaces::msg::Turtle>()
{
  return turtle_interfaces::msg::builder::Init_Turtle_name();
}

}  // namespace turtle_interfaces

#endif  // TURTLE_INTERFACES__MSG__DETAIL__TURTLE__BUILDER_HPP_
