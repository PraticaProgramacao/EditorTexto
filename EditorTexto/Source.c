#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

/*
Cada linha do texto ser� representada pela struct 'Linha'
Cada caractere, pela struct 'Caractere'

A l�gica segue:
[Linha] -> [O] <-> [l] <-> [�]
[Linha] -> [T] <-> [e] <-> [s] <-> [t] <-> [e]
[Linha] -> [E] <-> [d] <-> [i] <-> [t] <-> [o] <-> [r]

Que representa:
Ol�
Teste
Editor

Segundo a l�gica, temos as structs abaixo
*/

/* A linha � uma lista duplamente encadeada, para facilitar a movimenta��o do cursor entre os caracteres */
typedef struct TCaractere {
	char Letra;
	struct TCaractere * Proxima;
	struct TCaractere * Anterior;
}Caractere;

/* A linha � uma lista duplamente encadeada, para facilitar a troca de linha */
typedef struct TLinha {
	struct TLinha * Proxima;
	struct TLinha * Anterior;
	Caractere * Inicio; //Indica o in�cio da linha
}Linha;


//Fun��o usada para setar o cursor no console
void MoverCursor(int x, int y);



int main()
{
	int LinhaAtual = 0; //indica a linha atual que o cursor est� repousando
	int ColunaAtual = 0, k; //indica a coluna atual que o cursor est� repousando
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


/* Fun��o usada para setar o cursor no console
int x - Indica a posi��o do ponteiro no eixo X
int y - Indica a posi��o do ponteiro no eixo Y
*/
void MoverCursor(int x, int y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { x - 1, y - 1 });
}
