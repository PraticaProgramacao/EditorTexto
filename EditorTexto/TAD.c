#include "TAD.h"
#include <stdio.h>
#include <stdlib.h>




void InserirNovaLinha(Linha ** Texto, Linha ** linhaAtual, Caractere ** atual, int * posColuna) {
	Linha * novaLinha = (Linha *)malloc(sizeof(Linha));
	Caractere * QuebraLinha = (Caractere *)malloc(sizeof(Caractere));

	//Defini��o da nova linha
	novaLinha->Inicio = NULL;
	novaLinha->Anterior = NULL;
	novaLinha->Proxima = NULL;

	//A primeira linha obrigatoriamente ter� um \n, pois � uma quebra de linha no final das contas
	QuebraLinha->Letra = '\n';
	QuebraLinha->Anterior = NULL;
	QuebraLinha->Proxima = NULL;

	//Se for no in�cio da linha
	if ((*atual) == NULL)
	{
		//Se for na primeira linha
		if ((*linhaAtual)->Anterior == NULL)
			*Texto = novaLinha;

		novaLinha->Inicio = QuebraLinha;
		novaLinha->Anterior = (*linhaAtual)->Anterior;
		novaLinha->Proxima = (*linhaAtual);
		if ((*linhaAtual)->Anterior != NULL)
			(*linhaAtual)->Anterior->Proxima = novaLinha;
		(*linhaAtual)->Anterior = novaLinha;

	}
	else
	{
		//Defini��es da quebra de linha
		QuebraLinha->Anterior = (*atual);
		QuebraLinha->Proxima = NULL;

		novaLinha->Inicio = (*atual)->Proxima;
		if (novaLinha->Inicio != NULL)
			novaLinha->Inicio->Anterior = NULL;

		(*atual)->Proxima = QuebraLinha;

		novaLinha->Anterior = (*linhaAtual);
		novaLinha->Proxima = (*linhaAtual)->Proxima;

		if ((*linhaAtual)->Proxima != NULL)
			(*linhaAtual)->Proxima->Anterior = novaLinha;

		(*linhaAtual)->Proxima = novaLinha;
		(*atual) = NULL;

		(*linhaAtual) = novaLinha;
	}
}

int CountCaracteresLine(Linha * linhaAtual) {
	/* Inicialmente todas as linhas tem 0 caracteres, ent�o: */
	int i = 0;
	Caractere * aux = linhaAtual->Inicio;

	if (aux != NULL)
	{
		while (aux != NULL)
		{
			if (aux->Letra != '\n')
				i++;
			aux = aux->Proxima;
		}
	}
	return i;
}

void InserirCaractere(char letra, Caractere ** atual, Linha ** linhaAtual) {
	Caractere * novo = (Caractere *)malloc(sizeof(Caractere));
	novo->Letra = letra;
	novo->Proxima = NULL;
	novo->Anterior = NULL;

	//Inser��o no inicio
	if ((*atual) == NULL)
	{
		*atual = novo;
		if ((*linhaAtual)->Inicio == NULL)
			(*linhaAtual)->Inicio = (*atual);
		else
		{
			novo->Proxima = (*linhaAtual)->Inicio;
			(*linhaAtual)->Inicio->Anterior = novo;
			(*linhaAtual)->Inicio = novo;
		}
	}
	else
	{
		//Inser��o no fim
		if ((*atual)->Proxima == NULL) {
			(*atual)->Proxima = novo;
			novo->Anterior = (*atual);
			(*atual) = novo;
		}
		else
		{
			//Inser��o no meio
			novo->Anterior = (*atual);
			novo->Proxima = (*atual)->Proxima;

			(*atual)->Proxima->Anterior = novo;
			(*atual)->Proxima = novo;
			(*atual) = novo;
		}
	}
}

int DeletarCaractereAtual(Linha ** linhaAtual, Caractere ** caracterAtual, int * LinhaAtual, int * ColunaAtual) {
	Caractere * toDelete = (*caracterAtual);
	//Juntar linhas (implementar)
	if (toDelete == NULL)
	{
		ConcatenarBackspace(linhaAtual, caracterAtual, LinhaAtual, ColunaAtual);
		return DELETE_CONCATENADO;
	}
	else
	{
		//Remo��o no meio
		if (toDelete->Proxima != NULL && toDelete->Anterior != NULL)
		{
			toDelete->Anterior->Proxima = toDelete->Proxima;
			toDelete->Proxima->Anterior = toDelete->Anterior;
			(*caracterAtual) = toDelete->Anterior;
			free(toDelete);
		}
		//Elemento �nico da lista
		else if (toDelete->Proxima == NULL && toDelete->Anterior == NULL)
		{
			(*linhaAtual)->Inicio = NULL;
			(*caracterAtual) = NULL;
			free(toDelete);
		}
		else if (toDelete->Proxima == NULL) {
			toDelete->Anterior->Proxima = NULL;
			(*caracterAtual) = toDelete->Anterior;
			free(toDelete);
		}
		else if (toDelete->Anterior == NULL) {
			toDelete->Proxima->Anterior = NULL;
			(*linhaAtual)->Inicio = toDelete->Proxima;
			(*caracterAtual) = NULL;
			free(toDelete);
		}
	}
	return DELETE_SUCESS;
}

int DeletarProximoCaractere(Linha ** linhaAtual, Caractere ** caracterAtual, Caractere ** prox) {
	Caractere * toDelete;
	Linha * lAux, *lAuxToDelete;
	lAux = (*linhaAtual);
	lAuxToDelete = lAux->Proxima;
	toDelete = (*caracterAtual);

	if (toDelete == NULL)
	{
		toDelete = lAux->Inicio;
		lAux->Inicio = toDelete->Proxima; //Inicio da linha, aponta para o toDelete pr�ximo
		if (toDelete->Proxima != NULL)
			toDelete->Proxima->Anterior = lAux->Inicio; //O anterior do toDelete pr�ximo aponta para o inicio da linha
		free(toDelete); //Desaloca o toDelete
		
	}
	else if (toDelete->Proxima->Letra == '\n' && lAux->Proxima != NULL) //Remo��o no fim
	{
		free(toDelete->Proxima); //Free na struct do '\n'
		toDelete->Proxima = lAux->Proxima->Inicio; //Faz a liga��o do ultimo elemento da linha atual, com o primeiro da proxima linha
		toDelete->Proxima->Anterior = toDelete;   //Continua a liga��o
		lAux->Proxima = lAuxToDelete->Proxima;
		free(lAuxToDelete); //Desaloca a linha de baixo

	}
	else if (toDelete->Proxima != NULL)//Remo��o meio
	{
		toDelete = (*caracterAtual)->Proxima; //Pocisiona o toDelete,para o caracter que vai ser deletado
		(*caracterAtual)->Proxima = toDelete->Proxima; //Faz a liga��o do elemento anterior com o toDelete,com o proximo
		toDelete->Proxima->Anterior = (*caracterAtual);//Continua a liga��o
		free(toDelete); //Desaloca o toDelete
	}



	return DELETE_SUCESS;

}
void DestruirTexto(Linha ** Texto, Linha ** linhaAtual, Caractere ** caracterAtual, int * LinhaAtual, int * ColunaAtual) {
	Linha * lAux = (*Texto), *lAuxProx;
	Caractere * cAux, *cAuxProx;

	while (lAux != NULL)
	{
		lAuxProx = lAux->Proxima;
		cAux = lAux->Inicio;
		while (cAux != NULL)
		{
			cAuxProx = cAux->Proxima;
			free(cAux);
			cAux = cAuxProx;
		}
		free(lAux);
		lAux = lAuxProx;
	}
	(*Texto) = (Linha *)malloc(sizeof(Linha));
	(*Texto)->Anterior = NULL;
	(*Texto)->Proxima = NULL;
	(*Texto)->Inicio = NULL;
	(*linhaAtual) = (*Texto);
	(*caracterAtual) = NULL;
	(*LinhaAtual) = 0;
	(*ColunaAtual) = 0;
}

void ConcatenarBackspace(Linha ** linhaAtual, Linha ** caractereAtual, int * LinhaAtual, int * ColunaAtual) {
	int count, i = 0;
	Caractere * ToDelete;
	Linha * lAux = (*linhaAtual)->Anterior;
	if (lAux == NULL)
		return;

	count = CountCaracteresLine(lAux);

	for (ToDelete = lAux->Inicio; i < (count - 1); ToDelete = ToDelete->Proxima, i++);
	(*caractereAtual) = ToDelete;

	if (CountCaracteresLine((*linhaAtual)) == 0) {
		DeletarLinhaBackspace(linhaAtual, caractereAtual, LinhaAtual, ColunaAtual);
		return;
	}

	free(ToDelete->Proxima);
	ToDelete->Proxima = (*linhaAtual)->Inicio;

	if ((*linhaAtual)->Inicio != NULL)
		(*linhaAtual)->Inicio->Anterior = ToDelete;

	lAux->Proxima = (*linhaAtual)->Proxima;

	(*LinhaAtual)--;
	(*ColunaAtual) = count;

	free((*linhaAtual));
	(*linhaAtual) = lAux;

}

/*
Deleta uma linha
*/
void DeletarLinhaBackspace(Linha ** linhaAtual, Caractere ** caracterAtual, int * LinhaAtual, int * ColunaAtual) {
	Linha * toDelete = (*linhaAtual);
	Caractere * cToDelete;
	int count, i = 0;
	//se houver caractere na linha atual, remove
	if ((*linhaAtual)->Inicio != NULL)
		free(toDelete->Inicio);

	//Define a linha anterior como sendo a linha atual
	(*linhaAtual) = toDelete->Anterior;

	//Define pr�xima e anterior
	(*linhaAtual)->Proxima = toDelete->Proxima;
	if (toDelete->Proxima != NULL) {
		toDelete->Proxima->Anterior = (*linhaAtual);
		if ((*linhaAtual)->Inicio->Letra == '\n')
			(*caracterAtual) = NULL;

	}
	//Verifica se � �ltima linha(remover \n da linha anterior)
	else
	{
		count = CountCaracteresLine((*linhaAtual));
		for (cToDelete = (*linhaAtual)->Inicio; i < (count - 1); cToDelete = cToDelete->Proxima, i++);
		if (cToDelete->Letra == '\n')
		{
			free(cToDelete);
			(*linhaAtual)->Inicio = NULL;
			(*caracterAtual) = NULL;
		}
		else
		{
			free(cToDelete->Proxima);
			cToDelete->Proxima = NULL;
		}
	}

	//Desaloca a linha
	free(toDelete);

	(*LinhaAtual)--;
	(*ColunaAtual) = CountCaracteresLine((*linhaAtual));
}