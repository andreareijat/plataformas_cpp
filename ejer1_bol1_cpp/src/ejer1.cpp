#include<ros/ros.h>
#include<iostream>

using namespace std;

int main(int argc, char ** argv){
    ros::init(argc, argv, "nodo_prueba");
    ros::NodeHandle nh;

    ros::Rate loop_rate(0.5);

    while(ros::ok()){
        cout<<"Hello word"<<endl;
        loop_rate.sleep();
    }
    return 0;
}
