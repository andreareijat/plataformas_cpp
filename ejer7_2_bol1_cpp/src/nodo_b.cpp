#include<ros/ros.h>
#include<std_msgs/Int32.h>
#include<iostream>
using namespace std;

int sumador;
ros::Publisher pub;

void numerosCallBack(const std_msgs::Int32ConstPtr &msg){

    int cont=0;

    sumador=sumador+msg->data;
    cont++;    

    if(cont%10==0){
        pub.publish(suma);
        ROS_INFO("Contador %i",cont);
    }
}

int main(int argc, char ** argv){
    ros::init(argc, argv, "nodo_b");
    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe<std_msgs::Int32>("numeros",10,numerosCallBack);
    pub=nh.advertise<std_msgs::Int32>("resultado",10);

    ros::spin();

    return 0;
}