#include <iostream>
#include "Camino.h"
#include "Parser.h"

int main(){
    std::cout << "--- Prueba 1: camino vacio ---" << std::endl;
    Camino* c = new Camino(4);
    std::cout << "cantidad: " << c->cantidad << std::endl;
    std::cout << "imprimir -> "; c->imprimir();

    std::cout << "\n--- Prueba 2: agregar y compactar ---" << std::endl;
    //simulamos lo que haria A*: agrega 3 movimientos R del bloque 0
    c->agregar(Movimiento(0, 'R', 1));
    c->agregar(Movimiento(0, 'R', 1));
    c->agregar(Movimiento(0, 'R', 1));
    std::cout << "tras 3 R del bloque 0 (esperado: R1,3): ";
    c->imprimir();

    std::cout << "\n--- Prueba 3: secuencia mixta ---" << std::endl;
    Camino* c2 = new Camino();
    //R1,2 D2,1 R1,10 del enunciado en formato interno:
    c2->agregar(Movimiento(0, 'R', 1));  // R1,1
    c2->agregar(Movimiento(0, 'R', 1));  // R1,1 (fusiona con el anterior -> R1,2)
    c2->agregar(Movimiento(1, 'D', 1));  // D2,1
    for(int i = 0; i < 10; i++){
        c2->agregar(Movimiento(0, 'R', 1)); // R1,10
    }
    std::cout << "esperado: R1,2 D2,1 R1,10 -> ";
    c2->imprimir();

    std::cout << "\n--- Prueba 4: parsear desde string ---" << std::endl;
    Camino* c3 = new Camino();
    const char* secuencia = "R1,2D2,1R1,10";
    bool ok = c3->parsearDesdeString(secuencia);
    std::cout << "parsear '" << secuencia << "' -> " << (ok ? "OK" : "ERROR") << std::endl;
    std::cout << "cantidad de movimientos expandidos: " << c3->cantidad << " (esperado 13)" << std::endl;
    std::cout << "reimprimir (debe volver a compactar): ";
    c3->imprimir();

    std::cout << "\n--- Prueba 5: parsear string invalido ---" << std::endl;
    Camino* c4 = new Camino();
    std::cout << "parsear 'X1,2' -> " << (c4->parsearDesdeString("X1,2") ? "OK" : "ERROR") << std::endl;
    std::cout << "parsear 'R,2'  -> " << (c4->parsearDesdeString("R,2") ? "OK" : "ERROR") << std::endl;
    std::cout << "parsear 'R1'   -> " << (c4->parsearDesdeString("R1") ? "OK" : "ERROR") << std::endl;
    std::cout << "parsear ''     -> " << (c4->parsearDesdeString("") ? "OK" : "ERROR") << std::endl;
    std::cout << "(el vacio es OK: camino de 0 movimientos)" << std::endl;

    std::cout << "\n--- Prueba 6: aplicar camino a tablero real ---" << std::endl;
    Parser* p = new Parser();
    if(!p->cargar("Ejemplo1.txt")){
        std::cout << "no se cargo ejemplo1.txt, omitiendo" << std::endl;
    } else {
        Tablero* t = new Tablero(p->staticData, p->bloques, p->salidas, p->compuertas);
        Camino* sol = new Camino();
        sol->parsearDesdeString("R1,1"); //la solucion de SIMPLE1
        sol->aplicar(t);
        delete sol;

        //limpiar
        StaticData* sd = t->staticData;
        delete t;
        if(sd->paredesTablero){
            for(int i = 0; i < sd->altoTablero; i++) delete[] sd->paredesTablero[i];
            delete[] sd->paredesTablero;
        }
        delete[] sd->coloresBloques; delete[] sd->anchoBloques; delete[] sd->altoBloques;
        if(sd->geometriaBloques){
            for(int i = 0; i < sd->cantidadBloques; i++) delete[] sd->geometriaBloques[i];
            delete[] sd->geometriaBloques;
        }
        delete[] sd->xSalidas; delete[] sd->ySalidas; delete[] sd->coloresSalidas;
        delete[] sd->orientacionSalidas; delete[] sd->largoISalidas;
        delete[] sd->largoFSalidas; delete[] sd->pasosSalidas;
        delete[] sd->xCompuertas; delete[] sd->yCompuertas;
        delete[] sd->colorICompuertas; delete[] sd->colorFCompuertas;
        delete[] sd->pasosCompuertas;
        delete sd;
    }
    delete p;

    delete c; delete c2; delete c3; delete c4;
    std::cout << "\nOK" << std::endl;
    return 0;
}