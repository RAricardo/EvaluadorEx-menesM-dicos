#include "Cola.h"
#include "sync.h"
#include <vector>
#include <string>

using namespace std;

Cola::Cola(char tipo, int n_cola, int n, char * nombre_mem):
nombre_mem(nombre_mem)
{
    llenos = Sync::create(tipo + n_cola + "llenos");
    vacios = Sync::create(tipo + n_cola + "vacios", n);
    mutex = Sync::create(tipo + n_cola + "mutex", 1);
}


