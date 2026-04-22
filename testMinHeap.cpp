#include <iostream>
#include "MinHeap.h"

//aplica el push normal pero muestra por consola el tablero afectado
static void pushMostrar(MinHeap* h, int prio){
    Tablero* fake = (Tablero*)(long)prio;
    h->push(fake, prio);
    std::cout << "push(" << prio << "), tamano=" << h->tamano() << std::endl;
}

//aplica el pop normal pero muestra por consola el tablero afectado
static void popMostrar(MinHeap* h){
    Tablero* t = h->pop();
    std::cout << "pop -> prio=" << (long)t << ", tamano=" << h->tamano() << std::endl;
}

int main(){
    std::cout << "--- Prueba 1: heap vacio ---" << std::endl;
    MinHeap* h = new MinHeap(4);
    std::cout << "vacio? " << (h->vacio() ? "Si" : "No") << std::endl;
    std::cout << "pop de heap vacio -> " << (void*)h->pop() << std::endl;
    std::cout << "peek de heap vacio -> " << (void*)h->peek() << std::endl;

    std::cout << "\n--- Prueba 2: orden de extraccion ---" << std::endl;
    //insertamos desordenado, esperamos salida ordenada: 1,3,5,7,9
    pushMostrar(h, 5);
    pushMostrar(h, 9);
    pushMostrar(h, 1);
    pushMostrar(h, 7);
    pushMostrar(h, 3);
    std::cout << "peek -> prio=" << (long)h->peek() << " (debe ser 1)" << std::endl;
    popMostrar(h); popMostrar(h); popMostrar(h); popMostrar(h); popMostrar(h);
    std::cout << "vacio despues de todos los pops? " << (h->vacio() ? "Si" : "No") << std::endl;

    std::cout << "\n--- Prueba 3: crecimiento dinamico (push > capacidad inicial) ---" << std::endl;
    //capacidad inicial 4. Insertamos 10, debe auto-duplicar.
    for(int i = 10; i >= 1; i--) pushMostrar(h, i);
    std::cout << "capacidad actual: " << h->capacidad << std::endl;
    std::cout << "extrayendo todo en orden:" << std::endl;
    while(!h->vacio()) popMostrar(h);

    std::cout << "\n--- Prueba 4: prioridades repetidas ---" << std::endl;
    h->push((Tablero*)1L, 5);
    h->push((Tablero*)2L, 5);
    h->push((Tablero*)3L, 5);
    h->push((Tablero*)4L, 3);
    //esperamos: primero el de prioridad 3, luego los de 5 en algun orden
    popMostrar(h); popMostrar(h); popMostrar(h); popMostrar(h);

    std::cout << "\n--- Prueba 5: prioridades negativas y grandes ---" << std::endl;
    h->push((Tablero*)1L, -50);
    h->push((Tablero*)2L, 1000000);
    h->push((Tablero*)3L, 0);
    h->push((Tablero*)4L, -5);
    //orden esperado: -50, -5, 0, 1000000
    popMostrar(h); popMostrar(h); popMostrar(h); popMostrar(h);

    delete h;
    std::cout << "\nOK" << std::endl;
    return 0;
}