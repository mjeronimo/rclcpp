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

#include "rclcpp_parameter_blackboard/parameter_blackboard.hpp"

#include <memory>
#include <string>

#include "rcl_interfaces/srv/list_parameters.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"

namespace rclcpp_parameter_blackboard
{

ParameterBlackboard::ParameterBlackboard(
  const rclcpp::NodeOptions & options)
: Node("parameter_blackboard", apply_additional_node_options(options))
{
  RCLCPP_INFO(this->get_logger(),
    "Parameter blackboard node named '%s' ready, and serving '%zu' parameters already!",
    this->get_fully_qualified_name(), this->list_parameters(
      {}, rcl_interfaces::srv::ListParameters::Request::DEPTH_RECURSIVE).names.size());
  
  // Optional parameter to make parameter blackboard read-only
  get_parameter_or("read_only", read_only_, false);
  
  set_on_parameters_set_callback(
    std::bind(&ParameterBlackboard::read_only_callback, this, std::placeholders::_1));
}

rcl_interfaces::msg::SetParametersResult ParameterBlackboard::read_only_callback(
  std::vector<rclcpp::Parameter> /* parameters */)
{
  auto result = rcl_interfaces::msg::SetParametersResult();
  result.successful = true;

  if (read_only_) {
    result.successful = false;
    result.reason = "Parameter blackboard is read-only";
  }

  return result;
}

}  // namespace rclcpp_parameter_blackboard

RCLCPP_COMPONENTS_REGISTER_NODE(rclcpp_parameter_blackboard::ParameterBlackboard)
