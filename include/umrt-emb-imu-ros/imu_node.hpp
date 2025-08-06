#ifndef UMRT_IMU_NODE_HPP
#define UMRT_IMU_NODE_HPP

#include <rclcpp/rclcpp.hpp>
#include "sensor_msgs/msg/imu.hpp"
#include  "imu.h" 


class ImuNode : public rclcpp::Node {
public:
    /**
     * Constructs the ImuNode.
     */
    ImuNode(); 
private: 
    /**
     * Publishes IMU messages 
    */
    void imu_publisher_cb(); 
    size_t frame_id{}; 
    std::shared_ptr<Imu_Interface> imu_interface{nullptr}; 
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_publisher; 
    rclcpp::TimerBase::SharedPtr timer; 
    std::chrono::duration<int, std::milli> timer_duration; 

};


#endif //UMRT_IMU_NODE_HPP
