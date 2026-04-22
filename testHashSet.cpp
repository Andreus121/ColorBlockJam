#include <iostream>
#include "Parser.h"
#include "Tablero.h"
#include "HashSet.h"

//helper: crea un tablero cargado desde Ejemplo1.txt
Tablero* crearTableroInicial(){
    Parser* p = new Parser();
    if(!p->cargar("Ejemplo1.txt")){
        std::cout << "No se pudo cargar Ejemplo1.txt. Ejecutar desde el directorio correcto." << std::endl;
        delete p;
        return nullptr;
    }
    Tablero* t = new Tablero(p->staticData, p->bloques, p->salidas, p->compuertas);
    delete p; //p ya no es dueño (entrego a t)
    return t;
}

int main(){
    std::cout << "--- Prueba 1: HashSet vacio ---" << std::endl;
    HashSet* set = new HashSet(7);
    std::cout << "tamano: " << set->tamano() << std::endl;
    Tablero* t1 = crearTableroInicial();
    if(!t1){ delete set; return 1; }
    std::cout << "contiene(t1)? " << (set->contiene(t1) ? "Si" : "No") << std::endl;

    std::cout << "\n--- Prueba 2: insertar y consultar ---" << std::endl;
    bool ins1 = set->insertar(t1);
    std::cout << "insertar(t1) -> " << (ins1 ? "insertado" : "ya estaba") << std::endl;
    std::cout << "tamano: " << set->tamano() << std::endl;
    std::cout << "contiene(t1)? " << (set->contiene(t1) ? "Si" : "No") << std::endl;

    std::cout << "\n--- Prueba 3: insertar duplicado (mismo objeto) ---" << std::endl;
    bool ins2 = set->insertar(t1);
    std::cout << "insertar(t1) de nuevo -> " << (ins2 ? "insertado" : "ya estaba") << std::endl;
    std::cout << "tamano: " << set->tamano() << std::endl;

    std::cout << "\n--- Prueba 4: insertar un clon (distinto objeto, MISMO estado) ---" << std::endl;
    Tablero* gemelo = t1->clonar();
    std::cout << "contiene(gemelo)? " << (set->contiene(gemelo) ? "Si" : "No") << std::endl;
    bool ins3 = set->insertar(gemelo);
    std::cout << "insertar(gemelo) -> " << (ins3 ? "insertado" : "ya estaba") << std::endl;
    std::cout << "tamano: " << set->tamano() << std::endl;
    //gemelo NO fue insertado porque era igual al t1; hay que liberarlo manualmente
    delete gemelo;

    std::cout << "\n--- Prueba 5: insertar un tablero distinto ---" << std::endl;
    //movemos un clon de t1 para que sea un estado distinto y lo metemos
    Tablero* movido = t1->clonar();
    movido->moverBloque(0, 'L'); //ahora es un estado diferente
    std::cout << "contiene(movido)? " << (set->contiene(movido) ? "Si" : "No") << std::endl;
    bool ins4 = set->insertar(movido);
    std::cout << "insertar(movido) -> " << (ins4 ? "insertado" : "ya estaba") << std::endl;
    std::cout << "tamano: " << set->tamano() << std::endl;

    std::cout << "\n--- Prueba 6: stress - insertar muchos estados ---" << std::endl;
    //generar muchos vecinos y meterlos al set
    int total = 0, duplicados = 0;
    //desde t1 generamos vecinos, y desde cada vecino generamos más, etc.
    //hacemos una pequeña BFS manual de profundidad 3 sin optimizar
    //(solo para ver cómo se comporta el HashSet con muchas inserciones)
    Tablero* actuales[200];
    int nActuales = 1;
    actuales[0] = t1;

    for(int nivel = 0; nivel < 3 && nActuales > 0; nivel++){
        Tablero* siguientes[500];
        int nSig = 0;
        for(int i = 0; i < nActuales && nSig < 490; i++){
            int nv;
            Tablero** vecinos = actuales[i]->generarVecinos(nv);
            for(int v = 0; v < nv && nSig < 490; v++){
                if(set->insertar(vecinos[v])){
                    total++;
                    siguientes[nSig++] = vecinos[v];
                } else {
                    duplicados++;
                    delete vecinos[v]; //no va al set, lo liberamos
                }
            }
            delete[] vecinos;
        }
        for(int i = 0; i < nSig; i++) actuales[i] = siguientes[i];
        nActuales = nSig;
    }
    std::cout << "Estados nuevos insertados: " << total << std::endl;
    std::cout << "Duplicados detectados (no insertados): " << duplicados << std::endl;
    std::cout << "tamano final del set: " << set->tamano() << std::endl;
    std::cout << "numBuckets final: " << set->capacidad << std::endl;
    std::cout << "(factor de carga: " << (double)set->cantidad / set->capacidad << ")" << std::endl;

    //limpiar: el HashSet libera sus tableros. Solo liberamos staticData.
    StaticData* sd = t1->staticData;
    delete set;
    //staticData se libera aparte
    if(sd->paredesTablero){
        for(int i = 0; i < sd->altoTablero; i++) delete[] sd->paredesTablero[i];
        delete[] sd->paredesTablero;
    }
    delete[] sd->coloresBloques;
    delete[] sd->anchoBloques;
    delete[] sd->altoBloques;
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

    std::cout << "\nOK" << std::endl;
    return 0;
}