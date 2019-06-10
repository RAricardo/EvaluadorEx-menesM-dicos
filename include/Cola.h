#pragma once
#include <pthread.h>
#include "sync.h"
#include <stdio.h>

using namespace std;

class Cola
{

public:
  char tipo;
  int n_cola;
  int n;
  ISync *llenos;
  ISync *vacios;
  ISync *mutex;

  Cola(char tipo, int n_cola, int n);
  void meter();
  struct examen sacar();
};