#include <string>
// #include "odom_footprint_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/pose.hpp"
#include "rclcpp/rclcpp.hpp"

// void OdomFootprintBroadcaster::timer_callback()
// {
//     return;
//     //  broadcast_odom_footprint();
// }

// void OdomFootprintBroadcaster::broadcast_odom_footprint(geometry_msgs::msg::TransformStamped t)
// {
//     // geometry_msgs::msg::TransformStamped t;

//     // std::string odom1 = "/robot1/odom";
//     // std::string odom3 = "/robot3/odom";

//     // t.header.stamp = this->get_clock()->now();
//     // t.header.frame_id = "/robot1/odom";
//     // t.child_frame_id = "/robot1/base_footprint";

//     // t.transform.translation.x = 0;
//     // t.transform.translation.y = 0;
//     // t.transform.translation.z = 0;

//     // tf2::Quaternion q;
//     // q.setRPY(0, 0, 0);
//     // t.transform.rotation.x = q.x();
//     // t.transform.rotation.y = q.y();
//     // t.transform.rotation.z = q.z();
//     // t.transform.rotation.w = q.w();

//     // // Send the transformation
//     m_tf_broadcaster->sendTransform(t);
// }

// // void OdomFootprintBroadcaster::odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg){

// //     geometry_msgs::msg::TransformStamped t;

// //     // std::string odom1 = "/robot1/odom";
// //     // std::string odom3 = "/robot3/odom";

// //     t.header.stamp = this->get_clock()->now();
// //     t.header.frame_id = "/robot1/odom";
// //     t.child_frame_id = "/robot1/base_footprint";

// //     t.transform.translation.x = msg->pose.pose.position.x;
// //     t.transform.translation.y = msg->pose.pose.position.y;
// //     t.transform.translation.z = msg->pose.pose.position.z;

// //     // tf2::Quaternion q;
// //     // q.setRPY(0, 0, 0);
// //     t.transform.rotation.x = msg->pose.pose.orientation.x;
// //     t.transform.rotation.y = msg->pose.pose.orientation.y;
// //     t.transform.rotation.z = msg->pose.pose.orientation.z;
// //     t.transform.rotation.w = msg->pose.pose.orientation.w;
// //     broadcast_odom_footprint(t);

// //     // Send the transformation
// //     // m_tf_broadcaster->sendTransform(t);



// // }


class OdomFootprintBroadcaster : public rclcpp::Node
{
    public:
        OdomFootprintBroadcaster(std::string node_name) : Node(node_name)
        {
            // Initialize the transform broadcaster
            m_tf_broadcaster = std::make_shared<tf2_ros::TransformBroadcaster>(this);

            // Create a timer
            // m_timer = this->create_wall_timer(std::chrono::milliseconds((int)(1000.0 / 1.0)),
            //                                 std::bind(&OdomFootprintBroadcaster::timer_callback, this));
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            odom_sub = this->create_subscription<nav_msgs::msg::Odometry>("/robot1/odom", 10, std::bind(&OdomFootprintBroadcaster::odom_callback, this));
        
        }

    private:

        std::shared_ptr<tf2_ros::TransformBroadcaster> m_tf_broadcaster;

        // attributes
        rclcpp::TimerBase::SharedPtr m_timer;    
        // void timer_callback();
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub;
        void OdomFootprintBroadcaster::broadcast_odom_footprint(geometry_msgs::msg::TransformStamped t)
        {
        
            m_tf_broadcaster->sendTransform(t);
        }

        void OdomFootprintBroadcaster::odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg){

            geometry_msgs::msg::TransformStamped t;


            t.header.stamp = this->get_clock()->now();
            t.header.frame_id = "robot1/odom";
            t.child_frame_id = "robot1/base_footprint";

            t.transform.translation.x = msg->pose.pose.position.x;
            t.transform.translation.y = msg->pose.pose.position.y;
            t.transform.translation.z = msg->pose.pose.position.z;

            // tf2::Quaternion q;
            // q.setRPY(0, 0, 0);
            t.transform.rotation.x = msg->pose.pose.orientation.x;
            t.transform.rotation.y = msg->pose.pose.orientation.y;
            t.transform.rotation.z = msg->pose.pose.orientation.z;
            t.transform.rotation.w = msg->pose.pose.orientation.w;
            broadcast_odom_footprint(t);

            // Send the transformation
            // m_tf_broadcaster->sendTransform(t);



        }        // methods


};





















































