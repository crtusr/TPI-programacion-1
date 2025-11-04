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

bool escalera(int contador[])
{
	bool esValida = true;
	for(int i = 0; i < 6; i++)
	{
		if(contador[i] != 1) esValida = false;
	}
	if(esValida)
	for(int i = 0; i < 6; i++) contador[i] = 0;
	return esValida;
}

void calcularPares(int contador[], int &puntaje)
{
	for(int i = 0; i < 6; i++)
	{
		if(contador[i] >= 2) 
		{
			puntaje += (100 * contador[i] / 2);
			contador[i] %= 2;
		}
	}
	return;
}

void calcularTrios(int contador[], int &puntaje)
{
	for(int i = 1; i < 6; i++)
	{
		if(contador[i] >= 3) 
		{
			puntaje += (100 * (i + 1) * contador[i] / 3);
			contador[i] %= 3;
		}
	}
	return;
}

int contarPares(int contador[])
{
	int contPares = 0;
	for(int i = 0; i < 6; i++)
	{
		if(contador[i] >= 2) contPares += (contador[i] / 2);
	}
	return contPares;
}

int calcularPuntaje(int dados[], int cantDados, int &puntosAct)
{
	int puntaje = 0;
	int dadosRestantes = 0;
	
	int contador[6] = {0};
	
	for(int i = 0; i < cantDados; i++)
	{
		contador[dados[i] - 1]++;
	}
	//calculo escalera
	if(escalera(contador)) return 1500;
	else
	{
	  //me fijo si hay trios de 1 tiene que ir primero porque si sale 111111 serian 2000 puntos
	  while(contador[0] >= 3) 
	  {
	  	puntaje += 1000;
	  	contador[0] -= 3; //voy eliminando los ya contados
	  }
	  //reviso si hay triple par
	  if(contarPares(contador) == 3) return 1500;
	  //calculo los trios que no son 1
	  /*
	  for(int i = 1; i < 6; i++)
	  {
	  	while(contador[i] >= 3) 
	  	{
	  		puntaje += (i + 1) * 100;
	  		contador[i] -= 3;
	  	}
	  }
	  */
	  calcularTrios(contador, puntaje);
	  //vuelvo a contar pares pero en una variable
	  
	  calcularPares(contador, puntaje);
	  
	  if(contador[0]) 
	  {
	  	puntaje += 100;
	  	contador[0]--;
	  }
	  if(contador[4])
	  {
	  	puntaje += 50;
	  	contador[4]--;
	  }
	}
	
	for(int i = 0; i < 6; i++)
	{
	  dadosRestantes += contador[i];
	}
	  
	//tres pares 1500 {hay 3 dos en contador}
	//escalera 1500 {1 1 1 1 1 1}
	//trio de unos 1000 (3, x, x, x, x, x)
	//trios 100*n {x, 3, 3, 3, 3, 3}
	//par 100 (hay hasta 2 dos en contador)
	//uno 100 (1, x, x, x, x, x)
	//cinco 50 (x, x, x, x, 1, x)
	
	/*
	  que pasa si sale 
	  1 1 
	  1 1 1 1 1 1
	  
	*/
	puntosAct += puntaje;
	return dadosRestantes;
}

int main()
{
	int puntaje = 0;
	int dados[6] = {1, 1, 1, 3, 4, 6};
	int prueba[6] = {6, 6, 6, 5, 5, 2};
	//tirarDados(dados, 6);
	cout << endl << calcularPuntaje(dados, 6, puntaje) << "  " << puntaje << endl << calcularPuntaje(prueba, 6, puntaje) << "  " << puntaje;
	
}
