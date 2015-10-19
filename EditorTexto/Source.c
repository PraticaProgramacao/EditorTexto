#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//Bibliotecas Personalizadas
#include "FileController.h"
#include "KeyboardController.h"
#include "TAD.h"

#define FALSE 0
#define TRUE 1

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
	Keyboard keyboard;
	//Inicia o editor de texto
	while (1)
	{
		keyboard = GetUserInput();
		if (keyboard.Command == UP_ARROW)
			printf("UP ARROW FOI PRESSIONADA\n");
		else if (keyboard.Command == DOWN_ARROW)
			printf("DOWN ARROW FOI PRESSIONADA\n");
		else if (keyboard.Command == LEFT_ARROW)
			printf("LEFT ARROW FOI PRESSIONADA\n");
		else if (keyboard.Command == RIGHT_ARROW)
			printf("RIGHT ARROW FOI PRESSIONADA\n");
		else if (keyboard.Command == DELETE)
			printf("DELETE FOI PRESSIONADA\n");
		else if (keyboard.Command == BACKSPACE)
			printf("BACKSPACE FOI PRESSIONADA\n");
		else if (keyboard.Command == ENTER)
			printf("ENTER FOI PRESSIONADO\n");

		else
			printf("%c FOI PRESSIONADO\n", keyboard.Key);

	}
}


/* Fun��o usada para setar o cursor no console
int x - Indica a posi��o do ponteiro no eixo X
int y - Indica a posi��o do ponteiro no eixo Y
*/
void MoverCursor(int x, int y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { x - 1, y - 1 });
}
