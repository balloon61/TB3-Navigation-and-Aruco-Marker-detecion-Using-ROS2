#include <rclcpp/rclcpp.hpp>
#include "target_reacher/target_reacher.h"

void TargetReacher::GoalCallback(const std_msgs::msg::Bool::SharedPtr msg){
    rg = msg->data;
    if(rg == true){
    
        // Print message to the terminal window      
        RCLCPP_INFO(this->get_logger(),"Reach goal ");
       
        // Declaration of the publisher_ attribute
        // rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        // publisher_ = this->create_publisher<std_msgs::msg::String>("addison",10);
        // publisher_->publish(message);
        // TargetReacher::rotate();
    }
}
void TargetReacher::rotate(){
    return;
}


