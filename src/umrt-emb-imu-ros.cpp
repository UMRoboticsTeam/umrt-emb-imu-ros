//
// Created by Toni Odujinrin 02/08/2025
//

#include <rclcpp/rclcpp.hpp>

#include "umrt-emb-imu-ros/imu_node.hpp"

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImuNode>());
    rclcpp::shutdown();
    return 0;
}