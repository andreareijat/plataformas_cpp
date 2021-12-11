#include<ros/ros.h>
#include<my_own_action_msgs/simpleaction_msgsAction.h>
#include<actionlib/server/simple_action_server.h>

actionlib::SimpleActionServer<my_own_action_msgs::simpleaction_msgsAction> * server=NULL;

void callBackGoalAccion(const my_own_action_msgs::simpleaction_msgsGoalConstPtr &msg_goal){
    my_own_action_msgs::simpleaction_msgsResult result;
    my_own_action_msgs::simpleaction_msgsFeedback feedback;
    ros::Rate loop_rate(1);
    bool success = true;
    int i=0;

    for(;i<msg_goal->segundos;i++){

        if(server->isPreemptRequested()){ //comprobamos si se ha solicitado una cancelacion
            ROS_INFO("La accion se ha cancelado");
            success=false;
            break;
        }

        //cubro el feedback
        ROS_INFO("Hago que trabajo. Segundo: %i",i);
        feedback.parcial=i;
        server->publishFeedback(feedback); //publico el feedback

        loop_rate.sleep();
    }

    result.trabajo=i;
    result.msg=(success)?"La accion termino correctamente":"La accion tuvo errores";

    if(success) server->setSucceeded(result);
    else server->setPreempted(result);
}

int main(int argc, char ** argv){
    ros::init(argc, argv, "nodo_servidor_accion");
    ros::NodeHandle nh;

    server = new actionlib::SimpleActionServer<my_own_action_msgs::simpleaction_msgsAction>(nh, "servidor_accion_simple", callBackGoalAccion, false);
    server->start();
    ros::spin();

    return 0;
}