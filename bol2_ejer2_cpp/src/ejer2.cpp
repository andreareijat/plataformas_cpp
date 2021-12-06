#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <algorithm>
#include <vector>

using namespace std;

void laserCallBack(const sensor_msgs::LaserScanConstPtr & msg){
    
    float distancia = 0.0;

    distancia = msg->ranges[int(msg->ranges.size()/2)]; /*distancia del objeto que tiene justo enfrente*/
    cout<<distancia<<endl;
    cout<<"Minimo"<<min_element(msg->ranges[0],msg->ranges[msg->ranges.size()])<<endl;

    /*float inicio = begin(msg->ranges);
    int posicion_valor_min=(msg->ranges)[valor_min]-(msg->ranges)[inicio];
    cout<<min_element((msg->ranges)[0],(msg->ranges)[(msg->ranges).size()])<<endl;*/
}

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_suscriptor_laser");
    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe("scan",10,laserCallBack);

    ros::spin();

    return 0;

}