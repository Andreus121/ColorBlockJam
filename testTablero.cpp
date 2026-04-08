#include <iostream>
#include <string>
#include "Tablero.h"

int main(){
    // crear piezas
    u_int8_t geometria1[4] = {1, 0, 1, 1}; // Ejemplo de geometría
    Pieza* pieza1 = new Pieza(1, 2, 2, 2, 0, 0, geometria1);

    Pieza* piezas[1] = {pieza1};

    // crear tablero
    Tablero* tablero = new Tablero(7, 7, *piezas);

    tablero->imprimirTablero();

    std::cout <<"hola"<<std::endl;

    // agregar piezas al tablero
    tablero->agregarPieza(*pieza1);
    std::cout <<"hola"<<std::endl;
    tablero->imprimirTablero();

    return 1;
}

