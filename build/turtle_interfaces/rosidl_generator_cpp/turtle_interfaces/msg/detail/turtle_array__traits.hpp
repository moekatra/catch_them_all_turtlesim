// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from turtle_interfaces:msg/TurtleArray.idl
// generated code does not contain a copyright notice

#ifndef TURTLE_INTERFACES__MSG__DETAIL__TURTLE_ARRAY__TRAITS_HPP_
#define TURTLE_INTERFACES__MSG__DETAIL__TURTLE_ARRAY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "turtle_interfaces/msg/detail/turtle_array__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'turtle_array'
#include "turtle_interfaces/msg/detail/turtle__traits.hpp"

namespace turtle_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TurtleArray & msg,
  std::ostream & out)
{
  out << "{";
  // member: turtle_array
  {
    if (msg.turtle_array.size() == 0) {
      out << "turtle_array: []";
    } else {
      out << "turtle_array: [";
      size_t pending_items = msg.turtle_array.size();
      for (auto item : msg.turtle_array) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TurtleArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: turtle_array
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.turtle_array.size() == 0) {
      out << "turtle_array: []\n";
    } else {
      out << "turtle_array:\n";
      for (auto item : msg.turtle_array) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TurtleArray & msg, bool use_flow_style = false)
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
  const turtle_interfaces::msg::TurtleArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  turtle_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use turtle_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const turtle_interfaces::msg::TurtleArray & msg)
{
  return turtle_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<turtle_interfaces::msg::TurtleArray>()
{
  return "turtle_interfaces::msg::TurtleArray";
}

template<>
inline const char * name<turtle_interfaces::msg::TurtleArray>()
{
  return "turtle_interfaces/msg/TurtleArray";
}

template<>
struct has_fixed_size<turtle_interfaces::msg::TurtleArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<turtle_interfaces::msg::TurtleArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<turtle_interfaces::msg::TurtleArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TURTLE_INTERFACES__MSG__DETAIL__TURTLE_ARRAY__TRAITS_HPP_
