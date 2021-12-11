#include<ros/ros.h>
#include<my_own_action_msgs/simpleaction_msgsAction.h>
#include<actionlib/client/simple_action_client.h>
#include<iostream>

using namespace std;
int segundos_cancelacion = 0;

actionlib::SimpleActionClient<my_own_action_msgs::simpleaction_msgsAction> *cliente;

void doneCallBack(const actionlib::SimpleClientGoalState &state, const my_own_action_msgs::simpleaction_msgsResultConstPtr &result){ //se llama al terminar la accion
    //state representa el estado de terminación, nos permite comprobar si se cancelo
    //resultado final = result aunque se haya cancelado

    ROS_INFO("Done Callback");
    ROS_INFO("Estado: %s", state.toString().c_str());
    ROS_INFO("Resultado: %i", result->trabajo);
    ROS_INFO("Resultado: %s", result->msg.c_str());
    
}

void activeCallBack(){ //se llama al iniciar la accion
    ROS_INFO("Empezando a trabajar");
}

void feedbackCallBack(const my_own_action_msgs::simpleaction_msgsFeedbackConstPtr &feedback){ //recoge el feedback, podemos decidir cancelar el goal aqui
    ROS_INFO("Feedback callback");
    ROS_INFO("Feedback: %i", feedback->parcial);

    if (feedback->parcial==segundos_cancelacion){
        //cancelamos el goal
        cliente->cancelAllGoals();
    }
}

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_cliente");

    cliente = new actionlib::SimpleActionClient<my_own_action_msgs::simpleaction_msgsAction>("servidor_accion_simple",true);
    ros::Rate loop_rate(2);

    ROS_INFO("Esperando al servidor de acciones");
    cliente -> waitForServer();

    my_own_action_msgs::simpleaction_msgsGoal goal_msg;

    cout<<"Introduzca un numero de segundos: "<<endl;cin>>goal_msg.segundos;
    cout<<"Introduzca un numero para detener la accion: "<<endl;cin>>segundos_cancelacion;

    cliente -> sendGoal(goal_msg, doneCallBack, activeCallBack, feedbackCallBack); //los callbacks son para realizar operaciones con lo que me devuelva el servidor

    actionlib::SimpleClientGoalState status=cliente -> getState();

    int cont=0;

    while(status==actionlib::SimpleClientGoalState::PENDING || status==actionlib::SimpleClientGoalState::ACTIVE){ //mientras la accion no termina
        ROS_INFO("Haciendo cosas %i", cont);
        loop_rate.sleep();
        cont++;
        status=cliente -> getState(); //actualizamos el estado de la accion en curso
    }

    return 0;
}