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
#include <cstring>
#include "Memoria.h"

class MemoryManager {
    public:
    static struct Memoria* openMemory(char* name);
};