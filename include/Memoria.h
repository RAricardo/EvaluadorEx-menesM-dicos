#pragma once
#include "ColaEntrada.h"
#include "ColaSalida.h" 

using namespace std;

#define N_BUFFER 1000000

struct examen {
    int id; //identificador de examen
    int i;  //cola de entrada
    char k; //tipo de muestra
    int q;  //cantidad de muestra
    float p;//tiempo de procesamiento
    char r; //resultado
    char e; //estado

    examen(int id, int i, char k, int q, float p, char r, char e);
};

struct Memoria{
      int i; //Cantidad de colas de entrada
      int ie; //tamaño colas de entrada
      int oe; //tamaño de la cola de salida
      int b;  //reactivo sangre
      int d;  //reactivo detrito
      int s;  //reactivo piel
      int q;  //tamaño colas internas
      int c_id;  //contador de id

      struct examen examenes[N_BUFFER];
      Memoria(int i, int ie, int oe, int b, int d, int s, int q);
};

extern Memoria* mem;