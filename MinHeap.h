#pragma once
#include "Tablero.h"

/*
MinHeap: cola de prioridad implementada como heap binario sobre arreglo.
Guarda punteros a Tablero con una prioridad entera (f = g + h en A*).
El tablero con MENOR prioridad siempre queda en la cima (raíz).

Complejidad:
- push: O(log n)
- pop:  O(log n)
- peek: O(1)

El heap no es dueño de los tableros: no los libera en su destructor,
solo libera su arreglo interno. Quien los sacó con pop() es el nuevo
dueño y debe liberarlos (o pasarlos a otra estructura, como el ClosedSet).
*/
class MinHeap {
    public:
    //entrada del heap: un tablero con su prioridad
    struct Entrada {
        Tablero* tablero;
        int prioridad;
    };

    Entrada* datos;   //arreglo dinámico (el heap vive aquí)
    int largo;     //cuántas entradas hay
    int capacidad;    //tamaño actual del arreglo

    MinHeap(int capacidadInicial = 64);//empieza con un tamaño base
    ~MinHeap();//destructor, no elimina los punteros que contiene

    //inserta un tablero con su prioridad. O(log n).
    void push(Tablero* tablero, int prioridad);

    //retorna y elimina el tablero con menor prioridad.
    //Si el heap está vacío retorna nullptr.
    //El llamador se convierte en dueño del tablero retornado.
    Tablero* pop();

    //retorna el tablero con menor prioridad sin eliminarlo.
    //Si el heap está vacío retorna nullptr.
    Tablero* peek();

    bool vacio();

    //cantidad de elementos actual
    int tamano();

    private:
    //funciones auxiliares
    void duplicarCapacidad();//en caso de que llegué al limite
    void siftUp(int i);//subir una pieza hasta que sea mayor o igual a sus padres
    void siftDown(int i);//bajar una pieza hasta que sea menor o igual a sus hijos
};