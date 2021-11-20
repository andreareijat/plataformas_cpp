#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <iostream>

using namespace std;

void posicionCallBack (const nav_msgs::OdometryConstPtr & msg){
    ROS_INFO("Posicion %i",msg->pose);
}

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_suscriptor_odom");
    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe("odom",10,posicionCallBack);

    ros::spin();

    return 0;
}