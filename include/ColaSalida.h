#pragma once
#include "Cola.h"
#include <vector>

using namespace std;

class ColaSalida: public Cola {

    public: 
        vector<struct examen> reportes;
        ColaSalida(int oe);
        void imprimirCantidad(int num);
        void imprimirTiempo(int segundos);

};