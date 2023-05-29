#include <rclcpp/rclcpp.hpp>

#include <abb_rws_client/rws_service_provider_ros.hpp>
#include <abb_rws_client/rws_state_publisher_ros.hpp>


// #include <abb_rws_client/rws_service_provider_ros.hpp>

#include <abb_robot_msgs/msg/service_responses.hpp>

#include <abb_rws_client/mapping.hpp>
#include <abb_hardware_interface/utilities.hpp>

using RAPIDSymbols = abb::rws::RWSStateMachineInterface::ResourceIdentifiers::RAPID::Symbols;

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);

  rclcpp::Node::SharedPtr client_node = rclcpp::Node::make_shared("rws");

  client_node->declare_parameter("robot_nickname", std::string{});
  client_node->declare_parameter("no_connection_timeout", false);
  std::string robot_ip = client_node->declare_parameter<std::string>("robot_ip", "172.27.188.31");
  int robot_port = client_node->declare_parameter<int>("robot_port", 80);

  client_node->get_parameter<std::string>("robot_ip", robot_ip);
  client_node->get_parameter<int>("robot_port", robot_port);

  abb_rws_client::RWSServiceProviderROS srv_provider(client_node, robot_ip, robot_port);
  abb_rws_client::RWSStatePublisherROS state_publisher(client_node, robot_ip, robot_port);

  rclcpp::executors::MultiThreadedExecutor exec;
  exec.add_node(client_node);

  exec.spin();

  return 0;
}
