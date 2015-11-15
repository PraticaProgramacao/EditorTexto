#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//Bibliotecas Personalizadas
#include "FileController.h"
#include "KeyboardController.h"

#define FALSE 0
#define TRUE 1

#define DARKBLUE 9
#define LIGHTGREEN 10
#define LIGHTBLUE 11
#define RED 12
#define PINK 13
#define YELLOW 14
#define WHITE 15

#define MAX_COLUNA 68

/*
Cada linha do texto será representada pela struct 'Linha'
Cada caractere, pela struct 'Caractere'

A lógica segue:
[Linha] -> [O] <-> [l] <-> [á] <-> [\n]
[Linha] -> [T] <-> [e] <-> [s] <-> [t] <-> [e] <-> [\n]
[Linha] -> [E] <-> [d] <-> [i] <-> [t] <-> [o] <-> [r] <-> [\n]

Que representa:
Olá
Teste
Editor

Segundo a lógica, temos as structs abaixo
*/

//Funções primordiais do editor:
void MoverCursor(int x, int y);
void ImprimirTexto(Linha * Texto, Caractere * Atual, Linha * linhaAtual, char fileDir[]);
void QuebraLinhaAutomatica(Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * LinhaAtual, int * ColunaAtual, int qtdCaractere);

//Operação de teclados
void OperarKeyboardInput(Keyboard keyboard, int * LinhaAtual, int * ColunaAtual, Linha ** Texto, Caractere ** atual, Linha ** linhaAtual, FILE ** arq, char fileDir[]);

//Eventos de tecla

void EventCharKey(char letra, int * LinhaAtual, int * ColunaAtual, Linha * Texto, Caractere ** atual, Linha ** linhaAtual);
void EventLeftArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** atual, Linha ** Texto, Linha ** linhaAtual);
void EventEnter(int * LinhaAtual, int * ColunaAtual, Caractere ** atual, Linha ** Texto, Linha ** linhaAtual);
void EventRightArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventUpArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventDownArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventBackspace(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventDelete(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual);
void EventOpenFile(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual);
void EventSaveFile(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual);


int main()
{
	int LinhaAtual = 0; //indica a linha atual que o cursor está repousando
	int ColunaAtual = 0; //indica a coluna atual que o cursor está repousando

	FILE * arquivo = NULL;
	char fileDir[200] = "";
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
		ImprimirTexto(Texto, caractereAtual, linhaAtual, fileDir);
		MoverCursor(ColunaAtual, LinhaAtual);
		keyboard = GetUserInput();
		OperarKeyboardInput(keyboard, &LinhaAtual, &ColunaAtual, &Texto, &caractereAtual, &linhaAtual, &arquivo, fileDir);
	}
}


/* Função usada para setar o cursor no console
int x - Indica a posição do ponteiro no eixo X
int y - Indica a posição do ponteiro no eixo Y
UPDATE: Alerta erro ao mover o cursor
*/
void MoverCursor(int x, int y) {
	COORD coord;
	coord.X = x + 6;
	coord.Y = y + 1;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!SetConsoleCursorPosition(hConsole, coord))
		printf("Erro ao mover o cursor!");
}

void OperarKeyboardInput(Keyboard keyboard, int * LinhaAtual, int * ColunaAtual, Linha ** Texto, Caractere ** caractereAtual, Linha ** linhaAtual, FILE ** arq, char fileDir[]) {

	if (keyboard.Command == UP_ARROW)
		EventUpArrow(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == DOWN_ARROW)
		EventDownArrow(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == LEFT_ARROW)
		EventLeftArrow(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == RIGHT_ARROW)
		EventRightArrow(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == DELETE)
		EventDelete(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == BACKSPACE)
		EventBackspace(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == ENTER)
		EventEnter(LinhaAtual, ColunaAtual, caractereAtual, Texto, linhaAtual);
	else if (keyboard.Command == SAVE_FILE)
		EventSaveFile(arq, fileDir, Texto, linhaAtual, caractereAtual, ColunaAtual, LinhaAtual);
	else if (keyboard.Command == OPEN_FILE)
		EventOpenFile(arq, fileDir, Texto, linhaAtual, caractereAtual, ColunaAtual, LinhaAtual);
	else if (keyboard.Command == ESC)
		return;
	else if (keyboard.Key != NULL)
		EventCharKey(keyboard.Key, LinhaAtual, ColunaAtual, Texto, caractereAtual, linhaAtual);
}


/* Evento é chamado quando a tecla pra o lado esquerdo é pressionada */
void EventLeftArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual){
	int i = 0;
	if ((*ColunaAtual) > 0)
	{
		(*ColunaAtual)--;
		(*caracterAtual) = (*caracterAtual)->Anterior;
	}
	else
	{
		if ((*linhaAtual)->Anterior != NULL)
		{
			(*LinhaAtual)--;
			(*linhaAtual) = (*linhaAtual)->Anterior;
			*ColunaAtual = CountCaracteresLine((*linhaAtual));
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < (*ColunaAtual); (*caracterAtual) = (*caracterAtual)->Proxima, i++);

			if ((*caracterAtual) != NULL)
			{
				if ((*caracterAtual)->Letra == '\n')
					(*caracterAtual) = (*caracterAtual)->Anterior;
			}
		}
	}
}

void EventRightArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	int qntCaracteres = CountCaracteresLine((*linhaAtual));
	if ((*ColunaAtual) < qntCaracteres)
	{
		(*ColunaAtual)++;
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
	else if ((*caracterAtual) == NULL) {
		(*LinhaAtual)--;
		(*linhaAtual) = (*linhaAtual)->Anterior;
		(*caracterAtual) = NULL;
	}

	else
	{
		(*LinhaAtual)--;
		(*linhaAtual) = (*linhaAtual)->Anterior;
		countLinhaDestino = CountCaracteresLine((*linhaAtual));
		if ((*ColunaAtual) > countLinhaDestino) {
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < countLinhaDestino - 1; (*caracterAtual) = (*caracterAtual)->Proxima, i++);
			(*ColunaAtual) = countLinhaDestino;
		}
		else
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < (*ColunaAtual - 1); (*caracterAtual) = (*caracterAtual)->Proxima, i++);

		if ((*caracterAtual) != NULL)
		{
			if ((*caracterAtual)->Letra == '\n')
				(*caracterAtual) = (*caracterAtual)->Anterior;
		}
	}
}

void EventDownArrow(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	int countLinhaDestino, i = 0;
	if ((*linhaAtual)->Proxima == NULL)
		return;
	else
	{
		(*LinhaAtual)++;
		countLinhaDestino = CountCaracteresLine((*linhaAtual)->Proxima);
		(*linhaAtual) = (*linhaAtual)->Proxima;
		if ((*ColunaAtual) > countLinhaDestino) {
			//Vai pro fim
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < countLinhaDestino - 1; (*caracterAtual) = (*caracterAtual)->Proxima, i++);

			(*ColunaAtual) = countLinhaDestino;
		}
		else if ((*caracterAtual) == NULL)
			return;
		else
			for ((*caracterAtual) = (*linhaAtual)->Inicio; i < (*ColunaAtual - 1); (*caracterAtual) = (*caracterAtual)->Proxima, i++);

		if ((*caracterAtual) != NULL)
		{
			if ((*caracterAtual)->Letra == '\n')
				(*caracterAtual) = (*caracterAtual)->Anterior;
		}
	}
}

void EventEnter(int * LinhaAtual, int * ColunaAtual, Caractere ** atual, Linha ** Texto, Linha ** linhaAtual) {
	InserirNovaLinha(Texto, linhaAtual, atual, ColunaAtual);
	(*LinhaAtual)++;
	(*ColunaAtual) = 0;
}

void EventBackspace(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	if (DeletarCaractereAtual(linhaAtual, caracterAtual, LinhaAtual, ColunaAtual) == DELETE_SUCESS)
		(*ColunaAtual)--;
	
}

void EventDelete(int * LinhaAtual, int * ColunaAtual, Caractere ** caracterAtual, Linha ** Texto, Linha ** linhaAtual) {
	DeletarProximoCaractere(linhaAtual, caracterAtual, &(*caracterAtual)->Proxima);
}

void EventCharKey(char letra, int * LinhaAtual, int * ColunaAtual, Linha ** Texto, Caractere ** atual, Linha ** linhaAtual) {
	InserirCaractere(letra, atual, linhaAtual);
	(*ColunaAtual)++;
	QuebraLinhaAutomatica(Texto, linhaAtual, atual, LinhaAtual, ColunaAtual, MAX_COLUNA);
}

void ImprimirTexto(Linha * Texto, Caractere * caractereAtual, Linha * linhaAtual, char fileDir[]) {
	int qtdLinha = 0;
	Linha * lAux = Texto;
	Caractere * cAux = NULL;
	system("cls");

	//Imprime o nome do arquivo na primeira linha:
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	(strcmp(fileDir, "") == 0 ? printf("\t\t\t\tDocumento sem titulo\n") : printf("\t\t\t\t%s\n", fileDir));

	while (lAux != NULL)
	{
		//Altera a cor da linha
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (lAux == linhaAtual) ? LIGHTGREEN : WHITE);
		qtdLinha++;
		cAux = lAux->Inicio;
		printf("%4i. ", qtdLinha);
		while (cAux != NULL)
		{
			//Antes da quebra de linha, printa a quantidade de caracteres
			if (cAux->Letra == '\n')
				printf("(%i)", CountCaracteresLine(lAux));
			(caractereAtual == cAux ? printf("%c", toupper(cAux->Letra)) : printf("%c", cAux->Letra));

			cAux = cAux->Proxima;
		}
		lAux = lAux->Proxima;
	}
}

void QuebraLinhaAutomatica(Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * LinhaAtual, int * ColunaAtual, int qtdCaractere) {
	int i = 0;
	Caractere * aux;
	if (CountCaracteresLine((*linhaAtual)) > qtdCaractere) {
		for ((*caractereAtual) = (*linhaAtual)->Inicio; i < qtdCaractere; i++, (*caractereAtual) = (*caractereAtual)->Proxima);
		InserirNovaLinha(Texto, linhaAtual, caractereAtual, ColunaAtual);
		(*ColunaAtual) = 0;
		(*LinhaAtual)++;
	}
}

void EventOpenFile(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual) {
	char letra;
	system("cls");
	while ((*arq) == NULL)
	{
		printf("Informe o diretorio e o nome do arquivo:\n>>");
		gets(fileDir); fflush(stdin);
		(*arq) = Abrir(fileDir);
	}
	DestruirTexto(Texto, linhaAtual, caractereAtual, LinhaAtual, ColunaAtual);
	fseek((*arq), 0, 0);
	do
	{
		if (fread(&letra, sizeof(char), 1, (*arq)) == 1) {
			if (letra == '\n') {
				InserirNovaLinha(Texto, linhaAtual, caractereAtual, ColunaAtual);
				(*LinhaAtual)++;
				(*ColunaAtual) = 0;
			}
			else
			{
				InserirCaractere(letra, caractereAtual, linhaAtual);
				(*ColunaAtual)++;
			}
		}
	} while (!feof(*arq));
}

void EventSaveFile(FILE ** arq, char fileDir[200], Linha ** Texto, Linha ** linhaAtual, Caractere ** caractereAtual, int * ColunaAtual, int * LinhaAtual) {
	system("cls");
	if (strcmp(fileDir, "") == 0){
		printf("Informe o nome do arquivo:\n>>");
		gets(fileDir); fflush(stdin);
	}
	if (Salvar(Texto, fileDir) == SUCESSO)
		printf("Arquivo salvo com sucesso!\n");
	else
		printf("Erro ao salvar o arquivo. Verifique se há permissão de escrita no disco.\n");
	system("pause");
}
