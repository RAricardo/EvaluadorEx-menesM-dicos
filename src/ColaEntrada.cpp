#include "ColaEntrada.h"
#include "sync.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

ColaEntrada::ColaEntrada(int n_cola, int ie, int q, char *nombre_mem): 
    Cola('E', n_cola, ie, nombre_mem), cib(ColaInterna('B', n_cola, q, nombre_mem)),
    cid(ColaInterna('D', n_cola, q, nombre_mem)), cis(ColaInterna('S', n_cola, q, nombre_mem))
{
    thread hilo_Cola(&ColaEntrada::diferenciar, this);
    hilo_Cola.detach();
}

void ColaEntrada::diferenciar(){
    for (;;){
        examen examen = sacar();
        if (examen.k == 'B'){
            cib.enqueue(examen);
        }
        else if (examen.k == 'D'){
            cid.enqueue(examen);
        }
        else if (examen.k == 'S'){
            cis.enqueue(examen);
        }
    }
}

examen ColaEntrada::sacar(){
    openSems();

    char ch = '/';
    char chArray[2];
    sprintf(chArray, "%c", ch);
    char * dirname =  strcat(chArray, nombre_mem);

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

    //struct Memoria *pMemoria = MemoryManager::openMemory(nombre_mem);

    llenos->wait();
    mutex->wait();

    int index = 0;
    //pop
    while (pMemoria->examenes[index].i == n_cola){
        index++;
    }

    int id = pMemoria->examenes[index].id;
    int i = pMemoria->examenes[index].i;
    char k = pMemoria->examenes[index].k;
    int q = pMemoria->examenes[index].q;
    float p = pMemoria->examenes[index].p;
    char r = pMemoria->examenes[index].r;
    char e = pMemoria->examenes[index].e;

    mutex->signal();
    vacios->signal();

    examen n_examen = examen(id, i, k, q, p, r, e);

    return n_examen;
}

void ColaEntrada::meter(int c_entrada, char tipo, int cantidad, char *n){
    openSems();

    struct Memoria *pMemoria = MemoryManager::openMemory(n);

    int id = pMemoria->c_id;
    int i = c_entrada; //cola de entrada
    char k = tipo;     //tipo de muestra
    int q = cantidad;  //cantidad de muestra
    float p = 0;       //tiempo de procesamiento
    char r = '?';      //resultado
    char e = 'W';      //estado

    vacios->wait();
    mutex->wait();

    pMemoria->examenes[pMemoria->entra].id = id;
    pMemoria->examenes[pMemoria->entra].i = i;
    pMemoria->examenes[pMemoria->entra].k = k;
    pMemoria->examenes[pMemoria->entra].q = q;
    pMemoria->examenes[pMemoria->entra].p = p;
    pMemoria->examenes[pMemoria->entra].r = r;
    pMemoria->examenes[pMemoria->entra].e = e;

    pMemoria->entra = (pMemoria->entra + 1) % pMemoria->tamano;

    mutex->signal();
    llenos->signal();
}

void ColaEntrada::openSems(){
    stringstream sstmL;
    sstmL <<nombre_mem<< tipo << n_cola << "llenos";
    string ansllenos = sstmL.str();
    char * ansllenos2 = (char *) ansllenos.c_str();
    llenos = Sync::open(ansllenos2);

    stringstream sstmV;
    sstmV <<nombre_mem<< tipo << n_cola << "vacios";
    string ansvacios = sstmV.str();
    char * ansvacios2 = (char *) ansvacios.c_str();
    vacios = Sync::open(ansvacios2);

    stringstream sstmM;
    sstmM <<nombre_mem<< tipo << n_cola << "mutex";
    string ansmutex = sstmM.str();
    char * ansmutex2 = (char *) ansmutex.c_str();
    mutex = Sync::open(ansmutex2);
}