#include "MinHeap.h"

//constructor
MinHeap::MinHeap(int capacidadInicial){
    if(capacidadInicial < 1) capacidadInicial = 1;
    this->capacidad = capacidadInicial;
    this->largo = 0;
    this->datos = new Entrada[this->capacidad];
}

MinHeap::~MinHeap(){
    //el heap NO libera los Tablero* contenidos
    delete[] this->datos;
}

//Duplica el arreglo interno cuando se llena.
//Complejidad O(n), pero amortizada sobre muchos push queda en O(1) por push.
void MinHeap::duplicarCapacidad(){
    int nuevaCapacidad = this->capacidad * 2;
    Entrada* nuevos = new Entrada[nuevaCapacidad];
    for(int i = 0; i < this->largo; i++){
        nuevos[i] = this->datos[i];
    }
    delete[] this->datos;
    this->datos = nuevos;
    this->capacidad = nuevaCapacidad;
}

//Hace "subir" el elemento en la posicion i hasta que sea mayor o igual
//que su padre. Usado tras insertar al final.
void MinHeap::siftUp(int i){
    while(i > 0){
        int padre = (i - 1) / 2;
        if(this->datos[i].prioridad < this->datos[padre].prioridad){
            //intercambiar con el padre
            Entrada tmp = this->datos[i];
            this->datos[i] = this->datos[padre];
            this->datos[padre] = tmp;
            i = padre;
        } else {
            break;
        }
    }
}

//Hace "bajar" el elemento en la posicion i hasta que sea menor o igual
//que sus hijos. Usado tras poner el último elemento en la raíz para pop.
void MinHeap::siftDown(int i){
    while(true){
        int hijoIzq = 2 * i + 1;
        int hijoDer = 2 * i + 2;
        int menor = i;

        if(hijoIzq < this->largo && this->datos[hijoIzq].prioridad < this->datos[menor].prioridad){
            menor = hijoIzq;
        }
        if(hijoDer < this->largo && this->datos[hijoDer].prioridad < this->datos[menor].prioridad){
            menor = hijoDer;
        }
        if(menor == i) break; //ya está en su lugar

        //intercambiar con el hijo menor
        Entrada tmp = this->datos[i];
        this->datos[i] = this->datos[menor];
        this->datos[menor] = tmp;
        i = menor;
    }
}

//agregar un elemento
void MinHeap::push(Tablero* tablero, int prioridad){
    if(this->largo == this->capacidad){
        duplicarCapacidad();
    }
    //insertar al final
    this->datos[this->largo].tablero = tablero;
    this->datos[this->largo].prioridad = prioridad;
    this->largo++;
    //subirlo hasta que llegue a su lugar indicado, mantener el orden
    siftUp(this->largo - 1);
}

//sacar la cabeza del heap
Tablero* MinHeap::pop(){
    if(this->largo == 0) return nullptr;

    //la raíz (indice 0) es el menor
    Tablero* resultado = this->datos[0].tablero;

    this->largo--;
    if(this->largo > 0){
        //mover el último elemento a la raíz y hacerlo bajar
        this->datos[0] = this->datos[this->largo];
        siftDown(0);
    }
    return resultado;
}

//retornar el puntero de la cabeza del heap
Tablero* MinHeap::peek(){
    if(this->largo == 0) return nullptr;
    return this->datos[0].tablero;
}

//verificar si está vacio
bool MinHeap::vacio(){
    return this->largo == 0;
}

//ver el tamaño del heaṕ
int MinHeap::tamano(){
    return this->largo;
}