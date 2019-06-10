#pragma once
#include "Cola.h"
#include "ColaInterna.h"
#include "Memoria.h"
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



class ColaEntrada: public Cola {
  private:
    int ie; //tamaño colas de entrada
     ColaInterna cib;
     ColaInterna cid;
     ColaInterna cis;
  public:
     ColaEntrada(int n_cola, int ie, int q, char*nombre_mem);
     struct examen sacar();
     void meter(int c_entrada, char tipo, int cantidad, char*n);
     void diferenciar();
};