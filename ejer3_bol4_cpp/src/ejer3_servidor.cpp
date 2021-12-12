#include<ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include<my_own_action_msgs/numeros_aleatoriosAction.h>
#include<stdlib.h>

actionlib::SimpleActionServer<my_own_action_msgs::numeros_aleatoriosAction> * server=NULL;

void callBackGoalAccion(const my_own_action_msgs::numeros_aleatoriosGoalConstPtr &msg_goal){
    my_own_action_msgs::numeros_aleatoriosResult result;
    my_own_action_msgs::numeros_aleatoriosFeedback feedback;
    ros::Rate loop_rate(1);

    bool success=true;

    srand(msg_goal->seed); //establecemos la semilla para los numeros

    for(int i=0; i<msg_goal->iterations; i++){

        if(server->isPreemptRequested()){ //comprobamos si se ha solicitado una cancelacion
            ROS_INFO("La accion se ha cancelado");
            success=false;
            break;
        }

        //cubro el feedback
        ROS_INFO("Hago que trabajo. Segundo: %i",i);
        feedback.partial_number=rand()%10;
        server->publishFeedback(feedback); //publico el feedback

        loop_rate.sleep();
    }

    result.last_number=feedback.partial_number;

    if(success) server->setSucceeded(result);
    else server->setPreempted(result);
}


int main(int argc, char ** argv){
    ros::init(argc, argv, "nodo_servidor_accion");
    ros::NodeHandle nh;

    server = new actionlib::SimpleActionServer<my_own_action_msgs::numeros_aleatoriosAction>(nh, "servidor_accion_simple", callBackGoalAccion, false);
    server->start();
    ros::spin();

    return 0;
}