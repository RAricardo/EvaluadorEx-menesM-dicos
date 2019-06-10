#pragma once
#include "Cola.h"
#include "Memoria.h"
#include <vector>

using namespace std;

class ColaInterna: public Cola {

  private:
    vector<struct examen> examenes;
  public:
  ColaInterna(char tipo, int n_cola, int q);
  void enqueue(struct examen examen);
};