#include<ros/ros.h>
#include<sensor_msgs/LaserScan.h>
#include<geometry_msgs/Twist.h>
#include<std_msgs/Int32.h>

using namespace std;

float velocidad = 0.3;
ros::Publisher pub;
float distancia = 0.0;

void scanCallBack(const sensor_msgs::LaserScanConstPtr &msg){
    distancia = msg->ranges[int(msg->ranges.size()/2)];
}

void giroRobot(geometry_msgs::Twist &msg, int grados){
    ros::Rate loop_rate(2);

    msg.angular.z=1.6;

    int vueltas=int(grados/45);

    for(int i=0; i<vueltas; i++){ //cada vuelta gira 45
        pub.publish(msg);
        loop_rate.sleep();
    }
}

void moveRobot(geometry_msgs::Twist &msg){
    ros::Rate loop_rate(2);

    msg.linear.x=velocidad;
    pub.publish(msg);
    loop_rate.sleep();
}

void ordenesCallBack(const std_msgs::Int32ConstPtr &msg){ //el mensaje es un numero de grados multiplo de 90

    ROS_INFO("Recibiendo el mensaje %i",msg->data);
    ros::Rate loop_rate(2);
    geometry_msgs::Twist move;
    
    if(distancia < 1.0){
        giroRobot(move,msg->data);
    }
    else{
         moveRobot(move);
    }
    loop_rate.sleep();
}

int main(int argc, char ** argv){
    ros::init(argc, argv, "nodo_movimiento_robot");
    ros::NodeHandle nh;

    ros::Subscriber sub_scaner=nh.subscribe<sensor_msgs::LaserScan>("scan",10,scanCallBack);
    ros::Subscriber sub_velocidad=nh.subscribe<std_msgs::Int32>("ordenes",10,ordenesCallBack);
    pub = nh.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity",10);

    ros::spin();

    return 0;
}