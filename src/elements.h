#pragma once

struct examen {
    int id; //identificador de examen
    int i;  //cola de entrada
    char k; //tipo de muestra
    int q;  //cantidad de muestra
    float p;//tiempo de procesamiento
    char r; //resultado
    char e; //estado
};

struct Memoria {
    private:
      int i; //cantidad colas de entrada
      int ie;//tamaño colas de entrada
      int oe;//tamaño de la cola de salida
      int b; //reactivo sangre
      int d; //reactivo detrito
      int s; //reactivo piel
      int q; //tamaño colas internas
      struct examen buffer[];

    public:
      Memoria(int i, int ie, int oe, int b, int d, int s, int q);
      void meter();
      void sacar();
};

extern Memoria* mem;