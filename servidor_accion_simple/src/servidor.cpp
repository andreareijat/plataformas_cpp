#include<ros/ros.h>
#include<my_own_action_msgs/simpleaction_msgsAction.h>
#include<actionlib/server/simple_action_server.h>

actionlib::SimpleActionServer<my_own_action_msgs::simpleaction_msgsAction> *server;

void callBackGoal(const my_own_action_msgs::simpleaction_msgsGoalConstPtr & goal){

    my_own_action_msgs::simpleaction_msgsFeedback feedback;
    my_own_action_msgs::simpleaction_msgsResult result;
    ros::Rate loop_rate(1);
    int cont=0;
    bool rdo=true;

    for(;cont<goal->segundos;cont++){

        if (server->isPreemptRequested()){ 
            ROS_INFO("La accion ha sido cancelada");
            rdo=false;
            break;
        }
        ROS_INFO("Hago que trabajo. Segundo: %i",cont);
        feedback.parcial=cont;
        server->publishFeedback(feedback);
        loop_rate.sleep();
    }

    result.trabajo=cont;
    result.msg=(rdo)?"La accion ha terminado bien":"La accion se ha cancelado";

    if(rdo) server->setSucceeded(result);
    else server->setPreempted(result);

}


int main(int argc, char ** argv){
    ros::init(argc,argv, "servidor_accion");
    ros::NodeHandle nh;
    server = new actionlib::SimpleActionServer<my_own_action_msgs::simpleaction_msgsAction>(nh,"accion_simple", &callBackGoal, false);
    server->start();
    ros::spin();

    return 0;
}