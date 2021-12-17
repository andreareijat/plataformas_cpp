#include<sensor_msgs/LaserScan.h>
#include<geometry_msgs/Twist.h>
#include<nav_msgs/Odometry.h>
#include<ros/ros.h>
#include<my_msgs_srv/coordenadas.h>

float posicion_x = 0.0;
float posicion_y = 0.0;
const float velocidad = 0.1;
const float distancia = 0.05;
ros::Publisher movimiento;

void posicionCallBack(const nav_msgs::OdometryConstPtr &msg){

    float posicion_x = msg->pose.pose.position.x + 2 ;
    float posicion_y = msg->pose.pose.position.y + 2;
}

void moverRobot(geometry_msgs::Twist &msg, int direccion, int pasos){ //se le pasan dos variables, la velocidad y la direccion (adelante, atras)
    ros::Rate loop_rate(2);

    msg.linear.x=velocidad*direccion;
    ROS_INFO("Moviendo el robot %i en la direccion: %s ", pasos, (direccion>0)?"Positiva":"Negativa");
    
    for(int i=0; i<pasos; i++){
        movimiento.publish(msg);
        loop_rate.sleep();
    }

    msg.angular.x=0;    
}

void girarRobot(geometry_msgs::Twist &msg, int direccion, int vueltas=2){
    ros::Rate loop_rate(2);
    msg.angular.z=1.6*direccion;
    ROS_INFO("Girando el robot");

    for (int i =0;i<vueltas; i++){
        movimiento.publish(msg);
        loop_rate.sleep(); 
    }

    msg.angular.z=0;
}

bool servicioCallBack(my_msgs_srv::coordenadasRequest &request, my_msgs_srv::coordenadasResponse &response){
    
    bool rdo=true;
    float x = request.x;
    float y = request.y;

    geometry_msgs::Twist msg;

    if(0.5 <= x && x <=3.0 && 0.5 <= y && y <= 5.0){

        ROS_INFO("Moviendo el robot a las coordenadas (%f,%f)",x, y);
        float x_diff=x-posicion_x;
        float y_diff=y-posicion_y;

        if(x_diff!=0){
            ROS_INFO("Moviendo las X");
            moverRobot(msg, (x_diff>0)?1:-1, abs(int(x_diff/distancia)));
        }
        if(y_diff!=0){
            ROS_INFO("Moviendo las Y");
            girarRobot(msg, 1);
            moverRobot(msg,(y_diff>0)?1:-1, abs(int(y_diff/distancia)));
            girarRobot(msg, -1);
        }
    }
    else{
        ROS_INFO("Coordenadas no validas");
        rdo=false;
    }

    response.success=rdo;

    return true;
}

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_servidor");
    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe<nav_msgs::Odometry>("odom",10,posicionCallBack);
    ros::ServiceServer srvserver=nh.advertiseService<my_msgs_srv::coordenadasRequest, my_msgs_srv::coordenadasResponse>("servicio_posicion",servicioCallBack);
    movimiento=nh.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity",10);

    ros::MultiThreadedSpinner spinner(2); /*numeros de hilos, es necesario esto porque con servicios no se puede utilizar el ros::spin()*/
    spinner.spin(); /*pone a los dos hilos a la escucha*/

    return 0;
}