#include "tbot3_supervisor/simulation_supervisor.hpp"
#include <webots/supervisor.h>

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(sim_super::SimSupervisor, webots_ros2_driver::PluginInterface);

using namespace sim_super;

void SimSupervisor::reset_callback(
        const std::shared_ptr<tbot3_interfaces::srv::ResetSimulation_Request> req,
        std::shared_ptr<tbot3_interfaces::srv::ResetSimulation::Response> resp
) {
    wb_supervisor_simulation_reset();
}

void SimSupervisor::init(
    webots_ros2_driver::WebotsNode *node,
    std::unordered_map<std::string, std::string> &parameters
) {
    this->node_ = node;
    this->wb_node_ = wb_supervisor_node_get_self();

    RCLCPP_INFO(
        this->node_->get_logger(),
        "Initializing SimulationSupervisor plugin"
    );

    reset_service = this->node_->create_service<tbot3_interfaces::srv::ResetSimulation>(
        "SimulationSupervisor/reset_simulation",
        std::bind(&SimSupervisor::reset_callback, this, 
            std::placeholders::_1,
            std::placeholders::_2
        )
    );

    RCLCPP_INFO(
        this->node_->get_logger(),
        "ResetSimulation service created"
    );
}

void SimSupervisor::step(){

}