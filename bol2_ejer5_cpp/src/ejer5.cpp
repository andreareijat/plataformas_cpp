#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int32.h>

float distancia = 0.0;
ros::Publisher pub;
float velocidad=0.3;

void callBackScan(const sensor_msgs::LaserScanConstPtr & msg){

    distancia = msg->ranges[int(msg->ranges.size()/2)];
}

void desplazaRobot(geometry_msgs::Twist & msg_mov, int direccion){
    ros::Rate loop_rate(2);

    msg_mov.linear.x=direccion*velocidad;
    pub.publish(msg_mov);
    loop_rate.sleep();

}

void giraRobot(geometry_msgs::Twist & msg_mov, int vueltas=2){

    ros::Rate loop_rate(2);
    msg_mov.angular.z=1.6*direccion;

    for(int i = 0;i<vueltas;i++){
        pub.publish(msg_mov);
        loop_rate.sleep();
    }
}

void callBackComandos(const std_msgs::Int32ConstPtr & msg){

    ROS_INFO("Recibido el comando %i", msg->data);

    if(msg->data == 6 || msg->data == 4){
        ROS_INFO("Muevo el robot");
        desplazaRobot(msg_mov, (msg->data==4)?-1:1);
        if (distancia<1.0 && msg->data==6)
            return;

    }else if(msg->data == 2 || msg->data == 8){
        ROS_INFO("Giro el robot");
        giraRobot(msg_mov,(msg->data==2)?-1:1));
    }
    else{
        ROS_INFO("El comando no vale");
    }

}

int main(int argc, char ** argv){
    ros::init(argc,argv, "servidor_node");
    ros::NodeHandle nh;

    ros::Subscriber sub_comandos=nh.subscribe<std_msgs::Int32>("comandos",10,callBackComandos);
    ros::Subscriber sub_escaner=nh.subscribe<sensor_msgs::LaserScan>("scan",10,callBackScan);
    pub=nh.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity",10);

    ros::spin();

    return 0;
}