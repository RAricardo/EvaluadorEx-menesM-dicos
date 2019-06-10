#include "ColaInterna.h"
#include "Evaluador.h"
#include <vector>
#include <string>

using namespace std;

extern ColaSalida*sal;

ColaInterna::ColaInterna(char tipo, int n_cola, int q, char * n):
    Cola(tipo, n_cola, q, n), examenes (vector<examen>())
{
    thread hilo_Cola(&ColaInterna::procesar, this);
}

void ColaInterna::procesar()
{

    while (!examenes.empty())
    {

        examen examen = examenes.back();
        examenes.pop_back();
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
                reactivo = (double)rand() / (double)RAND_MAX * (25 - 8) + 8;
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
            sal->meter(examen);
        }
    }
}

void ColaInterna::enqueue(examen examen)
{
    vacios->wait();
    mutex->wait();
    examenes.push_back(examen);
    mutex->signal();
    vacios->signal();
}