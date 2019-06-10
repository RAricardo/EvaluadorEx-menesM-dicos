#pragma once
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
#include "ColaEntrada.h"
#include "ColaSalida.h"

using namespace std;

class Evaluador {
  public:
    static void init(char* n, int i, int ie, int oe, int b, int d, int s, int q);
    static struct Memoria* openMemory(char* name);
    static void update(char *n, char tipo, int carga);
};

extern ColaSalida* sal;