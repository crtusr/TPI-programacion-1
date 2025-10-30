#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "debug.h"

using namespace std;

void tirarDados(unsigned int dados[])
{
	srand(time(NULL));
  int random[6];
	random[0] = rand() % 500 + 99750;
	for(int i = 1; i < 6; i++)
	{
		random[i] = random[i - 1] - random[0] / 6;
	}
	
	for(int i = 0; i < 150000; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			if(i < 150000 - random[j])
			{
				dados[j] = rand() % 6 + 1;
			}
			cout << dados[j] << " ";
		}
		cout << "\r";
	}
}

int main()
{
	unsigned int dados[6];
	tirarDados(dados);
}