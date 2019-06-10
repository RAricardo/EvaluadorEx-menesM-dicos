SRCDIR   := src
BUILDDIR := build
INCLUDE  := include
BINDIR   := bin
CXXFLAGS := -pedantic-errors -Wall -Wextra -std=c++11 -I include
CXX := g++
FLAGS := -lrt -pthread

all: dirs $(BINDIR)/evaluator

VPATH := src include

$(BINDIR)/evaluator: $(BUILDDIR)/registro.o $(BUILDDIR)/Evaluador.o $(BUILDDIR)/examen.o $(BUILDDIR)/ColaEntrada.o $(BUILDDIR)/ColaSalida.o $(BUILDDIR)/Cola.o $(BUILDDIR)/sync.o $(BUILDDIR)/isync.o
	$(CXX) -o $@ $^ $(FLAGS)

$(BUILDDIR)/registro.o: $(SRCDIR)/registro.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/Evaluador.o: $(SRCDIR)/Evaluador.cpp $(INCLUDE)/Evaluador.h $(INCLUDE)/Memoria.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/examen.o: $(SRCDIR)/examen.cpp $(INCLUDE)/Memoria.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	
$(BUILDDIR)/ColaEntrada.o: $(SRCDIR)/ColaEntrada.cpp $(INCLUDE)/ColaEntrada.h $(INCLUDE)/Cola.h 
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/ColaSalida.o: $(SRCDIR)/ColaSalida.cpp $(INCLUDE)/ColaSalida.h $(INCLUDE)/Cola.h 
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/ColaInterna.o: $(SRCDIR)/ColaInterna.cpp $(INCLUDE)/ColaInterna.h $(INCLUDE)/Cola.h 
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/Cola.o: $(SRCDIR)/Cola.cpp $(INCLUDE)/Cola.h $(INCLUDE)/sync.h $(INCLUDE)/isync.h $(INCLUDE)/Memoria.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/sync.o: $(SRCDIR)/sync.cpp $(INCLUDE)/sync.h $(INCLUDE)/isync.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILDDIR)/isync.o: $(SRCDIR)/isync.cpp $(INCLUDE)/isync.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm -f -R $(BUILDDIR)
	rm -f registro

.PHONY: dirs
dirs:
	@test -d build || mkdir build
	@test -d bin || mkdir bin




