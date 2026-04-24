#pragma once
#include "Movimiento.h"
#include "Tablero.h"

/*
Camino se encarga de tener la secuencia de movimientos de un tablero
considerando movimientos individuales pero mostrarlos de manera compacta.
reconstruye el camino y parsea secuencia de movimientos
*/
class Camino {
    public:
    Movimiento* movimientos;//arreglo dinamico de movimientos
    int cantidad;//cuantos movimientos guardados
    int capacidad;//tamaño del arreglo (crece al duplicarse)

    Camino(int capacidadInicial = 16);//constructor
    ~Camino();//destructor libera el arreglo de movimientos

    //agrega un movimiento al final. Crece el arreglo si hace falta.
    void agregar(Movimiento m);

    //imprime la secuencia en formato COMPACTO del enunciado.
    //Movimientos consecutivos del mismo bloque en la misma direccion
    void imprimir();

    //aplica la secuencia a un tablero, imprimiendo el estado tras cada movimiento.
    //el tablero recibido lo va modificando para ver el progreso a tiempo real
    void aplicar(Tablero* tablero, bool mostrarInicial = true);

    //intenta parsear una cadena del usuario tipo "R1,2D2,1R1,10" al Camino.
    //Retorna true si se pudo parsear, false si la cadena no tiene el formato correcto.
    bool parsearDesdeString(const char* s);

    private:
    //auxiliar para aumentar el tamaño
    void duplicarCapacidad();
};