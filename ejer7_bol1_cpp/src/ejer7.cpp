#include<ros/ros.h>
#include<std_msgs/Int32.h>
#include<iostream>

using namespace std;

void resultadoCallBack(const std_msgs::Int32ConstPtr &msg){
    ROS_INFO("Resultado: %i",msg->data);
}

int main(int argc, char ** argv){
    ros::init(argc, argv, "nodo_a");
    ros::NodeHandle nh;

    std_msgs::Int32 msg;
    
    

    ros::Publisher pub=nh.advertise<std_msgs::Int32>("numeros",10);
    ros::Subscriber sub=nh.subscribe<std_msgs::Int32>("resultado",10,resultadoCallBack);

    while(ros::ok()){
        pub.publish(msg);
        cout<<"Introduzca un valor entero: "<<endl;cin>>msg.data;
        ros::spinOnce();
    }

    return 0;
}