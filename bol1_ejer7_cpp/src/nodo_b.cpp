#include <ros/ros.h>
#include <std_msgs/Int32.h>

int sumador=0; 
int cont=0;
ros::Publisher pub; /*solo la creo de forma global, la inicializacion solo me la puede hacer el Handle*/

void callBackNumeros(const std_msgs::Int32ConstPtr & msg){
    ROS_INFO("Recibiendo numero %i", msg->data);

    sumador=sumador+msg->data;
    cont++;

    if(cont%10==0){
        std_msgs::Int32 msg_sum;
        msg_sum.data=sumador;
        pub.publish(msg_sum);

    }
}

int main(int argc, char** argv){
    ros::init(argc,argv,"node_b");
    ros::NodeHandle nh;
    ros::Subscriber sub=nh.subscribe<std_msgs::Int32>("numeros",10,callBackNumeros);
    pub=nh.advertise<std_msgs::Int32>("resultados",10);

    ros::spin();

    return 0;

}