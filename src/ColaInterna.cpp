#include "ColaInterna.h"
#include <vector>
#include <string>

using namespace std;

ColaInterna::ColaInterna(char tipo, int n_cola, int q, char * n):
    Cola(tipo, n_cola, q, n)
{
    examenes = new vector<examen>;
    pthread_t hilo_Cola;
    pthread_create(&hilo_Cola, NULL, procesar, NULL);
}

void procesar()
{

    while (!examenes.empty())
    {

        examen examen = examenes.pop_back();
        for (int i = 0; i < examen.q; i++)
        {
            int reactivo;
            if (tipo == 'B')
            {
                reactivo = (double)rand() / (double)RAND_MAX * (7 - 1) + 1;
            }
            else if (tipo == 'D')
            {
                reactivo = (double)rand() / (double)RAND_MAX * (20 - 5) + 5;
            }
            else if (tipo == 'S')
            {
                int reactivo = (double)rand() / (double)RAND_MAX * (25 - 8) + 8;
            }

            int res = (double)rand() / (double)RAND_MAX * 50;
            char resultado = '?';
            if (res > 15)
            {
                resultado = 'N';
                if (res > 35)
                {
                    resultado = 'P';
                }
            }

            examen.r = resultado;

            ColaSalida->meter(examen, reactivo);
        }
    }
}

void enqueue(examen examen)
{
    vacios.wait();
    mutex.wait();
    examenes.push_back(examen);
    mutex.signal();
    vacios.signal();
}