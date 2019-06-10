#include "Memoria.h"
#include "ColaSalida.h"
#include <iostream>
#include <ctime>

using namespace std;

ColaSalida::ColaSalida(int oe, char * n):
Cola('s', 0, oe, n), reportes(vector<examen>())
{}

void ColaSalida::meter(examen examen){

    reportes.push_back(examen);

}

void ColaSalida::imprimirCantidad(int num){

    int i = 0;

    while(i < num){

        llenos->wait();
        mutex->wait();
        examen reporte = reportes.back();  
        reportes.pop_back();
        mutex->signal();
        llenos->signal();

        cout << reporte.id << " " << reporte.i << " " << reporte.r << endl;
        i++;    
    }

}

void ColaSalida::imprimirTiempo(int segundos){

    clock_t begin = clock();

    while((clock() - begin) < segundos){

        llenos->wait();
        mutex->wait();
        examen reporte = reportes.back();  
        reportes.pop_back();
        mutex->signal();
        llenos->signal();

        cout << reporte.id << " " << reporte.i << " " << reporte.r << endl;
        
    }
}