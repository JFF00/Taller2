#include <iostream>
#include <string>
using namespace std;
#include "tablero.cpp"
void menu(tablero t){
    int opt;
    cout<<"------------------CONECTA4----------------"<<endl;
    cout<<"1)JUGAR CONTRA IA\n2)PVP"<<endl;
    cin>>opt;
    if(opt==1){t.jugarvsIA();}
    else if(opt==2){t.jugarvsPlayer();}
}
int main(){
    tablero t=tablero();
    menu(t);

}
