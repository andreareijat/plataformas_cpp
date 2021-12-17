#include<ros/ros.h>
#include<my_msgs_srv/fibo.h>
#include<iostream>

using namespace std;

int main(int argc, char ** argv){
    ros::init(argc, argv, "nodo_cliente_fibonacci");
    ros::NodeHandle nh;

    ros::ServiceClient srvc=nh.serviceClient<my_msgs_srv::fibo>("servicio_fibonacci");

    my_msgs_srv::fibo msg;
    ROS_INFO("Esperando por el servidor");
    srvc.waitForExistence();

    cout<<"Introduzca el valor tope de la serie: "<<endl;cin>>msg.request.tope;

    if(srvc.call(msg)){
        ROS_INFO("Todo ok");
        ROS_INFO("El estado del servicio es %s", (msg.response.lista.c_str()));
        return 0;
    }
    else{
        ROS_INFO("Algo ha fallado");
        return 1;
    }
}