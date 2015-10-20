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

//Função usada para setar o cursor no console
void MoverCursor(int x, int y);

//Opera
void OperarKeyboardInput(Keyboard keyboard, int qtdLinha, int qndColunaAtual, int LinhaAtual, int ColunaAtual);


int main()
{
	int qtdLinha = 0; //Indica a quantidade de linha
	int qndColunaAtual = 0; //indica a quantidade total de caractere em que o cursor está repousando
	int LinhaAtual = 0; //indica a linha atual que o cursor está repousando
	int ColunaAtual = 0; //indica a coluna atual que o cursor está repousando
	char ch; //informa a letra que foi digitada pelo usuario
	Linha * Texto = (Linha *)malloc(sizeof(Linha));
	Keyboard keyboard;
	//Inicia o editor de texto
	while (1)
	{
		OperarKeyboardInput(GetUserInput(), qtdLinha, qndColunaAtual, LinhaAtual, ColunaAtual);
	}
}


/* Função usada para setar o cursor no console
int x - Indica a posição do ponteiro no eixo X
int y - Indica a posição do ponteiro no eixo Y
*/
void MoverCursor(int x, int y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { x - 1, y - 1 });
}

void OperarKeyboardInput(Keyboard keyboard, int qtdLinha, int qndColunaAtual, int LinhaAtual, int ColunaAtual) {
	if (keyboard.Command == UP_ARROW) 
		printf("\nUP ARROW FOI PRESSIONADA\n");
	else if (keyboard.Command == DOWN_ARROW)
		printf("\nDOWN ARROW FOI PRESSIONADA\n");
	else if (keyboard.Command == LEFT_ARROW)
		printf("\nLEFT ARROW FOI PRESSIONADA\n");
	else if (keyboard.Command == RIGHT_ARROW)
		printf("\nRIGHT ARROW FOI PRESSIONADA\n");
	else if (keyboard.Command == DELETE)
		printf("\nDELETE FOI PRESSIONADA\n");
	else if (keyboard.Command == BACKSPACE)
		printf("\nBACKSPACE FOI PRESSIONADA\n");
	else if (keyboard.Command == ENTER)
		printf("\nENTER FOI PRESSIONADO\n");
	else if (keyboard.Command == SAVE_FILE)
		printf("\nSALVANDO ARQUIVO...\n");
	else if (keyboard.Command == OPEN_FILE)
		printf("\nABRINDO ARQUIVO...\n");
	else
		printf("%c", keyboard.Key);
}