#include <ros/ros.h>
#include <std_msgs/Int32.h>

int main(int argc,char ** argv){
    ros::init(argc,argv, "test2_node");
    ros::NodeHandle nh;
    ros::Publisher pub=nh.advertise<std_msgs::Int32>("contador",1);

    std_msgs::Int32 cont;
    cont.data=0;
    ros::Rate loop_rate(0.5);

    while(ros::ok() || cont.data==100){
        pub.publish(cont);
        cont.data++;
        loop_rate.sleep();
    }
    
    return 0;
}