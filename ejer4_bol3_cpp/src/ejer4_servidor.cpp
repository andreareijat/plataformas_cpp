#include<ros/ros.h>
#include<my_msgs_srv/cuadrado.h>
#include<geometry_msgs/Twist.h>
#include<sensor_msgs/LaserScan.h>

using namespace std;

float velocidad = 0.3;
float distancia = 0.0;
ros::Publisher pub;

void scanCallBack(const sensor_msgs::LaserScanConstPtr &msg){
    distancia = msg->ranges[int(msg->ranges.size()/2)];
}

void girarRobot(geometry_msgs::Twist &msg){
    ros::Rate loop_rate(2);

    msg.angular.z=1.6;
    for (int i=0;i<2;i++){
        pub.publish(msg);
        loop_rate.sleep();
    }
    msg.angular.z=0; //probar a quitarlo
}

bool moverRobot(geometry_msgs::Twist &msg, int area){
    ros::Rate loop_rate(1);
    bool rdo=true;
    msg.linear.x=velocidad;

    if(distancia > 1.0){
        
        for(int i=0;i<area & rdo;i++){
            pub.publish(msg);
            loop_rate.sleep();
        }
    }
    else{
        ROS_INFO("Obstaculo");
        rdo=false;
    }

    msg.linear.x=0;
    return rdo;
}
bool dibujacuadrado(int area){

    bool rdo=true;
    geometry_msgs::Twist mov;

    for (int i = 0;i<4 && rdo; i++){

        rdo=moverRobot(mov,area);

        if (rdo){
            girarRobot(mov);
        }
    }

    return rdo;

}


bool cuadradoCallBack(my_msgs_srv::cuadradoRequest &request, my_msgs_srv::cuadradoResponse &response){

    bool rdo = true;

    for(int i=0;i<request.cantidad && rdo;i++){
        rdo=dibujacuadrado(request.area);
        }

    response.status=rdo;

    return true;
}

int main(int argc, char ** argv){
    ros::init(argc, argv, "nodo_servidor_cuadrado");
    ros::NodeHandle nh;
    
    ros::ServiceServer srvserver=nh.advertiseService<my_msgs_srv::cuadradoRequest,my_msgs_srv::cuadradoResponse>("servicio_cuadrado",cuadradoCallBack);
    ros::Subscriber sub=nh.subscribe<sensor_msgs::LaserScan>("scan",10,scanCallBack);
    pub=nh.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity",10);

    ros::MultiThreadedSpinner spinner(2); /*numeros de hilos, es necesario esto porque con servicios no se puede utilizar el ros::spin()*/
    spinner.spin(); /*pone a los dos hilos a la escucha*/

    return 0;
}