#pragma once
#include "Cola.h"
#include "sync.h"
#include <vector>
#include "elements.h"
#include <string>

using namespace std;

class Cola
{
    
  public:
  
  ISync llenos;
  ISync vacios;
  ISync mutex;


  Cola(int n){

      llenos = Sync::create("llenos");
      vacios = Sync::create("vacios", n);
      mutex = Sync::create("mutex", 1);
  }

void meter(string examen){

    vacios.wait();
    mutex.wait();

    mem->meter();

    mutex.signal();
    llenos.signal();

}

string sacar(){

    llenos.wait();
    mutex.wait();

    mem->sacar();

    mutex.signal();
    vacios.signal();
    
    return res;
}
};