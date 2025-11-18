#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void dibujarUIPartida(int puntaje[], int confianza[], string jugador[], int puntosTurno, int turno, int ronda);
void pedirNombres2(string jugador[]) ;
void tirarDados(int dados[], int  cantDados);
bool escalera(int contador[]);
void calcularPares(int contador[], int &puntaje);
void calcularTrios(int contador[], int &puntaje);
int contarPares(int contador[]);
int calcularPuntaje(int dados[], int cantDados, int &puntosAct, bool &sopaEsp);
void calcularHitos(bool hitos[][5], int jugMaxSopa, int confianza[], int contSopaVal[], bool sopaEsp[], int contNoSoup[]);
void resultados(string jugador[], int puntaje[], int confianza[], bool hitos[][5]);
void jugar(string jugador[], int puntaje[], int confianza[]);
void menuPrincipal();
void agregarRanking(string jugador[], string clasificadoJ[], int puntaje[] , int clasificadoP[], int confianza[], int clasificadoC[]);
#endif
