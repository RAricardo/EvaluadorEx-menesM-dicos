#include "Memoria.h"
#include "ColaSalida.h"
#include <iostream>
#include <ctime>

using namespace std;

ColaSalida::ColaSalida(int oe):
    tipo('s'), n_cola(0), n(oe), reportes(new vector<examen>())
{}

void ColaSalida::meter(examen examen){

    reportes.push_back(examen);

}

void ColaSalida::imprimirCantidad(int num){

    int i = 0;

    while(i < num){

        llenos.wait();
        mutex.wait();
        examen reporte = reportes.pop_back();  
        mutex.signal();
        llenos.signal();

        cout << reporte.id + " " + reporte.i + " " + reporte.r << endl;
        i++;    
    }

}

void ColaSalida::imprimirTiempo(int segundos){

    clock_t begin = clock();

    while((clock() - begin) < segundos){

        llenos.wait();
        mutex.wait();
        examen reporte = reportes.pop_back();  
        mutex.signal();
        llenos.signal();

        cout << reporte.id + " " + reporte.i + " " + reporte.r << endl;
        
    }
}