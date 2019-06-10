#include "Cola.h"
#include "sync.h"
#include <vector>
#include <string>

using namespace std;

Cola::Cola(char tipo, int n_cola, int n)
{
    llenos = Sync::create(tipo + n_cola + "llenos");
    vacios = Sync::create(tipo + n_cola + "vacios", n);
    mutex = Sync::create(tipo + n_cola + "mutex", 1);
}

static void meter(int c_entrada, char tipo, int cantidad, string n)
{
    // 2 B 6

    llenos = Sync::open(tipo + n_cola + "llenos");
    vacios = Sync::open(tipo + n_cola + "vacios");
    mutex = Sync::open(tipo + n_cola + "mutex");

    int fd = shm_open(n, O_RDWR, 0660);

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

    int id = pMemoria->c_id;
    int i = c_entrada;  //cola de entrada
    char k = tipo; //tipo de muestra
    int q = cantidad;  //cantidad de muestra
    float p = 0f;//tiempo de procesamiento
    char r = '?'; //resultado
    char e = "W"; //estado

    vacios.wait();
    mutex.wait();

    pMemoria->examenes[pMemoria->entra].id = id;
    pMemoria->examenes[pMemoria->entra].i = i;
    pMemoria->examenes[pMemoria->entra].k = k;
    pMemoria->examenes[pMemoria->entra].q = q;
    pMemoria->examenes[pMemoria->entra].p = p;
    pMemoria->examenes[pMemoria->entra].r = r;
    pMemoria->examenes[pMemoria->entra].e = e;

    pMemoria->entra = (pMemoria->entra + 1) % pMemoria->tamano;
    pMemoria->cantidad++;

    mutex.signal();
    llenos.signal();
}

