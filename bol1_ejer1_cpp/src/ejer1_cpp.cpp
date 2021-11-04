#include <ros/ros.h>
#include <std_msgs/Int32.h>
using namespace std;

int main(int argc, char ** argv){
    ros::init(argc,argv, "test1_node");
    ros::NodeHandle nh;
    ros::Rate loop_rate(2);

    while(ros::ok()){
        ROS_INFO("HOLA MUNDO");
        
        loop_rate.sleep();
    }

    return 0;
}