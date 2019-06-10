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

using namespace std;

class Evaluador {

  private:

  public:
    void init(char* n, int i, int ie, int oe, int b, int d, int s, int q);
};