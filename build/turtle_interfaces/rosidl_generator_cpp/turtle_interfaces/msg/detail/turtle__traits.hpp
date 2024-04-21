// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from turtle_interfaces:msg/Turtle.idl
// generated code does not contain a copyright notice

#ifndef TURTLE_INTERFACES__MSG__DETAIL__TURTLE__TRAITS_HPP_
#define TURTLE_INTERFACES__MSG__DETAIL__TURTLE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "turtle_interfaces/msg/detail/turtle__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace turtle_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Turtle & msg,
  std::ostream & out)
{
  out << "{";
  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: pose_x
  {
    out << "pose_x: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_x, out);
    out << ", ";
  }

  // member: pose_y
  {
    out << "pose_y: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_y, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Turtle & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }

  // member: pose_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_x: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_x, out);
    out << "\n";
  }

  // member: pose_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_y: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_y, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Turtle & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace turtle_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use turtle_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const turtle_interfaces::msg::Turtle & msg,
  std::ostream & out, size_t indentation = 0)
{
  turtle_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use turtle_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const turtle_interfaces::msg::Turtle & msg)
{
  return turtle_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<turtle_interfaces::msg::Turtle>()
{
  return "turtle_interfaces::msg::Turtle";
}

template<>
inline const char * name<turtle_interfaces::msg::Turtle>()
{
  return "turtle_interfaces/msg/Turtle";
}

template<>
struct has_fixed_size<turtle_interfaces::msg::Turtle>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<turtle_interfaces::msg::Turtle>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<turtle_interfaces::msg::Turtle>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TURTLE_INTERFACES__MSG__DETAIL__TURTLE__TRAITS_HPP_
