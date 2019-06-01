#pragma once
#include "Cola.h"
#include "sync.h"
#include <vector>
#include <string>

using namespace std;

class Cola
{
    
  public:
  
  ISync llenos;
  ISync vacios;
  ISync mutex;
  vector<string> data;
  int n;

  Cola(int n){

      llenos = Sync::create("llenos");
      vacios = Sync::create("vacios");
      mutex = Sync::create("mutex");
      this->n = n;
  }

void meter(string examen){

    vacios.wait();
    mutex.wait();

    data.push_back(examen);

    mutex.signal();
    llenos.signal();

}

string sacar(){

    llenos.wait();
    mutex.wait();

    string res = data.pop_back();

    mutex.signal();
    vacios.signal();
    
    return res;
}
};