#include <ios>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "debug.h"

using namespace std;

void pedirNombres2(string jugador[]) 
{
  string dummy;
	getline(cin, dummy);

    cout << "Ingresa el nombre del Jugador 1: ";
    getline(cin, jugador[0]);

    cout << "Ingresa el nombre del Jugador 2: ";
    getline(cin, jugador[1]);
}

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
			puntaje += (100);
			contador[i] -= 2;
		}
	}
	return;
}

void calcularTrios(int contador[], int &puntaje)
{
  //puse acá que 111 son 1000 puntos pero asumiendo que no hay 6 unos
  if(contador[0] >= 3) 
	{
		puntaje += 1000;
		contador[0] -= 3;
	}
	for(int i = 1; i < 6; i++)
	{
    //acá calcula el resto de los triples
		if(contador[i] >= 3) 
		{
			puntaje += (100 * (i + 1));
			contador[i] -= 3;
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
	if(escalera(contador)) 
  {
    puntosAct += 1500;
    return 0;
  }
	else
	{
	  //El primero es un caso especial me fijo si hay dos trios de 1 tiene que ir primero porque si sale 111111 serian 2000 puntos lo hice así porque seria un caso limite
    
    if(contador[0] == 6) 
	  {
	  	puntaje += 2000;
	  	contador[0] -= 6; //elimino los 6 de contador asi me queda en 0
	  }

	  //reviso si hay triple par
	  if(contarPares(contador) == 3)
    {
      puntosAct += 1500;
      return 0;
    }
	  
	  calcularTrios(contador, puntaje);

	  //se asume que ya no hay triple par
	  calcularPares(contador, puntaje);
	  
	  //si quedo un 1 suelto
	  if(contador[0]) 
	  {
	  	puntaje += 100;
	  	contador[0]--;
	  }
	  //si quedo un 5 suelto
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
	  
	//tres pares 1500 {3x2, 1x4 y 1x2, 1x6}
	//escalera 1500 {1 1 1 1 1 1}
	//trio de unos 1000 (3, x, x, x, x, x)
	//trios 100*n {x, 3, 3, 3, 3, 3}
	//par 100 (hay hasta 2 dos en contador)
	//uno 100 (1, x, x, x, x, x)
	//cinco 50 (x, x, x, x, 1, x)
	
	//solo falta codificar el caso "no soup for you" que es cuando se tiraron los y no hay combinaciones posibles, en ese caso puntosAct de volvería 0

	puntosAct += puntaje;
	return dadosRestantes;
}



void jugar(string jugador[], int puntaje[], int confianza[])
{	
  //primero defino como es una ronda y quizas despues lo extraiga a una función
	confianza[0] = 300;
	confianza[1] = 300;
	int dadosRestantes = 6;
	int dados[6];
	char opcion = 's';

  while(dadosRestantes && opcion == 's')
	{
		tirarDados(dados, dadosRestantes);
		dadosRestantes = calcularPuntaje(dados, dadosRestantes, puntaje[0]);
		//si me quedan dados por tirar o si mi puntaje no es 0 (si me hubiese salido NO SOUP FOR YOU mi puntaje se volvería 0)
		if(dadosRestantes && puntaje[0])
		{
			cout << endl << "puntaje actual" << endl;
			cout << "continuar tirando? (s)i/(n)o" << endl;
			cin >> opcion;
		}
		else if(puntaje[0] == 0 || (puntaje[0] < confianza[0] && !dadosRestantes))
	  {
			cout << endl << "No soup for you" << endl;
			confianza[0] -= 100;
		}
	}
	return;
}

void menuPrincipal()
{
	system("cls");
	cout << "   NO SOUP FOR YOU" <<endl;
  cout << "------------------------"<<endl;
  cout << "1 - JUGAR"<<endl;
  cout << "2 - ESTADISTICAS"<<endl;
  cout << "3 - CREDITOS"<<endl;
  cout << "------------------------"<<endl;
  cout << "0 - SALIR"<<endl;

}

int main()
{
	int opcion = -1; //prueba
	string jugadores[2];
	int puntaje[2] = {0};
	int confianza[2] = {0}; //si esta en 0 es que nunca se arrancó un juego
	
	while(opcion)
	{
	//prueba
    menuPrincipal();
    cin >> opcion;
  
    switch (opcion)
  	{
      case 1:
        pedirNombres2(jugadores);
				jugar(jugadores, puntaje, confianza);
  			break;
      case 2:
        
        break;
      case 3:
          
        break;
      case 0:
          
        break;
      default:
        cout <<"Opcion incorrecta." << endl;
  	}
	}
}

