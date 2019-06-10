#pragma once
#include <vector>
#include "Cola.h"

class ColaSalida: public Cola {

    public: 
        vector<struct examen> reportes;
        ColaSalida(int oe, char * n);
        void meter(struct examen examen);
        void imprimirCantidad(int num);
        void imprimirTiempo(int segundos);

};