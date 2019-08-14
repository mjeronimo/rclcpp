// Copyright 2019 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RCLCPP_PARAMETER_BLACKBOARD__PARAMETER_BLACKBOARD_HPP__
#define RCLCPP_PARAMETER_BLACKBOARD__PARAMETER_BLACKBOARD_HPP__

#include "rclcpp/rclcpp.hpp"

namespace rclcpp_parameter_blackboard
{

class ParameterBlackboard : public rclcpp::Node
{
public:
  explicit ParameterBlackboard(
    const rclcpp::NodeOptions & options = (
      rclcpp::NodeOptions()
      .allow_undeclared_parameters(true)
      .automatically_declare_parameters_from_overrides(true)
  ));

protected:
  rclcpp::NodeOptions apply_additional_node_options(const rclcpp::NodeOptions & options)
  {
  // Copy node_options
  auto blackboard_options = rclcpp::NodeOptions(options);

  // Overwrite options for parameter blackboard
  blackboard_options.allow_undeclared_parameters(true);
  blackboard_options.automatically_declare_parameters_from_overrides(true);

  return blackboard_options;    
  }

  bool read_only_;
  rcl_interfaces::msg::SetParametersResult read_only_callback(
    std::vector<rclcpp::Parameter> parameters);
};

}  // namespace rclcpp_parameter_blackboard

#endif  // RCLCPP_PARAMETER_BLACKBOARD__PARAMETER_BLACKBOARD_HPP__
