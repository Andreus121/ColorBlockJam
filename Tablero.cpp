#include <iostream>
#include <string>
#include "Tablero.h"

Tablero::Tablero(int ancho, int alto,Pieza* piezas){
    this->ancho = ancho;
    this->alto = alto;
    this->piezas = piezas;
    // crear matriz vacía con las medidas dadas
    this->cuadricula = new char*[ancho];
    for (size_t i = 0; i < ancho; i++){
        cuadricula[i] = new char[alto];
        for (size_t j = 0; j < alto; j++){
            cuadricula[i][j] = '-';
        }
    }
    
}

void Tablero::agregarPieza(Pieza pieza){
    // agregar la pieza a la matriz
    for (int i = 0; i < pieza.ancho*pieza.alto; i+=pieza.ancho) {
        for(int j = 0; j < pieza.alto; j++) {
            std::cout <<"adios"<<std::endl;
            if((int)pieza.geometria[i + j] == 1) {
                
            }
        }
    }
}

void Tablero::imprimirTablero(){
    for (int i = 0; i < alto; i++){
        for (int j = 0; j < ancho; j++){
            std::cout << cuadricula[j][i];
        }
        std::cout << std::endl;
    }
}