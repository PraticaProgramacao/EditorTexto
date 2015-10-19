#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

/*
Cada linha do texto será representada pela struct 'Linha'
Cada caractere, pela struct 'Caractere'

A lógica segue:
[Linha] -> [O] <-> [l] <-> [á]
[Linha] -> [T] <-> [e] <-> [s] <-> [t] <-> [e]
[Linha] -> [E] <-> [d] <-> [i] <-> [t] <-> [o] <-> [r]

Que representa:
Olá
Teste
Editor

Segundo a lógica, temos as structs abaixo
*/

/* A linha é uma lista duplamente encadeada, para facilitar a movimentação do cursor entre os caracteres */
typedef struct TCaractere {
	char Letra;
	struct TCaractere * Proxima;
	struct TCaractere * Anterior;
}Caractere;

/* A linha é uma lista duplamente encadeada, para facilitar a troca de linha */
typedef struct TLinha {
	struct TLinha * Proxima;
	struct TLinha * Anterior;
	Caractere * Inicio; //Indica o início da linha
}Linha;


//Função usada para setar o cursor no console
void MoverCursor(int x, int y);



int main()
{
	int LinhaAtual = 0; //indica a linha atual que o cursor está repousando
	int ColunaAtual = 0, k; //indica a coluna atual que o cursor está repousando
	char ch; //informa a letra que foi digitada pelo usuario
	Linha * Texto = (Linha *)malloc(sizeof(Linha));

	//Inicia o editor de texto
	while (1)
	{
		printf("Informe a posicao X do cursor:\n");
		scanf("%i", &LinhaAtual);
		printf("Informe a posicao Y do cursor:\n");
		scanf("%i", &ColunaAtual);

		MoverCursor(LinhaAtual, ColunaAtual);

		getchar();
	}
}


/* Função usada para setar o cursor no console
int x - Indica a posição do ponteiro no eixo X
int y - Indica a posição do ponteiro no eixo Y
*/
void MoverCursor(int x, int y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { x - 1, y - 1 });
}
