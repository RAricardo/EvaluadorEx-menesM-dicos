#include "ColaEntrada.h"
#include "sync.h"
#include <vector>
#include <string>

ColaEntrada::ColaEntrada(int n_cola, int ie, int q):
    Cola('E', n_cola, ie), cib(new ColaInterna('B', n_cola, q)),
    cid(new ColaInterna('D', n_cola, q)), cis(new ColaInterna('S', n_cola, q))
{
    pthread_t hilo_Cola;
    pthread_create(&hilo_Cola, NULL, diferenciar, (void *)n); //pasar cola como argumento
}

void ColaEntrada::diferenciar(void * n)
{
    for (;;){

        examen examen = sacar((char*)n);
        if(examen.k == 'B'){

            cib->enqueue(examen);

        } else if(examen.k == 'D'){
            
            cid->enqueue(examen);

        } else if(examen.k == 'S'){

            cis->enqueue(examen);

        }
    }
}

examen ColaEntrada::sacar(char * n){

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

    llenos->wait();
    mutex->wait();
    //Cola Entrada 1
    int index = 0;

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