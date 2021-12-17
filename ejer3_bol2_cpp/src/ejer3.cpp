#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<iostream>

using namespace std;

int main(int argc, char ** argv){
    ros::init(argc, argv, "nodo_velocidad");
    ros::NodeHandle nh;

    ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity",10);
    ros::Rate loop_rate(0.5);

    geometry_msgs::Twist msg;
    cout<<"Introduzca una velocidad: "<<endl;cin>>msg.linear.x;

    while(ros::ok()){
        pub.publish(msg);
        loop_rate.sleep();
    }

    return 0;
}