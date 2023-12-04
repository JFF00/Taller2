#include "tablero.h"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;
tablero::tablero(){//constructor del tablero, no necesita parametros. Se genera un espacio vacio para los puestos vacios del tablero
    for (int i=0;i<6; ++i) {
        for (int j=0;j<7; ++j) {
            tabla[i][j] = ' ';
        }
    }
}
void tablero::printTablero(){
    for(int i=0;i<6;i++){
        for(int j=0;j<7;j++){
            cout<<"  [  "<<tabla[i][j]<<"  ]  ";
        }
        cout<<endl;
    }
    cout<<"---------------------------------------------------------------"<<endl;
}


int tablero::añadirFicha(char tabla[6][7],int c,int turno){//funcion que retorna la columna a la que se añadió una ficha, -1 si es que no hay espacio en la columna
    char color=' ';
    if(turno%2==0){//si es numero par o 0, es turno del primer jugador y por lo tanto el color es R
        color='R';
    }
    else if(turno%2!=0){
        color='A';
    }
    for(int i=5;i>=0;i--){//si es numero inpar o 1, es turno del primer jugador y por lo tanto el color es a
        if(tabla[i][c]==' '){
            tabla[i][c]=color;
            return i;
            break;
        }
    }
    return -1;
}
//funcion que juega vs la ia, en comparacion a jugarvsPlayer solo cambia que la seleccion de la columna está dada por minimax y mejorCol, mientras que vs un player está dada por la 
//seleccion del jugador.
void tablero::jugarvsIA(){
    int i=0;
    int col;
    bool out=false;
    int dificultad;
    cout<<"Dificultad:\n1)Facil\n2)Normal\n3)Dificil"<<endl;
    cin>>dificultad;
    if(dificultad==1){
        dificultad=2;
    }
    if(dificultad==2){
        dificultad=4;
    }
    if(dificultad==3){
        dificultad=7;
    }
    cout<<"Cargar Partida?\n1)Si\n2)No"<<endl;
    int opt;
    cin>>opt;
    if(opt==1){
        cargarPartida(tabla);
    }
    
    cout<<"PRESIONAR 0 PARA SALIR."<<endl;
    printTablero();
while(out!=true){
    ///TURNO DEL PRIMER JUGADOR
    if(i%2==0){
        cout<<"Jugador 1: Ingresar columna:"<<endl;
        cin>>col;
        if(col==0){
            cout<<"Saliendo"<<endl;
            cout<<"Guardar Partida?\n1)Si\n2)No"<<endl;
            int save;
            cin>>save;
            if(save==1){
                guardarPartida();
            }
            else{out=true;
           } break;
        }
        else if(tabla[0][col-1]!=' '){
            cout<<"NO HAY ESPACIO EN ESTA COLUMNA. ESCOGER OTRA: "<<endl;
            cin>>col;
            añadirFicha(tabla,col-1,i); 
        }
        else{
            añadirFicha(tabla,col-1,i);
        }
    }
    //TURNO DEL SEGUNDO JUGADOR O LA IA
    if(i%2!=0){
        unsigned t0,t1;
        t0=clock();
        int colia=mejorCol(tabla,dificultad);
        añadirFicha(tabla,colia,i);
        t1=clock();
        double time=(double(t1-t0)/CLOCKS_PER_SEC);
        cout<<"SE DEMORA: "<<time<<endl;

        
    }
    out=checkWin(tabla,i);//en cada turno se comprueba si es que este gana el juego.
    int contcolllena=0;
    for(int c=0;c<7;c++){
            if(tabla[0][c]!=' '){
                contcolllena++;
            }
    }
    if(out==true){
        cout<<"Victoria!!!!!!. Ganó el Jugador: "<<(i%2)+1<<endl;
    }
    else if(contcolllena==7){
       cout<<"EMPATE."<<endl;
                out=true;
            break;
    }
    else{
        i++;
    }
    printTablero();
  }
}

//Funcion que juega vs otro jugador, tambien permite ingresos por consola para escoger las columnas. Si la columna no tiene espacio pide una distinta.
void tablero::jugarvsPlayer(){
    int i=0;
    int col;
    bool out=false;
    cout<<"PRESIONAR 0 PARA SALIR."<<endl;
    cout<<"Cargar Partida?\n1)Si\n2)No"<<endl;
    int opt;
    cin>>opt;
    if(opt==1){
        cargarPartida(tabla);}
    else{
    printTablero();
while(out!=true){
    ///TURNO DEL PRIMER JUGADOR
    if(i%2==0){
        cout<<"Jugador 1: Ingresar columna:"<<endl;
        cin>>col;
        if(col==0){
            cout<<"Saliendo"<<endl;
            cout<<"Guardar Partida?\n1)Si\n2)No"<<endl;
            int save;
            cin>>save;
            if(save==1){
                guardarPartida();
            }
            else{out=true;
           } break;
        }
        else if(tabla[0][col-1]!=' '){
            cout<<"NO HAY ESPACIO EN ESTA COLUMNA. ESCOGER OTRA: "<<endl;
            cin>>col;
            añadirFicha(tabla,col-1,i); 
        }
        else{
            añadirFicha(tabla,col-1,i);
        }
    }
    //TURNO DEL SEGUNDO JUGADOR O LA IA
    if(i%2!=0){
        cout<<"Jugador 2: Ingresar columna:"<<endl;
        cin>>col;
        if(col==0){
        cout<<"Saliendo"<<endl;
            cout<<"Guardar Partida?\n1)Si\n2)No"<<endl;
            int save;
            cin>>save;
            if(save==1){
                guardarPartida();
            }
            else{out=true;
           } break;
        }
        else if(tabla[0][col-1]!=' '){
            cout<<"NO HAY ESPACIO EN ESTA COLUMNA. ESCOGER OTRA: "<<endl;
            cin>>col;
            añadirFicha(tabla,col-1,i); 
        }
        else{
            añadirFicha(tabla,col-1,i);
        }
        
    }
    int contcolllena=0;
    for(int c=0;c<7;c++){
            if(tabla[0][c]!=' '){
                contcolllena++;
            }
    }
    if(contcolllena==7){
        cout<<"EMPATE."<<endl;
                out=true;
                break;
    }
    out=checkWin(tabla,i);
    if(out==true){
        cout<<"Victoria!!!!!!. Ganó el Jugador: "<<(i%2)+1<<endl;
    }else{
        i++;
    }
    printTablero();
}  
}}
//funcion que retorna true si se cumple una de las condiciones de victoria. El parametro i hace referencia al turno y por tanto el color de la ficha.
bool tablero::checkWin(char tabla[6][7],int i){
    //Se comprueban las distintas formas de ganar.
    char color=' ';
    if(i%2==0){
        color='R';
    }
    else if(i%2!=0){
        color='A';
    }
    //Diagonales positivas
    for(int f=0;f<3;f++){
        for(int c=0;c<4;c++){
            if(tabla[f][c]==color&&tabla[f-1][c+1]==color&&tabla[f-2][c+2]==color&&tabla[f-3][c+3]==color){
                return true;
                break;
            }
        }
    }
    //Diagonales negativas
    for(int f=3;f<6;f++){
        for(int c=0;c<4;c++){
            if(tabla[f][c]==color&&tabla[f-1][c-1]==color&&tabla[f-2][c-2]==color&&tabla[f-3][c-3]==color){
                return true;
                break;
            }
        }
    }
    //Verticales    
    for(int f=3;f<6;f++){
        for(int c=0;c<7;c++){
            if(tabla[f][c]==color&&tabla[f-1][c]==color&&tabla[f-2][c]==color&&tabla[f-3][c]==color){
                return true;   
                break;        
            }
        }
    }
    //Horizontales
    for(int f=0;f<6;f++){
        for(int c=0;c<4;c++){
            if(tabla[f][c]==color&&tabla[f][c+1]==color&&tabla[f][c+2]==color&&tabla[f][c+3]==color){
               return true;
               break;
            }
            
        }}
    return false;
}
//funcion que retorna si se cumple una condicion de victoria o empate
bool tablero::esHoja(char tabla[6][7]){
    int columnallena=0;
    bool llena=false;
    for(int c=0;c<7;c++){
        if(tabla[0][c]=='A'||tabla[0][c]=='R'){
            columnallena++;
        }
    }
    if(columnallena==7){
        llena=true;
    }
    return checkWin(tabla,0)||checkWin(tabla,1)||llena;

}

//Funcion donde se calcula puntaje del tablero actualmente. Segun cuantas fichas seguidas hayan el puntaje aumenta. Si hay 2 fichas son 10 puntos, si hay 3 son 100 y si hay 4 son 1000000
int tablero::puntajeActual(char copia[6][7]){
    int puntaje=0;
    for(int f=0;f<6;f++){
        for(int c=0;c<4;c++){
            //horizontal
            if(copia[f][c]=='R'&&copia[f][c+1]=='R'){
                puntaje+=10;
            }
            if(copia[f][c]=='R'&&copia[f][c+1]=='R'&&copia[f][c+2]=='R'){
                puntaje+=100;
            }
            if(copia[f][c]=='R'&&copia[f][c+1]=='R'&&copia[f][c+2]=='R'&&copia[f][c+3]=='R'){
                puntaje+=1000000;
            }
            if(copia[f][c]=='A'&&copia[f][c+1]=='A'){
                puntaje-=10;
            }
             if(copia[f][c]=='A'&&copia[f][c+1]=='A'&&copia[f][c+2]=='A'){
                puntaje-=100;
            }
            if(copia[f][c]=='A'&&copia[f][c+1]=='A'&&copia[f][c+2]=='A'&&copia[f][c+3]=='A'){
                puntaje-=1000000;
            }
            
        }}
    for(int f=3;f<6;f++){
        for(int c=0;c<7;c++){
             //vertical
            if(copia[f][c]=='R'&&copia[f-1][c]=='R'){
                puntaje+=10;
            }
            if(copia[f][c]=='R'&&copia[f-1][c]=='R'&&copia[f-2][c]=='R'){
                puntaje+=100;
            }
            if(copia[f][c]=='R'&&copia[f-1][c]=='R'&&copia[f-2][c]=='R'&&copia[f-3][c]=='R'){
                puntaje+=1000000;
            }
            if(copia[f][c]=='A'&&copia[f-1][c]=='A'){
                puntaje-=10;
            }
             if(copia[f][c]=='A'&&copia[f-1][c]=='A'&&copia[f-2][c]=='A'){
                puntaje-=100;
            }
            if(copia[f][c]=='A'&&copia[f-1][c]=='A'&&copia[f-2][c]=='A'&&copia[f-3][c]=='A'){
                puntaje-=1000000;
            }
        }
    }
    for(int f=3;f<6;f++){
        for(int c=0;c<4;c++){
             //diagonal arriba
            if(copia[f][c]=='R'&&copia[f-1][c+1]=='R'){
                puntaje+=10;
            }
            if(copia[f][c]=='R'&&copia[f-1][c+1]=='R'&&copia[f-2][c+2]=='R'){
                puntaje+=100;
            }
            if(copia[f][c]=='R'&&copia[f-1][c+1]=='R'&&copia[f-2][c+2]=='R'&&copia[f-3][c+3]=='R'){
                puntaje+=1000000;
            }
            if(copia[f][c]=='A'&&copia[f-1][c+1]=='A'){
                puntaje-=10;
            }
             if(copia[f][c]=='A'&&copia[f-1][c+1]=='A'&&copia[f-2][c+2]=='A'){
                puntaje-=100;
            }
            if(copia[f][c]=='A'&&copia[f-1][c+1]=='A'&&copia[f-2][c+2]=='A'&&copia[f-3][c+3]=='A'){
                puntaje-=1000000;
            }
        }
    }
    for(int f=0;f<3;f++){
        for(int c=0;c<4;c++){
             //diagonal abajo
            if(copia[f][c]=='R'&&copia[f+1][c+1]=='R'){
                puntaje+=10;
            }
            if(copia[f][c]=='R'&&copia[f+1][c+1]=='R'&&copia[f+2][c+2]=='R'){
                puntaje+=100;
            }
            if(copia[f][c]=='R'&&copia[f+1][c+1]=='R'&&copia[f+2][c+2]=='R'&&copia[f+3][c+3]=='R'){
                puntaje+=1000000;
            }
            if(copia[f][c]=='A'&&copia[f+1][c+1]=='A'){
                puntaje-=10;
            }
             if(copia[f][c]=='A'&&copia[f+1][c+1]=='A'&&copia[f+2][c+2]=='A'){
                puntaje-=100;
            }
            if(copia[f][c]=='A'&&copia[f+1][c+1]=='A'&&copia[f+2][c+2]=='A'&&copia[f+3][c+3]=='A'){
                puntaje-=1000000;
            }
        }
    }
 return puntaje;
}
//algoritmo minimax para la decision de la CPU, retorna el mejor puntaje.
int tablero::minimax(char tabla[6][7],int profundidad,int turno){
   int score=puntajeActual(tabla);
   bool hoja=esHoja(tabla);
    // Caso base: si la profundidad máxima ha sido alcanzada o el juego ha terminado
    if (profundidad== 0 ||hoja==true ) {
        return score;
    }

    if (turno%2!=0) {
        int maxScore=INT_MIN;
        for (int c=0;c<7;++c) {
            if (tabla[0][c]=='A'||tabla[0][c]=='R') {
                char copia[6][7];
                for(int f1=0;f1<6;f1++){
                  for(int c1=0;c1<7;c1++){
                      copia[f1][c1]=tabla[f1][c1];}}
                añadirFicha(copia,c,turno);
                int score = minimax(copia,profundidad- 1,1);
                if(score>maxScore){
                    maxScore=score;
                }
            }
        }

        return maxScore;
    } else {
        int minScore=INT_MAX;
        for (int c=0;c<7;++c) {
            if (tabla[0][c]==' ') {
                char copia[6][7];
                for(int f1=0;f1<6;f1++){
                  for(int c1=0;c1<7;c1++){
                      copia[f1][c1]=tabla[f1][c1];}}
                añadirFicha(copia,c,turno+1);
                int score= minimax(copia,profundidad- 1,0);
                if(score<minScore){
                    minScore=score;
                }
            }
        }

        return minScore;
    }
}
//usa minimax para retornar la mejor columna.
int tablero::mejorCol(char tabla[6][7],int dificultad) {
    int mejorScore=INT_MIN;
    int mejorCol=-1;
    for (int c=0; c<7; ++c) {
        if (tabla[0][c]==' ') {
            char copia[6][7];
                for(int f1=0;f1<6;f1++){
                  for(int c1=0;c1<7;c1++){
                      copia[f1][c1]=tabla[f1][c1];}}
            añadirFicha(copia,c,1);
            int colScore= minimax(copia,dificultad, false);
            if (colScore>mejorScore) {
                mejorCol=c;
                mejorScore= colScore;
            }
        }
    }

    return mejorCol;

}
//se guardan las partidas
void tablero::guardarPartida(){
    string nombrepartida="";
    cout<<"Ingresar nombre de archivo";
    cin>>nombrepartida;
    nombrepartida+=".csv";
    ofstream partida(nombrepartida);
    if(!partida){
        cout<<"Error al crear archivo"<<endl;
    }else{
        fflush(stdin);
        for(int f=0;f<6;f++){
            for(int c=0;c<7;c++){
                if(tabla[f][c]=='A'){
                    partida<<2<<";";
                }
                if(tabla[f][c]=='R'){
                    partida<<1<<";";
                }
                if(tabla[f][c]==' '){
                    partida<<0<<";";
                }
            }
            partida<<endl;
        }
        partida.close();
        cout<<"Partida guardada correctamente."<<endl;
    }
}
//se cargan las partidas
void tablero::cargarPartida(char tabla[6][7]){
    string nombrepartida="";
    string linea;
    string c1,c2,c3,c4,c5,c6,c7;
    char cc1,cc2,cc3,cc4,cc5,cc6,cc7;
    cout<<"Ingresar nombre de archivo";
    cin>>nombrepartida;
    nombrepartida+=".csv";
    ifstream partida(nombrepartida,ios::in);
    if(!partida){
        cout<<"Error al abrir"<<endl;
    }
    else{
        int fila=0;
        while(getline(partida,linea)){
            stringstream line(linea);
            getline(line,c1,';');
            getline(line,c2,';');
            getline(line,c3,';');
            getline(line,c4,';');
            getline(line,c5,';');
            getline(line,c6,';');
            getline(line,c7,';');
            if(c1=="1"){cc1='R';}else if(c1=="2"){cc1='A';}else if(c1=="0"){cc1=' ';}

            if(c2=="1"){cc2='R';}else if(c2=="2"){cc2='A';}else if(c2=="0"){cc2=' ';}

            if(c3=="1"){cc3='R';}else if(c3=="2"){cc3='A';}else if(c3=="0"){cc3=' ';}

            if(c4=="1"){cc4='R';}else if(c4=="2"){cc4='A';}else if(c4=="0"){cc4=' ';}

            if(c5=="1"){cc5='R';}else if(c5=="2"){cc5='A';}else if(c5=="0"){cc5=' ';}

            if(c6=="1"){cc6='R';}else if(c6=="2"){cc6='A';}else if(c6=="0"){cc6=' ';}

            if(c7=="1"){cc7='R';}else if(c7=="2"){cc7='A';}else if(c7=="0"){cc7=' ';}
            tabla[fila][0]=cc1;
            tabla[fila][1]=cc2;
            tabla[fila][2]=cc3;
            tabla[fila][3]=cc4;
            tabla[fila][4]=cc5;
            tabla[fila][5]=cc6;
            tabla[fila][6]=cc7;
            cout<<cc1<<cc2<<cc3<<cc4<<cc5<<cc6<<cc7<<endl;
            fila++;
        }
        partida.close();
        cout<<"Archivo cargado correctamente"<<endl;
    }
}
int tablero::minimaxAB(char tabla[6][7],int profundidad,int alfa,int beta,int turno){
    int score=puntajeActual(tabla);
   bool hoja=esHoja(tabla);
    // Caso base: si la profundidad máxima ha sido alcanzada o el juego ha terminado
    if (profundidad== 0 ||hoja==true ) {
        return score;
    }
    if (turno%2!=0) {
        int maxScore=INT_MIN;
        for (int c=0;c<7;++c) {
            if (tabla[0][c]=='A'||tabla[0][c]=='R') {
                char copia[6][7];
                for(int f1=0;f1<6;f1++){
                  for(int c1=0;c1<7;c1++){
                      copia[f1][c1]=tabla[f1][c1];}}
                añadirFicha(copia,c,turno);
                int score = minimaxAB(copia,profundidad- 1,alfa,beta,1);
                if(score>maxScore){
                    maxScore=score;
                }
                if(alfa>score){
                    alfa=score;
                }
                if(beta<=alfa){
                    break;
                }
            }
        }

        return maxScore;
    } else {
        int minScore=INT_MAX;
        for (int c=0;c<7;++c) {
            if (tabla[0][c]==' ') {
                char copia[6][7];
                for(int f1=0;f1<6;f1++){
                  for(int c1=0;c1<7;c1++){
                      copia[f1][c1]=tabla[f1][c1];}}
                añadirFicha(copia,c,turno+1);
                int score= minimaxAB(copia,profundidad-1,alfa,beta,0);
                if(beta>score){
                    beta=score;
                }
                if(score<minScore){
                    minScore=score;
                }
                if(beta<=alfa){
                    break;
                }
            }
        }

        return minScore;
    }
}
int tablero::mejorColAB(char tabla[6][7],int dificultad){
    int mejorScore=INT_MIN;
    int mejorCol=-1;
    int alfa=INT_MIN;
    int beta=INT_MAX;
    for (int c=0; c<7; ++c) {
        if (tabla[0][c]==' ') {
            char copia[6][7];
                for(int f1=0;f1<6;f1++){
                  for(int c1=0;c1<7;c1++){
                      copia[f1][c1]=tabla[f1][c1];}}
            añadirFicha(copia,c,1);
            int colScore= minimaxAB(copia,dificultad-1,alfa,beta,0);
            if (colScore>mejorScore) {
                mejorCol=c;
                mejorScore= colScore;
            }
            if(alfa>mejorScore){
                alfa=mejorScore;
            }
        }
    }
    return mejorCol;
}
