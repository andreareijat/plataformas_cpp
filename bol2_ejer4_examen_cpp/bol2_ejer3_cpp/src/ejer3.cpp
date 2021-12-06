#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include<iostream>

using namespace std;

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_publicador_velocidades");
    ros::NodeHandle nh;

    ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity",10);

    ros::Rate loop_rate(2);
    geometry_msgs::Twist msg;
    msg.linear.x = 0.0;

    cout<<"Introduzca la velocidad de avance del robot: "; cin>>msg.linear.x;cout<<endl;

    while (ros::ok()){

        pub.publish(msg);
        loop_rate.sleep();

    }

    return 0;
}