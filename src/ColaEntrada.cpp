#pragma once
#include "Cola.h"
#include "sync.h"
#include <vector>
#include <string>
#include "EvaluadorExamenes.h"

using namespace std;

class ColaEntrada:public Cola
{  
  public:
  
  EvaluadorExamenes evaluador;

  ColaEntrada(){
      pthread_create("colaEntrada", NULL, diferenciar, NULL; //pasar cola como argumento
  }

  void diferenciar(){
      string examen = data.pop_back();
      string tipo = "";
      if (examen.contains("B")){
          tipo = "blood";
      }
      evaluador->meterExamen(tipo, examen)
  }
};