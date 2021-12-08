#include<ros/ros.h>
#include<my_msgs_srv/cuadrado.h>

using namespace std;

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_cliente_cuadrado");
    ros::NodeHandle nh;

    ros::ServiceClient srvc=nh.serviceClient<my_msgs_srv::cuadrado>("servicio_cuadrado");
    my_msgs_srv::cuadrado msg;

    srvc.waitForExistence();

    cout<<"Introduce el valor del area: "<<endl;cin>>msg.request.area;
    cout<<"Introduce el numero de cuadrados: "<<endl;cin>>msg.request.cantidad;

    if(srvc.call(msg)){
        ROS_INFO("Todo ok");
        ROS_INFO("El estado del servicio es %s", (msg.response.status));
        return 0;
    }
    else{
        ROS_INFO("Algo ha fallado");
        return 1;
    }
}