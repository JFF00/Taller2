using namespace std;
#include <iostream>
#pragma once
class tablero{
    public:
     char tabla[6][7];
     //funcion que retorna el numero de fila disponible dentro de una columna, simula gravedad
     int añadirFicha(char tabla[6][7],int columna,int color);
     void printTablero();
     tablero();
     //funcion que juega contra IA
     void jugarvsIA();    
     //funcion que juega contra un segundo jugador
     void jugarvsPlayer();
     //checkwin retorna verdadero si alguna de las condiciones de victoria se dan
     bool checkWin(char tabla[6][7],int turno);
     //funcion que retorna el puntaje actual del tablero.
     int puntajeActual(char copia[6][7]);
     //boolean que retorna si el estado del tablero es una hoja(dentro del arbol). Si es empate, victoria de alguno.
     bool esHoja(char tabla[6][7]);
     //int que retorna mejor puntaje dentro del recorrido del arbol
     int minimax(char tabla[6][7],int profundidad,int turno);
     int minimaxAB(char tabla[6][7],int profundidad,int alfa,int beta,int turno);//alfa beta
     //retorna mejor columna a partir de minimax
     int mejorColAB(char tabla[6][7],int dificultada);//alfa beta
     int mejorCol(char tabla[6][7],int dificultad);   
     //funciones que guardan y cargan partidas.
     void guardarPartida();
     void cargarPartida(char tabla[6][7]);
     
     
};