#pragma once
#include "Tablero.h"

/*
Hash un conjunto de Tablero*

Complejidad:
- insertar: O(1) amortizado
- contiene: O(1) promedio
- tamaño: O(1)

El Hash es dueño de los tableros y los elimina en sus destructor
A* debe reconstruir el camino y después eliminar el Hash
*/
class HashSet {
    public:
    //nodo de la lista enlazada que cuelga de cada bucket
    struct Nodo {
        Tablero* tablero;
        Nodo* siguiente;
    };

    Nodo** lista;   //arreglo de punteros a Nodo (cada posición es la cabeza de una lista)
    int capacidad;   //cuantos espacios tiene la lista (incluso sin tablas)
    int cantidad;     //cuántos tableros hay en total

    HashSet(int capacidadInicial = 101);//constructor con un tamaño base
    ~HashSet();//destructor

    //Inserta un tablero en el set. Si ya había uno igual (esIgual), no inserta.
    //Retorna true si insertó, false si ya estaba.
    bool insertar(Tablero* tablero);

    //verificar si ya existe un tablero igual
    bool contiene(Tablero* tablero);

    //cantidad de tableros en el set
    int tamano();

    private:
    //redimensiona la tabla (aproximadamente al doble) cuando el factor
    //de carga se vuelve alto. Mantiene las operaciones en O(1) amortizado.
    void rehashear();
};