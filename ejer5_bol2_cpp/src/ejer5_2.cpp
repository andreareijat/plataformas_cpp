#include<ros/ros.h>
#include<std_msgs/Int32.h>
#include<iostream>

using namespace std;

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_cliente_robot_movimiento");
    ros::NodeHandle nh;

    ros::Rate loop_rate(2);

    ros::Publisher pub=nh.advertise<std_msgs::Int32>("ordenes",10);

    std_msgs::Int32 msg;

    cout<<"Introduce los grados como un valor multiplo de 90: "<<endl;cin>>msg.data;

    while(ros::ok()){ 
        
        pub.publish(msg);
        loop_rate.sleep();
    }

    return 0;
}