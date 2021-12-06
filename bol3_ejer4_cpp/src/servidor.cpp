#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <bol3_ejer4_cpp/forma.h>

using namespace std;

ros::Publisher pub;
float distancia=0.0;
const float velocidad=0.3;

bool moverrobot(int area, geometry_msgs::Twist & msg_mov){

    bool rdo=true;
    msg_mov.linear.x=velocidad;
    ros::Rate sleep_rate(1);

    for(int i=0;i<area & rdo;i++){

        if (distancia>1){ 
        
            pub.publish(msg_mov);
            sleep_rate.sleep();
        }
        else{
            ROS_INFO("Obstaculo detectado.");
            rdo=false;
        }
       
        
    }
    msg_mov.linear.x=0;
    return rdo;
}

void girarrobot(geometry_msgs::Twist & msg_mov){

    msg_mov.angular.z=1.6;
    ros::Rate sleep_rate(1);
    for(int i=0;i<2;i++){
        pub.publish(msg_mov);
        sleep_rate.sleep();
    }
    msg_mov.angular.z=0;
}

bool dibujacuadrado(int area){

    bool rdo=true;
    geometry_msgs::Twist msg_mov;

    for (int i = 0;i<4 && rdo; i++){

        rdo=moverrobot(area,msg_mov);

        if (rdo){
            girarrobot(msg_mov);
        }
    }

    return rdo;

}

bool callBackServicioCuadrados(bol3_ejer4_cpp::formaRequest & req, bol3_ejer4_cpp::formaResponse & resp){

    bool rdo=true;

    for (int i=0;i<req.cuadrados && rdo;i++){

        rdo=dibujacuadrado(req.area);

    }

    resp.status=rdo;

    return true;

}

void callBackScan(const sensor_msgs::LaserScanConstPtr & msg){

    distancia=msg->ranges[int(msg->ranges.size()/2)];
}



int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_servidor");
    ros::NodeHandle nh;

    ros::Subscriber sub_scan=nh.subscribe<sensor_msgs::LaserScan>("scan",10,callBackScan);
    
    pub=nh.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity",10);
    ros::ServiceServer srv_server=nh.advertiseService<bol3_ejer4_cpp::formaRequest,bol3_ejer4_cpp::formaResponse>("srv_cuadrados",callBackServicioCuadrados);

    ros::MultiThreadedSpinner spinner(2); /*numeros de hilos, es necesario esto porque con servicios no se puede utilizar el ros::spin()*/
    spinner.spin(); /*pone a los dos hilos a la escucha*/

    return 0;

}