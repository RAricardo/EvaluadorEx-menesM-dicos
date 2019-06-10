#pragma once
#include "Cola.h"
#include "ColaInterna.h"

#include <string>
#include <cstring>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include<cstring>
#include "Memoria.h"

using namespace std;

class ColaEntrada: public Cola {
  private:
    int ie; //tamaño colas de entrada
     ColaInterna *cib;
     ColaInterna *cid;
     ColaInterna *cis;
  public:
     ColaEntrada(int n_cola, int ie, int q);
     struct examen sacar(char * n);
     void diferenciar(void * n);
};