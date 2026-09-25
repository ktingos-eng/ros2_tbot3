#ifndef SIMULATION_SUPERVISOR_HPP
#define SIMULATION_SUPERVISOR_HPP

#include <rclcpp/rclcpp.hpp>
#include <rclcpp/macros.hpp>
#include "webots_ros2_driver/PluginInterface.hpp"
#include "webots_ros2_driver/WebotsNode.hpp"
#include "webots_ros2_driver/WebotsNode.hpp"
#include "tbot3_interfaces/srv/reset_simulation.hpp"

namespace sim_super {

class SimSupervisor : public webots_ros2_driver::PluginInterface {
    public:
        void step() override;
        void init(
            webots_ros2_driver::WebotsNode *node,
            std::unordered_map<std::string, std::string> &parameters
        ) override;

    private:
        void reset_callback(
            const std::shared_ptr<tbot3_interfaces::srv::ResetSimulation_Request> req,
            std::shared_ptr<tbot3_interfaces::srv::ResetSimulation::Response> resp
        );

        WbNodeRef wb_node_;
        webots_ros2_driver::WebotsNode* node_;
        rclcpp::Service<tbot3_interfaces::srv::ResetSimulation>::SharedPtr reset_service;
};

}

#endif