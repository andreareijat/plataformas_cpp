#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include<iostream>
using namespace std;

void callBackResultados(const std_msgs::Int32ConstPtr & msg){
    ROS_INFO("Recibiendo la suma. La suma total es: %i", msg->data);
}
int main(int argc, char**argv){
    ros::init(argc,argv,"node_a");
    ros::NodeHandle nh;

    ros::Publisher pub=nh.advertise<std_msgs::Int32>("numeros",10);
    ros::Subscriber sub=nh.subscribe<std_msgs::Int32>("resultados",10,callBackResultados);

    std_msgs::Int32 msg;

    while(ros::ok()){
        cout<<"dame un numero: "<<endl;
        cin>>msg.data;
        pub.publish(msg);
        ros::spinOnce(); /*escucha el callback vuelve al main repetidamente, comprueba si hay algo en la cola(buffer), si lo hay lo imprime*/
    }

    return 0;
}