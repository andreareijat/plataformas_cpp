#include <ros/ros.h>
#include <my_msgs/fibo.h>
#include <sstream> 

using namespace std;

bool callBackFibonacci(my_msgs::fiboRequest &req, my_msgs::fiboResponse & resp){

    double total=0.0;
    stringstream ss;
    double pre = 0.0;
    double pos = 1.0;
    
    ros::Rate loop_rate(2);

    for(int i=0;i<req.tope;i++){

        total=pre+pos;
        ss<<pre<<","<<pos;
        pre=pos;
        pos=total;
        loop_rate.sleep();
    }

    resp.lista=ss.str();

    return true;

}

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_ejer2");
    ros::NodeHandle nh;

    ros::ServiceServer server=nh.advertiseService<my_msgs::fiboRequest,my_msgs::fiboResponse>("mi_servicio",callBackFibonacci);
    ROS_INFO("Servicio creado");

    ros::spin();

    return 0;
}