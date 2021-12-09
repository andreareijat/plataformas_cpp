#include<ros/ros.h>
#include<std_msgs/Int32.h>
#include<my_msgs_srv/apuesta.h>

int numero_jugador1=0;

void jugador1CallBack(const std_msgs::Int32ConstPtr &msg){
    numero_jugador1=msg->data;
}

bool suma_numeros(int numero_apostado,int apuesta){

    int total=numero_apostado+numero_jugador1;

    if((total % 2 == 0 && apuesta == 0) || (total % 2 != 0 && apuesta == 1))
        return true;
    else{
        return false;
    }
}

bool apuestaCallBack(my_msgs_srv::apuestaRequest &request, my_msgs_srv::apuestaResponse &response){
    ROS_INFO("Dentro del callback");
    bool rdo = suma_numeros(request.numero_apostado,request.apuesta);

    response.resultado=rdo;
    response.numero_apostado=request.numero_apostado;
    response.numero_contrincante=numero_jugador1;

    return true;
}

int main(int argc, char ** argv){
    ros::init(argc, argv, "nodo_juez");
    ros::NodeHandle nh;

    ros::ServiceServer server=nh.advertiseService<my_msgs_srv::apuestaRequest,my_msgs_srv::apuestaResponse>("servicio_apuesta",apuestaCallBack);
    ROS_INFO("Servicio creado");
    ros::Subscriber sub=nh.subscribe<std_msgs::Int32>("enteros",10,jugador1CallBack);

    ros::MultiThreadedSpinner spinner(2); /*numeros de hilos, es necesario esto porque con servicios no se puede utilizar el ros::spin()*/
    spinner.spin(); /*pone a los dos hilos a la escucha*/

    return 0;
}