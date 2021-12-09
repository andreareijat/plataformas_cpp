#include<ros/ros.h>
#include<std_msgs/Int32.h>
#include<iostream>

using namespace std;

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_jugador1");
    ros::NodeHandle nh;
    ros::Rate loop_rate(2);

    ros::Publisher pub=nh.advertise<std_msgs::Int32>("enteros",10);
    std_msgs::Int32 msg;

    while(ros::ok() || msg.data==11){

        cout<<"Introduce un entero: "<<endl;cin>>msg.data;
        pub.publish(msg);
        loop_rate.sleep();
    }

    return 0;
}