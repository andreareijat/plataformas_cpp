#include<ros/ros.h>
#include<iostream>
#include<std_msgs/Int32.h>

using namespace std;

int main(int argc, char ** argv){
    ros::init(argc,argv,"publicador");
    ros::NodeHandle nh;
    ros::Rate loop_rate(0.5);

    ros::Publisher pub=nh.advertise<std_msgs::Int32>("contador",10);

    std_msgs::Int32 msg;
    msg.data=0;

    while(ros::ok() || msg.data == 100){
        pub.publish(msg);
        msg.data+=1;
        loop_rate.sleep();
    }

    return 0;
}