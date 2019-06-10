#include "MemoryManager.h"

Memoria* MemoryManager::openMemory(char* name){
    char ch = '/';
    char chArray[2];
    sprintf(chArray, "%c", ch);
    char * dirname =  strcat(chArray, name);

    int fd = shm_open(dirname, O_RDWR, 0660);

    if (fd < 0)
    {
        cerr << "Error abriendo la memoria compartida: "
             << errno << strerror(errno) << endl;
        exit(1);
    }

    void *dir;

    if ((dir = mmap(NULL, sizeof(struct examen), PROT_READ | PROT_WRITE, MAP_SHARED,
                    fd, 0)) == MAP_FAILED)
    {
        cerr << "Error mapeando la memoria compartida: "
             << errno << strerror(errno) << endl;
        exit(1);
    }

    struct Memoria *pMemoria = (struct Memoria *)dir;
    
    return pMemoria;
}

void MemoryManager::unlink(char * name){
    char ch = '/';
    char chArray[2];
    sprintf(chArray, "%c", ch);
    char * dirname =  strcat(chArray, name);
    shm_unlink(dirname);
    
}