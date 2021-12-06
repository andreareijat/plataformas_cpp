#include <ros/ros.h>
#include <my_msgs/fibo.h>
#include <iostream>

using namespace std;

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_cliente");
    ros::NodeHandle nh;
    ros::ServiceClient cliente=nh.serviceClient<my_msgs::fibo>("mi_servicio");
    my_msgs::fibo msg;

    ROS_INFO("Esperando por el servidor");
    cliente.waitForExistence();

    cout<<"Introduzca el valor tope de la serie: "<<endl;cin>>msg.request.tope;

    if (cliente.call(msg)){  /*bool del callback*/
        ROS_INFO("Todo OK");
        ROS_INFO("El estado del servicio es %s", (msg.response.lista.c_str()));

        return 0;
    }
    else{
        ROS_INFO("Algo fallo");

        return 1;
    }
}