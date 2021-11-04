#include<ros/ros.h>
#include<std_msgs/Int32.h>

void contadorCallback(const std_msgs::Int32ConstPtr & msg){

        ROS_INFO("CallBack contador: %i", msg->data);

}

int main(int argc, char ** argv){

    ros::init(argc,argv,"subscriptor");
    ros::NodeHandle nh;
    ros::Subscriber sub=nh.subscribe<std_msgs::Int32>("contador",10,contadorCallback);

    ros::spin();

    return 0;
}