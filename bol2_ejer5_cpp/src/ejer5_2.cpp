#include <ros/ros.h>
#include<stdlib.h>
#include <std_msgs/Int32.h>
#include<time.h>

using namespace std;

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_b_examen");
    ros::NodeHandle nh;

    ros::Rate loop_rate(2);

    srand(time(NULL));

    std_msgs::Int32 num;
    
    num.data=90*(rand()%51);

    ros::Publisher pub=nh.advertise<std_msgs::Int32> ("comandos",10);

    while (ros::ok()){

        pub.publish(num);
        loop_rate.sleep();
    }

    return 0;
}