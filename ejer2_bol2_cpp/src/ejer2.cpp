#include<ros/ros.h>
#include<sensor_msgs/LaserScan.h>
#include<algorithm>

using namespace std;

void laserCallBack(const sensor_msgs::LaserScanConstPtr &msg){

    float valor_minimo=min_element(msg->ranges);
    int posicion_valor_minimo=ranges[valor_minimo]-ranges[begin(ranges)];

    ROS_INFO("Valor minimo de ranges: %i",valor_minimo);
    ROS_INFO("Posicion valor minimo: %i",)
}

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_laser");
    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe<sensor_msgs::LaserScan>("scan",10,laserCallBack);

    return 0;
}