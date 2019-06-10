#include "Evaluador.h"

void Evaluador::init(char* n, int i, int ie, int oe, int b, int d, int s, int q)
{
    for (int c = 0; c<i; ++c){
          new ColaEntrada(c, ie, q, n);
    }
    sal = new ColaSalida(oe, n);

    int fd = shm_open(n, O_RDWR | O_CREAT | O_EXCL, 0660);

    if (fd < 0)
    {
        cerr << "Error creando la memoria compartida: "
             << errno << strerror(errno) << endl;
        exit(1);
    }

    if (ftruncate(fd, sizeof(struct Memoria)) != 0)
    {
        cerr << "Error creando la memoria compartida: "
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

    pMemoria->i = i;
    pMemoria->ie = ie;
    pMemoria->oe = oe;
    pMemoria->b = b;
    pMemoria->d = d;
    pMemoria->s = s;
    pMemoria->q = q;
    pMemoria->c_id = 0;
    pMemoria->entra = 0;
    pMemoria->tamano = N_BUFFER;

    close(fd);

}