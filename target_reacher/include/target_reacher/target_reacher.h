#pragma once

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <string>
#include "bot_controller/bot_controller.h"
#include "ros2_aruco_interfaces/msg/aruco_markers.hpp"
#include "tf2_ros/static_transform_broadcaster.h"

// timer
class TargetReacher : public rclcpp::Node
{
public:
    TargetReacher(std::shared_ptr<BotController> const &bot_controller) : Node("target_reacher")
    {

        m_bot_controller = bot_controller;
        // std::array<std::array<double,2>,4> position;
        // for (int i=0; i<4; i++){
        //     position[0].at(i) = this->declare_parameter<double>("final_destination.aruco_" + std::string(i) + ".x");    
        //     position[1].at(i) = this->declare_parameter<double>("final_destination.aruco_" + std::string(i) + ".y");    
            
        // }

        // m_bot_controller->set_goal(2, 3);
        double x0 = this->declare_parameter<double>("final_destination.aruco_0.x");
        double y0 = this->declare_parameter<double>("final_destination.aruco_0.y");
        double x1 = this->declare_parameter<double>("final_destination.aruco_1.x");
        double y1 = this->declare_parameter<double>("final_destination.aruco_1.y");
        double x2 = this->declare_parameter<double>("final_destination.aruco_2.x");
        double y2 = this->declare_parameter<double>("final_destination.aruco_2.y");
        double x3 = this->declare_parameter<double>("final_destination.aruco_3.x");
        double y3 = this->declare_parameter<double>("final_destination.aruco_3.y");

        // move the robot    
        m_bot_controller->set_goal(x0, y0);
        reach_goal = create_subscription<std_msgs::msg::Bool>("/goal_reached", 10, std::bind(&TargetReacher::GoalCallback, this, std::placeholders::_1) );

    }
    void GoalCallback(const std_msgs::msg::Bool::SharedPtr msg);
    void rotate();
private:
    // attributes
    std::shared_ptr<BotController> m_bot_controller;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr reach_goal;
    bool rg = false;
};