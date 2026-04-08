#include <iostream>
#include <string>
#include "Pieza.h"

int main() {
    // Crear una pieza de ejemplo
    u_int8_t geometria1[4] = {1, 0, 1, 1}; // Ejemplo de geometría
    Pieza* pieza1 = new Pieza(1, 2, 2, 2, 0, 0, geometria1);

    // Imprimir la pieza
    pieza1->imprimirPieza();

    u_int8_t geometria2[6] = {1, 1, 1, 1, 0, 1}; // Ejemplo de geometría
    Pieza* pieza2 = new Pieza(1, 5, 3, 2, 0, 0, geometria2);

    // Imprimir la pieza
    pieza2->imprimirPieza();

    return 0;
}