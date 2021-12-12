#include<ros/ros.h>
#include<actionlib/client/simple_action_client.h>
#include<iostream>
#include<my_own_action_msgs/numeros_aleatoriosAction.h>
#include<stdlib.h>

using namespace std;
int suma_maxima= 0;

actionlib::SimpleActionClient<my_own_action_msgs::numeros_aleatoriosAction> *cliente;

void doneCallBack(const actionlib::SimpleClientGoalState &state, const my_own_action_msgs::numeros_aleatoriosResultConstPtr &result){ //se llama al terminar la accion
    //state representa el estado de terminación, nos permite comprobar si se cancelo
    //resultado final = result aunque se haya cancelado

    ROS_INFO("Done Callback");
    ROS_INFO("Estado: %s", state.toString().c_str());
    ROS_INFO("Resultado: %i", result->last_number);
    
}

void activeCallBack(){ //se llama al iniciar la accion
    ROS_INFO("Empezando a trabajar");
}

void feedbackCallBack(const my_own_action_msgs::numeros_aleatoriosFeedbackConstPtr &feedback){ //recoge el feedback, podemos decidir cancelar el goal aqui
    ROS_INFO("Feedback callback");
    ROS_INFO("Feedback: %i", feedback->partial_number);
    
    int suma_parcial=0;
    suma_parcial+=feedback->partial_number;

    if (suma_parcial==suma_maxima){
        //cancelamos el goal
        cliente->cancelAllGoals();
    }
}

int main(int argc, char ** argv){
    ros::init(argc,argv,"nodo_cliente");

    cliente = new actionlib::SimpleActionClient<my_own_action_msgs::numeros_aleatoriosAction>("servidor_accion_simple",true);
    ros::Rate loop_rate(2);

    ROS_INFO("Esperando al servidor de acciones");
    cliente -> waitForServer();

    my_own_action_msgs::numeros_aleatoriosGoal goal_msg;

    cout<<"Introduzca un numero de iteraciones: "<<endl;cin>>goal_msg.iterations;
    cout<<"Introduzca una semilla: "<<endl;cin>>goal_msg.seed;
    cout<<"Introduzca la suma maxima: "<<endl;cin>>suma_maxima;

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