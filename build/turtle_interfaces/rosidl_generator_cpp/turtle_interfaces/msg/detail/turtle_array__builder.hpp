// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from turtle_interfaces:msg/TurtleArray.idl
// generated code does not contain a copyright notice

#ifndef TURTLE_INTERFACES__MSG__DETAIL__TURTLE_ARRAY__BUILDER_HPP_
#define TURTLE_INTERFACES__MSG__DETAIL__TURTLE_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "turtle_interfaces/msg/detail/turtle_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace turtle_interfaces
{

namespace msg
{

namespace builder
{

class Init_TurtleArray_turtle_array
{
public:
  Init_TurtleArray_turtle_array()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::turtle_interfaces::msg::TurtleArray turtle_array(::turtle_interfaces::msg::TurtleArray::_turtle_array_type arg)
  {
    msg_.turtle_array = std::move(arg);
    return std::move(msg_);
  }

private:
  ::turtle_interfaces::msg::TurtleArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::turtle_interfaces::msg::TurtleArray>()
{
  return turtle_interfaces::msg::builder::Init_TurtleArray_turtle_array();
}

}  // namespace turtle_interfaces

#endif  // TURTLE_INTERFACES__MSG__DETAIL__TURTLE_ARRAY__BUILDER_HPP_
