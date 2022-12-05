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
        // create the bot_controller
        m_bot_controller = bot_controller;

        // This part can used for simplifed the following part, but it's unfinish 
        // std::array<std::array<double,2>,4> position;
        // for (int i=0; i<4; i++){
        //     position[0].at(i) = this->declare_parameter<double>("final_destination.aruco_" + std::string(i) + ".x");    
        //     position[1].at(i) = this->declare_parameter<double>("final_destination.aruco_" + std::string(i) + ".y");    
            
        // }

        // get the value from yaml file
        x0 = this->declare_parameter<double>("final_destination.aruco_0.x");
        y0 = this->declare_parameter<double>("final_destination.aruco_0.y");
        x1 = this->declare_parameter<double>("final_destination.aruco_1.x");
        y1 = this->declare_parameter<double>("final_destination.aruco_1.y");
        x2 = this->declare_parameter<double>("final_destination.aruco_2.x");
        y2 = this->declare_parameter<double>("final_destination.aruco_2.y");
        x3 = this->declare_parameter<double>("final_destination.aruco_3.x");
        y3 = this->declare_parameter<double>("final_destination.aruco_3.y");

        // move the robot to the position which is able to detect the marker 
        m_bot_controller->set_goal(6.0, 4.5);
        // reach goal subscriber
        reach_goal = create_subscription<std_msgs::msg::Bool>("/goal_reached", 10, std::bind(&TargetReacher::GoalCallback, this, std::placeholders::_1) );
        // marker detect subscriber
        marker_detect = create_subscription<ros2_aruco_interfaces::msg::ArucoMarkers>("/aruco_markers", 10, std::bind(&TargetReacher::MarkerdetectCallback, this, std::placeholders::_1) );
        // twist cmd publisher
        publisher_cmd_vel = this->create_publisher<geometry_msgs::msg::Twist>("/robot1/cmd_vel", 10);

    }
    void GoalCallback(const std_msgs::msg::Bool::SharedPtr msg);
    void MarkerdetectCallback(const ros2_aruco_interfaces::msg::ArucoMarkers::SharedPtr msg);
    void rotate();
    void GotoGoal();

private:
    // attributes
    std::shared_ptr<BotController> m_bot_controller; // bot controller 
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr reach_goal; // reach goal subscriber
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_cmd_vel; // twist publisher
    rclcpp::Subscription<ros2_aruco_interfaces::msg::ArucoMarkers>::SharedPtr marker_detect; // marker detect subscriber

    // reach goal variable
    bool rg = false;
    // marker detect variable
    bool md = false;
    // marker id initialize, since the marker id should be only from 0~3 so any value which is not in this range should be fine
    int marker_id = 10;

    // record yaml position variables
    double x0 = 0;
    double y0 = 0;
    double x1 = 0;
    double y1 = 0;
    double x2 = 0;
    double y2 = 0;
    double x3 = 0;
    double y3 = 0;
    
};