#include <iostream>
#include <string>
#include "Tablero.h"

int main(){
    // crear piezas
    u_int8_t geometria1[4] = {1, 0, 1, 1}; // Ejemplo de geometría
    Pieza* pieza1 = new Pieza(1, 'a', 2, 2, 2, 1, geometria1);
    u_int8_t geometria2[6] = {1,1,1,0,1,1};
    Pieza* pieza2 = new Pieza(2,'b',2,3,3,3,geometria2);
    u_int8_t geometria3[6] = {1,1,1,1,0,1};
    Pieza* pieza3 = new Pieza(2,'c',3,2,7,4,geometria3);
    
    // Crear array de piezas dinámicamente (en HEAP)
    Pieza** piezas = new Pieza*[3];
    piezas[0] = pieza1;
    piezas[1] = pieza2;
    piezas[2] = pieza3;

    // crear tablero vacío
    Tablero* tablero = new Tablero(10, 10);
    tablero->imprimirTablero();

    // agregar paredes al tablero
    char* paredes[10] = {};
    for(int i=0; i<10; i++){
        paredes[i] = new char[10];
        for(int j=0; j<10; j++){
            if(i==0 || i==9 || j==0 || j==9){
                paredes[i][j] = '#';
            }else{
                paredes[i][j] = ' ';
            }
        }
    }

    tablero->agregarParedes(paredes);
    std::cout <<"Se agregan las paredes al tablero"<<std::endl;
    tablero->imprimirTablero();
    
    //agregar salidas al tablero
    Salida* salida1 = new Salida('a',2,0,'H', 2);
    Salida* salida2 = new Salida('b',0,3,'V', 3);
    Salida* salida3 = new Salida('c',9,1,'V', 5);
    Salida** salidas = new Salida*[3];
    salidas[0] = salida1;
    salidas[1] = salida2;
    salidas[2] = salida3;
    tablero->agregarSalidas(salidas, 3);
    std::cout <<"Se agregan las salidas al tablero"<<std::endl;
    tablero->imprimirTablero();

    // agregar piezas al tablero
    std::cout <<"Se agregan las piezas"<<std::endl;
    tablero->agregarPiezas(piezas, 3);
    tablero->imprimirTablero();

    delete tablero;  // Libera cuadricula Y el array de piezas
    return 0;
}

