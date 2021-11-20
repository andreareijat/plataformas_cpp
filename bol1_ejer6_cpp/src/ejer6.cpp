#include <ros/ros.h>
#include <my_msgs/calificacion.h>
#include <iostream>

using namespace std;

void calificacionesCallBack (const my_msgs::calificacionConstPtr & msg){
    ROS_INFO("Nombre ");
    cout<<"Nombre: "<<msg->nombre<<endl<<"Convocatoria: "<<msg->convocatoria<<endl<<"Nota: "<<msg->nota<<endl;
}

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_suscriptor");
    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe("calificaciones",10,calificacionesCallBack);

    ros::spin();

    return 0;
}