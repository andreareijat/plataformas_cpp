#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include "my_msgs/calificacion.h"
#include<iostream>

using namespace std;

int main(int argc, char ** argv){

    int mi_nota, mi_convocatoria;
    bool confirmacion = 1;

    ros::init(argc,argv,"publicador");
    ros::NodeHandle nh;
    ros::Publisher pub=nh.advertise<my_msgs::calificacion>("calificaciones",10);

    my_msgs::calificacion mi_calificacion;
    mi_calificacion.nombre="Andrea";
    mi_calificacion.convocatoria=9;
    mi_calificacion.nota=9.8;

    ros::Rate loop_rate(1);
    
    while(ros::ok() && confirmacion==1){
        pub.publish(mi_calificacion);

        cout<<"Introduzca el nombre: "<<mi_calificacion.nombre;
        cout<<"Introduzca la convocatoria: "<<mi_calificacion.convocatoria;
        cout<<"Introduzca la nota: "<<mi_calificacion.nota;

        cout<<"Desea introducir otra calificacion 1/0: "<<confirmacion;
        loop_rate.sleep();
    }

    return 0;
}