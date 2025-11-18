#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
// #include "debug.h"
#include "funciones.h"

using namespace std;

//--------funcion para dibujar menues

void dibujarUIPartida(int puntaje[], int confianza[], string jugador[], int puntosTurno, int turno, int ronda)
{
	system("cls");
	cout << jugador[0] << ": " << setw(30 - jugador[0].size()) << left << puntaje[0] << setw(30) << right << jugador[1] << ": " << puntaje[1] << endl;
	cout << "Confianza: " << setw(30) << left << confianza[0] << setw(23) << right << "Confianza: " << confianza[1];
  cout << endl << right << setw(15) << "Ronda: " << left << ronda << endl;
	cout << endl << "Turno de " << jugador[turno] << endl;

	return;
}

void pedirNombres2(string jugador[]) 
{
	char opcion = 'n';
	while(tolower(opcion) == 'n')
	{
	  system("cls");
    string dummy;
	  getline(cin, dummy);
      
    cout << "NO SOUP FOR YOU" << endl;
	  cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
	  cout << "Antes de comenzar deben registrar sus nombres: " << endl;
  	
    cout << endl << "Jugador 1: ";
    getline(cin, jugador[0]);
  
    cout << endl << "Jugador 2: ";
    getline(cin, jugador[1]);
    
		cout << endl << "Confirmar nombres? (s)i o (n)o: "; 
		cin >> opcion;
	}
}

void tirarDados(int dados[], int  cantDados)
{
  int rollDelay = cantDados * 200;
	srand(time(NULL)); //semilla del numero aleatorio
	/*
	 *el chiste es que random[] va a ser una secuencia de numeros que se va haciendo cada vez más chica ej: {99750, 84500, ...,} y con rand lo doy un poco de variabilidad
	 * */
        int random[6];
	random[0] = rand() % 50 + rollDelay / 2; // defino el primero de los random
	// en este for lo unico que hago es ir decrementandolo de a 1/6
	for(int i = 1; i < 6; i++)
	{
		random[i] = random[i - 1] - random[0] / 6;
	}
	// este es el for donde ocurre la animación el for externo solo hace de contador de 0 a 149999
	for(int i = 0; i < rollDelay; i++)
	{
		//este for hace que los dados cambien, itera por cada dado
		for(int j = 0; j < cantDados; j++)
		{
			// el if hace que cuando el contador i llegue a cierto punto deje de actualizar los dados que no cumplen la condicion, como los random[] van en orden decresciente, entonces los primeros dados van a dejar de actualizarse antes que los ultimos
			if(i < rollDelay - random[j])
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

int calcularPuntaje(int dados[], int cantDados, int &puntosAct, bool &sopaEsp)
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
		sopaEsp = true;
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
	
	if(!puntaje) 
	{
		puntosAct = 0;
		return 0;
	}

	puntosAct += puntaje;
	return dadosRestantes;
}

void calcularHitos(bool hitos[][5], int jugMaxSopa, int confianza[], int contSopaVal[], bool sopaEsp[], int contNoSoup[])
{
  hitos[jugMaxSopa][0] = true;

	if(confianza[0] > confianza[1]) hitos[0][1] = true;
	else if(confianza[0] < confianza[1]) hitos[1][1] = true;
	if(contSopaVal[0] > contSopaVal[1]) hitos[0][2] = true;
	else if(contSopaVal[0] < contSopaVal[1]) hitos[1][2] = true;
	if(sopaEsp[0]) hitos[0][3] = true;
	if(sopaEsp[1]) hitos[1][3] = true;
	if(contNoSoup[0] > contNoSoup[1]) hitos[0][4] = true;
	else if(contNoSoup[0] < contNoSoup[1]) hitos[1][4] = true;
  return;
}

void resultados(string jugador[], int puntaje[], int confianza[], bool hitos[][5])
{
	int bonus[2][5];
	int puntosHitos[5] = {300, 200, 100, 500, 100};
	int ganador;
	for(int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++) 
		{
			bonus[i][j] = puntosHitos[j]*hitos[i][j];
		}
	}
  cout << left << setw(20) << "HITO" << setw(20) << jugador[0] << jugador[1] << endl;
	cout << setfill('-') << setw(60) << "-" << endl;
	cout << setfill(' ') << left << setw(20) << "Puntos" << right << setw(5) << puntaje[0] << left << setw(15) << " PTS" << right << setw(5) << puntaje[1] << " PTS" << endl;
	cout << left << setw(20) << "Sopa mas cara" << right << setw(5) << bonus[0][0] << left << setw(15) << " PTS" << right << setw(5) << bonus[1][0] << " PTS" << endl;
	cout << left << setw(20) << "Mayor confianza" << right << setw(5) << bonus[0][1] << left << setw(15) << " PTS" << right << setw(5) << bonus[1][1] << " PTS" << endl;
	cout << left << setw(20) << "Cliente constante" << right << setw(5) << bonus[0][2] << left << setw(15) << " PTS" << right << setw(5) << bonus[1][2] << " PTS" << endl;
	cout << left << setw(20) << "Pedido perfecto" << right << setw(5) << bonus[0][3] << left << setw(15) << " PTS" << right << setw(5) << bonus[1][3] << " PTS" << endl;
	cout << left << setw(20) << "Premio George" << right << setw(5) << bonus[0][4] << left << setw(15) << " PTS" << right << setw(5) << bonus[1][4] << " PTS" << endl;
	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
	for(int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			puntaje[i] += bonus[i][j];
		}
	}

	if(puntaje[0] > puntaje[1])
	{
	  ganador = 0;
	}
	else if(puntaje[0] < puntaje[1])
	{
	  ganador = 1;
	}
	else
	{
	  if(confianza[0] > confianza[1])
	  {
	    ganador = 0;
	  }
	  else if(confianza[0] < confianza[1])
	  {
	    ganador = 1;
	  }
		else ganador = -1; //esto sería un empate
	}
	cout << left << setw(20) << "TOTAL" << right << setw(5) << puntaje[0] << left << setw(15) << " PTS" << right << setw(5) << puntaje[1] << " PTS" << endl;
	if(ganador < 0)
	{
	  cout << endl << "Tanto " << jugador[0] << " como " << jugador[1] << "se pueden consderar clientes fieles del tirano de la sopa";
	}
	else cout << endl << "GANADOR: " << jugador[ganador] << " con " << puntaje[ganador] << " puntos." << endl;

	system("pause");
	return;
}

void jugar(string jugador[], int puntaje[], int confianza[])
{	
  //primero defino como es una ronda y quizas despues lo extraiga a una función
	const int minValido = 300;
	puntaje[0] = 0;
	puntaje[1] = 0;
	confianza[0] = 300;
	confianza[1] = 300;
	int puntosTurno;
	int dadosRestantes;
	char opcion;
	int dados[6];
	int ronda = 0;

	//variables para los hitos
	
	int contSopaVal[2] = {0};		// Cliente Constante
	int contNoSoup[2] = {0};		// Premio George
	int maxSopa = -1; 
	int jugMaxSopa;							// Sopa más cara
	bool sopaEsp[2] = {0};			// Si logro tirar Sopa especial al menos una vez en la partida
	int jugMayConfianza[2];			// Mayor confianza
  
	bool hitos[2][5] = {0};
	
	/* hitos lo defini como un array bidimiensional
	 *
	 * Sopa mas cara			x	x
	 * Mayor confianza		x	x
	 * Cliente Constante	x	x
	 * Pedido perfecto		x	x
	 * Premio George			x	x
	 *
	 * */
	//Este bucle representa una partida
	
	
	while(ronda < 6 && puntaje[0] < 2500 && puntaje[1] < 2500)
	{ 
		for(int jAct = 0; jAct < 2; jAct++)
		{
      puntosTurno = 0;
		  opcion = 's'; //lo necesito para el while interno (posiblemente lo extraiga en otra funcion
		  dadosRestantes = 6;
		  dibujarUIPartida(puntaje, confianza, jugador, puntosTurno, jAct, ronda + 1);
      while(dadosRestantes && opcion == 's')
	    {
				cout << endl;
				system("set /p \"=Presione enter para tirar los dados...\" "); //Igual a system pause pero solo se toma con enter y me deja poner un texto en consola
				cout << endl;
		    tirarDados(dados, dadosRestantes);
		    dadosRestantes = calcularPuntaje(dados, dadosRestantes, puntosTurno, sopaEsp[jAct]);

			  cout << endl << "puntaje actual: " << puntosTurno << endl;
		    //si me quedan dados por tirar o si mi puntaje alcanza la confianza del tirano (si me hubiese salido NO SOUP FOR YOU mi puntaje se volvería 0)
			  if(!dadosRestantes && puntosTurno >= minValido)
			  {
			    cout << "Logro alcanzar una sopa valida" << endl << "Utilizo todos los dados, turno finlizado" << endl;
				  opcion = 'n';
  
				  system("pause");
			  }
			  else if(dadosRestantes && puntosTurno >= minValido)
		    {
			    cout << "Logro alcanzar una sopa valida" << endl;
					cout << "Dados restantes: " << dadosRestantes << endl;
					cout << "Desea continuar tirando? (s)i/(n)o: ";
  
			    cin >> opcion;
		    }
		    else if(puntosTurno == 0 || (puntosTurno < minValido && !dadosRestantes))
	      {
					
			    cout << endl << "No soup for you" << endl;
			    contNoSoup[jAct]++;
					if(confianza[jAct] > 300) confianza[jAct] -= 100;
				  opcion = 'p'; //podria ser cualquier valor que no coincida yo elelgí 'p' por perdió
			    system("pause"); // es para "pausar" el programa y poder leer el mensaje
		    }
		    else if(puntosTurno < minValido && dadosRestantes)
		    {
			    cout << "El tirano no aceptara pedidos tan endebles, debe seguir tirando" << endl;
				}
		  	
		    if(tolower(opcion) == 'n')
		    {
				  contSopaVal[jAct]++;
					puntaje[jAct] += puntosTurno > confianza[jAct] ? confianza[jAct] : puntosTurno;
				  confianza[jAct] += 300;
					if(maxSopa < puntosTurno)
					{
						maxSopa = puntosTurno;
						jugMaxSopa = jAct;
					}
		    }
	    }
		}
		ronda++;
	}
	cout << endl << endl << "juego finalizado" << endl << endl;
	//sumar los puntos de los hitos aquí
	system("pause");
  system("cls");
	calcularHitos(hitos, jugMaxSopa, confianza, contSopaVal, sopaEsp, contNoSoup);
	resultados(jugador, puntaje, confianza, hitos);
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
	cout << endl << "Por favor elija una opcion: ";
  return;
}

void agregarRanking(string jugador[], string clasificadoJ[], int puntaje[] , int clasificadoP[], int confianza[], int clasificadoC[], int &nEntradas)
{
	string temp;
	int temp2;
	int j;
	for(int i = 0; i < 2; i++)
	{
		j = nEntradas;
		clasificadoJ[j] = jugador[i];
		clasificadoP[j] = puntaje[i];
		clasificadoC[j] = confianza[i];
		while(j > 0 && clasificadoP[j] > clasificadoP[j-1])
		{
			//nombre del jugador
			temp = clasificadoJ[j-1];
			clasificadoJ[j-1] = clasificadoJ[j];
			clasificadoJ[j] = temp;
			
			temp2 = clasificadoP[j-1];
			clasificadoP[j-1] = clasificadoP[j];
			clasificadoP[j] = temp2;

			temp2 = clasificadoC[j-1];
			clasificadoC[j-1] = clasificadoC[j];
			clasificadoC[j] = temp2;

			j--;
		}
		if(nEntradas < 5)
		{
			nEntradas++;
	  }
	}
	return;
}

void estadisticas(string jugador[], int puntaje[], int confianza[], int nEntradas)
{
	system("cls");
	cout << "ESTADISTICA";
	cout << setfill('-') << setw(60) << "-" << endl << setfill(' ');
	cout << left << setw(20) << "NOMBRE" << setw(20) << "PUNTOS" << "CONFIANZA" << endl;
	for(int i = 0; i < nEntradas; i++)
	{
		cout << left << setw(20) << jugador[i] << right << setw(4) << puntaje[i] << left << setw(16) << " PTS" << right << confianza[i] << " PTS" << endl;
	}
	system("pause");
	return;
}
void creditos()
{
	system("cls");
  cout << "EQUIPO 17" << endl;
	cout << setfill('-') << setw(60) << "-" << endl << setfill(' ') << endl;
	cout << left << setw(20) << "LEGAJO" << setw(20) << "NOMBRE" << "APELLIDO" << endl << endl;
	cout << left << setw(20) << "34100" << setw(20) << "Hernan" << "Flores" << endl;
	cout << left << setw(20) << "32493" << setw(20) << "Mauro" << "Calvo" << endl;
	cout << left << setw(20) << "34219" << setw(20) << "Lucas" << "Gasperi" << endl << endl;
	cout << setfill('-') << setw(60) << "-" << endl << setfill(' ') << endl << endl;
	system("pause");
	return;
}

void debugDados()
{
	int dados[6];
	int input;
	int dadoAct = 0;
	int dadosRestantes;
	int puntos = 0;
	bool sopaEsp;

	cout << "ingrese los valores de los dados como un numero de 6 digitos: ";
	cin >> input;

	while(input > 0 && dadoAct < 6)
	{
		dados[dadoAct] = input % 10;
		if(dados[dadoAct] > 6 || dados[dadoAct] < 1)
		{
			cout << endl << "Inrodujo valores de dados no validos" << endl;
			system("pause");
			return;
		}
		input /= 10;
		dadoAct++;
	}
	dadosRestantes = calcularPuntaje(dados, dadoAct, puntos, sopaEsp);
	for(int i = 0; i < 6; i++)
	{
		cout << dados[i] << " ";
	}

	cout << endl << "calculo de puntos: " << puntos << " |dados restantes: " << dadosRestantes;
	system("pause");
	return;
}

int main()
{
	int nEntradas = 0;
	int opcion = -1; //prueba
	char salir = 'n';
	string jugadores[2];
	int puntaje[2] = {-1, -1};
	string historialJugadores[6];
	int historialPuntajes[6] = {0};
	int historialConfianza[6] = {0};
	int confianza[2] = {0}; //si esta en 0 es que nunca se arrancó un juego
	int dados[6] = {3, 5, 5, 1, 2, 4};
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
				agregarRanking(jugadores, historialJugadores, puntaje, historialPuntajes, confianza, historialConfianza, nEntradas);
				break;
      case 2:
				estadisticas(historialJugadores, historialPuntajes, historialConfianza, nEntradas);
        break;
			case 3:
        creditos(); 
        break;
			case 4:
				system("cls");
        debugDados();
				break;
      case 0:
				system("cls");
        cout << endl << endl << endl << "Esta seguro de que desea salir del juego? (s)i o (n)o?";
				cin >> salir;
				if(salir == 's') opcion = 0;
				else if(salir == 'n') opcion = 1;
        break;
      default:
        cout <<"Opcion incorrecta." << endl;
  	}
	}
	return 0;
}

