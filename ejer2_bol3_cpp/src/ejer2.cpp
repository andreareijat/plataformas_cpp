#include<ros/ros.h>
#include<my_msgs_srv/fibo.h>
#include<sstream>

using namespace std;

ros::Publisher pub;

bool fibonacciCallBack(my_msgs_srv::fiboRequest &request, my_msgs_srv::fiboResponse &response){

    ros::Rate loop_rate(2);

    double anterior = 1.0;
    double siguiente = 0.0;
    stringstream ss; //buffer

    for(int i=0;i<=request.tope;i++){

        ss<<siguiente<<","; //agregamos los elementos al buffer
        anterior+=siguiente;
        siguiente=anterior-siguiente;
        

        loop_rate.sleep();
    }


    response.lista=ss.str(); //convertimos el buffer a cadena

    return true; //siempre true, es para saber si se ejecuta con exito
}

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_servicio_fibonacci");
    ros::NodeHandle nh;

    ros::ServiceServer srvserver=nh.advertiseService<my_msgs_srv::fiboRequest,my_msgs_srv::fiboResponse>("servicio_fibonacci",fibonacciCallBack);
    ROS_INFO("Servicio creado");

    ros::spin();

    return 0;
}