#include<ros/ros.h>
#include<my_own_msgs/calificacion.h>
#include<iostream>
#include<std_msgs/Bool.h>

using namespace std;

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_calificacion");
    ros::NodeHandle nh;

    my_own_msgs::calificacion msg;
    std_msgs::Bool confirmacion;

    confirmacion.data=true;

    ros::Publisher pub=nh.advertise<my_own_msgs::calificacion>("calificaciones",10);

    while(ros::ok() || confirmacion.data == false){

        if(confirmacion.data==true){

            cout<<"Introduzca el nombre: "<<endl;cin>>msg.nombre;
            cout<<"Introduzca la convocatoria: "<<endl;cin>>msg.convocatoria;
            cout<<"Introduzca la nota: "<<endl;cin>>msg.nota;

            pub.publish(msg);
            cout<<"Nuevo mensaje 1/0: "<<endl;cin>>confirmacion.data;

        }
    }


    return 0;
}