#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "debug.h"

using namespace std;

void tirarDados(int dados[], int  cantDados)
{
	srand(time(NULL)); //semilla del numero aleatorio
	/*
	 *el chiste es que random[] va a ser una secuencia de numeros que se va haciendo cada vez más chica ej: {99750, 84500, ...,} y con rand lo doy un poco de variabilidad
	 * */
        int random[6];
	random[0] = rand() % 500 + 99750; // defino el primero de los random
	// en este for lo unico que hago es ir decrementandolo de a 1/6
	for(int i = 1; i < 6; i++)
	{
		random[i] = random[i - 1] - random[0] / 6;
	}
	// este es el for donde ocurre la animación el for externo solo hace de contador de 0 a 149999
	for(int i = 0; i < 150000; i++)
	{
		//este for hace que los dados cambien, itera por cada dado
		for(int j = 0; j < cantDados; j++)
		{
			// el if hace que cuando el contador i llegue a cierto punto deje de actualizar los dados que no cumplen la condicion, como los random[] van en orden decresciente, entonces los primeros dados van a dejar de actualizarse antes que los ultimos
			if(i < 150000 - random[j])
			{
				dados[j] = rand() % 6 + 1;
			}
			cout << dados[j] << " ";
		}
		cout << "\r"; //retorno del carro es decir lleva el cursor al principio de la linea lo cual hacer que sobreescriba los dados en el mismo lugar y permitan esa animación
	}
}

int calcularPuntaje(int dados[], int cantDados)
{
	
	int puntaje = 0;
	int combos
	for(int i = 0; i < cantDados; i++)
	{
		
	}
	return puntaje;
}

int main()
{
	int puntaje;
	int dados[6] = {1, 1, 1, 3, 4, 6};
	//tirarDados(dados);
	cout << endl << calcularPuntaje(dados, 6);
	
}
