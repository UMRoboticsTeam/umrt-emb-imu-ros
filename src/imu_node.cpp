#include "umrt-emb-imu-ros/imu_node.hpp"
#include <ctime> 


ImuNode::ImuNode() : Node("imu") {
    this->declare_parameter("i2c_addr", "/dev/i2c-1"); 
    this->declare_parameter("slave_addr", 0x28); 
    this->declare_parameter("polling_freq",100); 
    
    std::string i2c_addr{(this->get_parameter("i2c_addr")).as_string()}; 
    uint8_t slave_addr{this->get_parameter("slave_addr").as_int()}; 
    long int polling_freq{this -> get_parameter("polling_freq").as_int()}; 
    
    timer_duration = std::chrono::duration<int, std::milli>(polling_freq); 
    imu_publisher = create_publisher<sensor_msgs::msg::Imu>("imu_data",10); 
    imu_interface = std::make_shared<Imu_Interface>(i2c_addr,slave_addr); 
        
    timer = this->create_wall_timer(timer_duration, std::bind(&ImuNode::imu_publisher_cb, this));
}



void ImuNode::imu_publisher_cb(){
    std::array<double,3> gyr_xyz{imu_interface->get_gyr_xyz()};
    std::array<double,3> lin_acc_xyz{imu_interface->get_lin_acc_xyz()};
    std::array<double,4> qua_xyzw{imu_interface->get_qua_xyzw()};
    sensor_msgs::msg::Imu msg;
    msg.orientation.x = qua_xyzw[0];
    msg.orientation.y = qua_xyzw[1];
    msg.orientation.z = qua_xyzw[2];
    msg.orientation.w = qua_xyzw[3];
    msg.orientation_covariance[0] = -1;

    msg.angular_velocity.x = gyr_xyz[0];
    msg.angular_velocity.y = gyr_xyz[1];
    msg.angular_velocity.z = gyr_xyz[2];
    msg.angular_velocity_covariance[0] = -1;

    msg.linear_acceleration.x = lin_acc_xyz[0];
    msg.linear_acceleration.y = lin_acc_xyz[1];
    msg.linear_acceleration.z = lin_acc_xyz[2];
    msg.linear_acceleration_covariance[0] = -1;

   
    msg.header.stamp = this->now();  
    msg.header.frame_id = std::to_string(frame_id);

    imu_publisher->publish(msg);

    frame_id++;
}
