#pragma once

#include "rclcpp/rclcpp.hpp"
#include <nav_msgs/msg/odometry.hpp>
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/pose.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include <string>

class OdomFootprintBroadcaster : public rclcpp::Node
{
    public:
        OdomFootprintBroadcaster(std::string node_name) : Node(node_name)
        {
            // Initialize the transform broadcaster
            m_tf_broadcaster = std::make_shared<tf2_ros::TransformBroadcaster>(this);

            // Create a timer
            m_timer = this->create_wall_timer(std::chrono::milliseconds((int)(1000.0 / 1.0)),
                                            std::bind(&OdomFootprintBroadcaster::timer_callback, this));
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            odom_sub = this->create_subscription<nav_msgs::msg::Odometry>("robot1/odom", 10, std::bind(&OdomFootprintBroadcaster::odom_callback, this));
        
        }

    private:

        std::shared_ptr<tf2_ros::TransformBroadcaster> m_tf_broadcaster;

        // attributes
        rclcpp::TimerBase::SharedPtr m_timer;    
        void timer_callback();
        void broadcast_odom_footprint(geometry_msgs::msg::TransformStamped);
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub;
        void odom_callback();
        // methods


};