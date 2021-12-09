#include<ros/ros.h>
#include<my_msgs_srv/apuesta.h>
#include<iostream>

using namespace std;

int main(int argc, char ** argv){
    ros::init(argc, argv, "nodo_jugador2");
    ros::NodeHandle nh;
    

    ros::ServiceClient client=nh.serviceClient<my_msgs_srv::apuesta>("servicio_apuesta");
  
    my_msgs_srv::apuesta msg;
    client.waitForExistence();
    
    cout<<"Introduzca el numero apostado: "<<endl;cin>>msg.request.numero_apostado;
    cout<<"Introduzca la apuesta 1/0 (impar/par): "<<endl;cin>>msg.request.apuesta;

    if(client.call(msg)){
        ROS_INFO("Todo ok");
        ROS_INFO("El estado del servicio es %i", (msg.response.resultado));
        return 0;
    }
    else{
        ROS_INFO("Algo ha fallado");
        return 1;
    }
    

    


}