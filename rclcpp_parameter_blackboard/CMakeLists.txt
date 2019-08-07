cmake_minimum_required(VERSION 3.5)

project(rclcpp_parameter_blackboard)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(ament_cmake REQUIRED)
find_package(rcl_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)

include_directories(include)

function(add_dependencies library)
  ament_target_dependencies(${library}
    "rcl_interfaces"
    "rclcpp"
    "rclcpp_components")
endfunction()

add_library(parameter_blackboard_library SHARED
  src/parameter_blackboard.cpp)

add_dependencies(parameter_blackboard_library)

rclcpp_components_register_node(parameter_blackboard_library
  PLUGIN "rclcpp_parameter_blackboard::ParameterBlackboard"
  EXECUTABLE parameter_blackboard)

install(TARGETS
  parameter_blackboard_library
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_pytest REQUIRED)

endif()

ament_package()
