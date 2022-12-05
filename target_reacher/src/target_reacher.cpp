#include <rclcpp/rclcpp.hpp>
#include "target_reacher/target_reacher.h"

void TargetReacher::GoalCallback(const std_msgs::msg::Bool::SharedPtr msg){
    
    // This function is used for check if the robot reach the first goal
    // the first goal is the position which can detect marker
    
    // bool variable to check if the robot reach "first" goal
    rg = msg->data;
    
    // if reach goal and marker is not detect which means that before the first goal, 
    // because the robot have not seen the marker yet
    if(rg == true && md == false){
    
        // Print message to the terminal window      
        RCLCPP_INFO(this->get_logger(),"Reach goal ");
        // start rotate to find the marker
        rotate();

    }
}

void TargetReacher::MarkerdetectCallback(const ros2_aruco_interfaces::msg::ArucoMarkers::SharedPtr msg){
    // get the marker id
    marker_id = msg->marker_ids.at(0);
    // my marker id variable is initialize as 10 so if it is lower than 10 means that it detect the marker, 
    // also this should happen after reach first goal this is used to prevent so error
    if(marker_id < 10 && rg == true){
        // marker detect becomes true
        md = true;
        // print the marker id
        RCLCPP_INFO(this->get_logger(),"Marker detect %d", marker_id);
        // go to the position that marker id tells us
        GotoGoal();
    }
}

void TargetReacher::rotate(){

    
    // This function rotate the robot, which is use for finding the marker
    

    // generate twist message 
    geometry_msgs::msg::Twist msg;
    msg.linear.x = 0.0;
    msg.angular.z = 0.2;
    // publish twist message
    publisher_cmd_vel->publish(msg);
}

void TargetReacher::GotoGoal(){

    
    // This function is used for go to the goal that the marker ask the robot to go to
   
    if(marker_id == 0) 
        m_bot_controller->set_goal(x0, y0);
    else if(marker_id == 1)
        m_bot_controller->set_goal(x1, y1);
    else if(marker_id == 2)
        m_bot_controller->set_goal(x1, y1);
    else if(marker_id == 3)
        m_bot_controller->set_goal(x1, y1);

}