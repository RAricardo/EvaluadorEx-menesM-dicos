#pragma once
#include <pthread.h>
#include "sync.h"
#include <string>
#include <cstring>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include "Memoria.h"
#include <thread>

using namespace std;

class Cola
{

public:
  char tipo;
  int n_cola;
  int n;
  char * nombre_mem;
  ISync *llenos;
  ISync *vacios;
  ISync *mutex;

  Cola(char tipo, int n_cola, int n, char * nombre_mem);
};