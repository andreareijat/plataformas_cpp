#include<ros/ros.h>
#include<iostream>
#include<std_msgs/Int32.h>

using namespace std;

void contadorCallBack(const std_msgs::Int32ConstPtr &msg){

    ROS_INFO("Callback: %i", msg->data); //porque accedo como un puntero y no como msg.data????
}

int main(int argc, char ** argv){
    ros::init(argc, argv,"suscriptor");
    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe<std_msgs::Int32>("contador",10,contadorCallBack);

    ros::spin();

    return 0;

}