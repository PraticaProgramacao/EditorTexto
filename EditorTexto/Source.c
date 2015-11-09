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

//Funções primordiais do editor:
void MoverCursor(int x, int y);
void ImprimirTexto(Linha * Texto, Caractere ** Atual);

//Operação de teclados
void OperarKeyboardInput(Keyboard keyboard, int * LinhaAtual, int * ColunaAtual, Linha * Texto, Caractere ** atual, Linha ** linhaAtual);

//Eventos de tecla

void EventCharKey(char letra, int * LinhaAtual, int * ColunaAtual, Linha * Texto, Caractere ** atual, Linha ** linhaAtual);
void EventLeftArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** atual, Linha ** Texto, Linha ** linhaAtual);
void EventEnter(int * LinhaAtual, int * ColunaAtual, Caractere ** atual, Linha ** Texto, Linha ** linhaAtual);
void EventRightArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventUpArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventDownArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventBackspace(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventDelete(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);


int main()
{
	int LinhaAtual = 0; //indica a linha atual que o cursor está repousando
	int ColunaAtual = 0; //indica a coluna atual que o cursor está repousando
	
	//Configuração inicial do texto
	Linha * Texto = (Linha *)malloc(sizeof(Linha));
	Texto->Anterior = NULL;
	Texto->Inicio = NULL;
	Texto->Proxima = NULL;
	Caractere * caractereAtual = Texto->Inicio;
	Linha * linhaAtual = Texto;

	Keyboard keyboard;
	//Inicia o editor de texto
	while (1)
	{
		ImprimirTexto(&Texto, &caractereAtual);
		MoverCursor(ColunaAtual, LinhaAtual);
		OperarKeyboardInput(GetUserInput(), &LinhaAtual, &ColunaAtual, &Texto, &caractereAtual, &linhaAtual);
	}
}


/* Função usada para setar o cursor no console
int x - Indica a posição do ponteiro no eixo X
int y - Indica a posição do ponteiro no eixo Y
UPDATE: Alerta erro ao mover o cursor
*/
void MoverCursor(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!SetConsoleCursorPosition(hConsole, coord))
		printf("Erro ao mover o cursor!");
}

void OperarKeyboardInput(Keyboard keyboard, int * LinhaAtual, int * ColunaAtual, Linha * Texto, Caractere ** atual, Linha ** linhaAtual) {
	
	if (keyboard.Command == UP_ARROW)
		EventUpArrow(LinhaAtual, ColunaAtual, atual, Texto, linhaAtual);
	else if (keyboard.Command == DOWN_ARROW)
		EventDownArrow(LinhaAtual, ColunaAtual, atual, Texto, linhaAtual);
	else if (keyboard.Command == LEFT_ARROW)
		EventLeftArrow(LinhaAtual, ColunaAtual, atual, Texto, linhaAtual);
	else if (keyboard.Command == RIGHT_ARROW)
		EventRightArrow(LinhaAtual, ColunaAtual, atual, Texto, linhaAtual);
	else if (keyboard.Command == DELETE)
		EventDelete(LinhaAtual, ColunaAtual, atual, Texto, linhaAtual);
	else if (keyboard.Command == BACKSPACE)
		EventBackspace(LinhaAtual, ColunaAtual, atual, Texto, linhaAtual);
	else if (keyboard.Command == ENTER)
		EventEnter(LinhaAtual, ColunaAtual, atual, Texto, linhaAtual);
	else if (keyboard.Command == SAVE_FILE)
		printf("\nSALVANDO ARQUIVO...\n");
	else if (keyboard.Command == OPEN_FILE)
		printf("\nABRINDO ARQUIVO...\n");
	else
		EventCharKey(keyboard.Key, LinhaAtual, ColunaAtual, Texto, atual, linhaAtual);
}



void EventLeftArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual){
	int i = 0;
	if ((*ColunaAtual) > 0) 
	{
		(*ColunaAtual)--;
 		ImprimirTexto(Texto, caracterAtual);
		(*caracterAtual) = (*caracterAtual)->Anterior;
	}
	else 
	{
		if ((*linhaAtual)->Anterior != NULL) {
			(*LinhaAtual)--;
			(*linhaAtual) = (*linhaAtual)->Anterior;
			*ColunaAtual = CountCaracteresLine(linhaAtual);
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < (*ColunaAtual - 1); (*caracterAtual) = (*caracterAtual)->Proxima, i++);
		}
	}
}

void EventRightArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	if ((*ColunaAtual) < CountCaracteresLine(linhaAtual))
	{
		(*ColunaAtual)++;
		ImprimirTexto(Texto, caracterAtual);
		if ((*caracterAtual) != NULL)
			(*caracterAtual) = (*caracterAtual)->Proxima;
		else
			(*caracterAtual) = (*linhaAtual)->Inicio;
	}
	else
	{
		if ((*linhaAtual)->Proxima != NULL) {
			(*LinhaAtual)++;
			(*linhaAtual) = (*linhaAtual)->Proxima;
			(*caracterAtual) = NULL;
			*ColunaAtual = 0;
		}
		else return;
	}
}

void EventUpArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	int countLinhaDestino, i = 0;
	if ((*LinhaAtual) <= 0)
		return;
	else
	{
		(*LinhaAtual)--;
		(*linhaAtual) = (*linhaAtual)->Anterior;
		countLinhaDestino = CountCaracteresLine(linhaAtual);
		if ((*ColunaAtual) > countLinhaDestino) {
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < countLinhaDestino-1; (*caracterAtual) = (*caracterAtual)->Proxima, i++);
			(*ColunaAtual) = countLinhaDestino;
		}
		else
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < (*ColunaAtual); (*caracterAtual) = (*caracterAtual)->Proxima, i++);
	}
}

void EventDownArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	int countLinhaDestino, i = 0;
	if ((*linhaAtual)->Proxima == NULL)
		return;
	else
	{
		(*LinhaAtual)++;
		(*linhaAtual) = (*linhaAtual)->Proxima;
		countLinhaDestino = CountCaracteresLine(linhaAtual);
		if ((*ColunaAtual) > countLinhaDestino) {
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < countLinhaDestino - 1; (*caracterAtual) = (*caracterAtual)->Proxima, i++);
			(*ColunaAtual) = countLinhaDestino;
		}
		else
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < (*ColunaAtual); (*caracterAtual) = (*caracterAtual)->Proxima, i++);
	}
}

void EventEnter(int * LinhaAtual, int * ColunaAtual, Caractere ** atual, Linha ** Texto, Linha ** linhaAtual) {
	InserirNovaLinha(Texto, linhaAtual, atual, (*ColunaAtual));
	(*LinhaAtual)++;
	(*ColunaAtual) = 0;
}

void EventBackspace(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	DeletarCaractere(LinhaAtual, caracterAtual, caracterAtual);
	(*ColunaAtual)--;
}
void EventDelete(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	DeletarCaractere(LinhaAtual, caracterAtual, &(*caracterAtual)->Proxima);
}


void EventCharKey(char letra, int * LinhaAtual, int * ColunaAtual, Linha ** Texto, Caractere ** atual, Linha ** linhaAtual) {
	InserirCaractere(letra, atual, linhaAtual);
	(*ColunaAtual)++;
}
void ImprimirTexto(Linha ** Texto, Caractere ** Atual) {
	
	Linha * lAux = (*Texto);
	Caractere * cAux = NULL;
	system("cls");
	while (lAux != NULL)
	{
		cAux = lAux->Inicio;
		while (cAux != NULL)
		{
			((*Atual) == cAux ? printf("%c", toupper(cAux->Letra)) : printf("%c", cAux->Letra));
			cAux = cAux->Proxima;
		}
		lAux = lAux->Proxima;
	}
}