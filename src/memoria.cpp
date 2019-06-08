#pragma once
#include "Cola.h"
#include "sync.h"
#include <vector>
#include <string>
#include "elements.h"

using namespace std;

class Memoria
{
    Memoria::Memoria(int i, int ie, int oe, int b, int d, int s, int q):
        i(i), ie(ie), oe(oe), b(b), d(d), s(s), q(q),
        buffer(new examen[(i * ie) + oe + (q * 3 * i)])
    {}

    void Memoria::meter(){

    }

    void Memoria::sacar(){
        
    }
};