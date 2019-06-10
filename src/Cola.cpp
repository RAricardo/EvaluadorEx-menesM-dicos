#include "Cola.h"
#include "sync.h"
#include <vector>
#include <string>
#include "MemoryManager.h"
#include <iostream>
#include <sstream>

using namespace std;

Cola::Cola(char tipo, int n_cola, int n, char * nombre_mem):
tipo(tipo),n_cola(n_cola), n(n),
nombre_mem(nombre_mem)
{
    stringstream sstmL;
    sstmL << tipo << n_cola << "llenos";
    string ansllenos = sstmL.str();
    char * ansllenos2 = (char *) ansllenos.c_str();
    llenos = Sync::create(ansllenos2);

    stringstream sstmV;
    sstmV << tipo << n_cola << "vacios";
    string ansvacios = sstmV.str();
    char * ansvacios2 = (char *) ansvacios.c_str();
    vacios = Sync::create(ansvacios2, n);

    stringstream sstmM;
    sstmM << tipo << n_cola << "mutex";
    string ansmutex = sstmM.str();
    char * ansmutex2 = (char *) ansmutex.c_str();
    mutex = Sync::create(ansmutex2, 1);
}

