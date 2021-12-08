#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<sensor_msgs/LaserScan.h>
#include<std_msgs/Int32.h>

using namespace std;

ros::Publisher pub;
float distancia = 0.0;
float velocidad = 0.3;

void moverRobot(geometry_msgs::Twist &msg, int direccion){ //se le pasan dos variables, la velocidad y la direccion (adelante, atras)
    ros::Rate loop_rate(2);

    msg.linear.x=velocidad*direccion; //porque no puedo acceder como un puntero msg->linear.x??
    pub.publish(msg);

    loop_rate.sleep();
}

void girarRobot(geometry_msgs::Twist &msg, int direccion){
    ros::Rate loop_rate(2);

    int vueltas=2;
    msg.angular.z=1.6*direccion;
    
    for(int i = 0;i<vueltas;i++){
        pub.publish(msg);
        loop_rate.sleep();
    }

}

void ordenesCallBack(const std_msgs::Int32ConstPtr &msg){

    ROS_INFO("Recibiendo el comando %i", msg->data);

    geometry_msgs::Twist mov;

    if(msg->data==6 || msg->data==4){ //adelante, atras

        //ejecutar cualquiera de los otros 3   
        //pedir otro valor
        ROS_INFO("Avanza el robot");
        moverRobot(mov,(msg->data==4)?-1:1);
    
        if(distancia<1.0 && msg->data == 6)//comprobar si tiene un obstaculo delante
            return;
        
    }
    else if(msg->data==8 || msg->data==2){
        ROS_INFO("Giro el robot");
        girarRobot(mov,(msg->data==8)?1:-1);
    }
    else{ 
        ROS_INFO("El comando no vale");
    }
}

void scanCallBack(const sensor_msgs::LaserScanConstPtr &msg){

    distancia = msg->ranges[int(msg->ranges.size()/2)];
}

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_cuadrado_robot");
    ros::NodeHandle nh;

    ros::Subscriber sub_ordenes=nh.subscribe<std_msgs::Int32>("ordenes",10,ordenesCallBack);
    ros::Subscriber sub_scaner=nh.subscribe<sensor_msgs::LaserScan>("scan",10,scanCallBack);
    pub=nh.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity",10);

    ros::spin();

    return 0;
}