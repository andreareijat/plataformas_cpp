#include<ros/ros.h>
#include<actionlib_tutorials/FibonacciAction.h>
#include<actionlib/client/simple_action_client.h>
#include <sstream> 

using namespace std;
int tope = 0;

actionlib::SimpleActionClient<actionlib_tutorials::FibonacciAction> *cliente;

void doneCallBack(const actionlib::SimpleClientGoalState &state, const actionlib_tutorials::FibonacciResultConstPtr &result){ //se llama al terminar la accion
    //state representa el estado de terminación, nos permite comprobar si se cancelo
    //resultado final = result aunque se haya cancelado

    ROS_INFO("Done Callback");
    ROS_INFO("Estado: %s", state.toString().c_str());

    cout<<"La serie de Fibonacci es: ";
    for(int i=0; i<result->sequence.size();i++){
        cout<<result->sequence[i]<<" ";
    }
    cout<<endl;

}

void activeCallBack(){ //se llama al iniciar la accion
    ROS_INFO("Empezando a trabajar");
}

void feedbackCallBack(const actionlib_tutorials::FibonacciFeedbackConstPtr &feedback){ //recoge el feedback, podemos decidir cancelar el goal aqui
    ros::Rate loop_rate(1);

    cout<<"Feedback serie: ";
    for(int i=0; i<feedback->sequence.size();i++){

        if(feedback->sequence[i]>tope){
                    cliente->cancelAllGoals(); //cancelamos el goal
                    break;}

        cout<<feedback->sequence[i]<<" ";
    }
    cout<<endl;

}

int main(int argc, char ** argv){
    ros::init(argc, argv, "nodo_cliente_fibonacci");
    cliente = new actionlib::SimpleActionClient<actionlib_tutorials::FibonacciAction>("fibonacci",true);

    ros::Rate loop_rate(2);

    ROS_INFO("Esperando al servidor de acciones");
    cliente -> waitForServer();

    actionlib_tutorials::FibonacciGoal msg;
    cout<<"Introduce un numero entero para calcular la serie: "<<endl;cin>>msg.order;

    tope=msg.order;

    cliente -> sendGoal(msg, doneCallBack, activeCallBack, feedbackCallBack); //los callbacks son para realizar operaciones con lo que me devuelva el servidor
    cliente -> waitForResult(ros::Duration(30)); //bloquea hasta que el goal termina, devuelve un bool para saber si el servidor termino en el tiempo objetivo (30)

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