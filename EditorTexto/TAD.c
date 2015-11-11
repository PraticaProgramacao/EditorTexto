#include "TAD.h"
#include <stdio.h>
#include <stdlib.h>

void InserirNovaLinha(Linha ** Texto, Linha ** linhaAtual, Caractere ** atual, int * posColuna) {
	Linha * novaLinha = (Linha *)malloc(sizeof(Linha));
	Caractere * QuebraLinha = (Caractere *)malloc(sizeof(Caractere));

	//Definição da nova linha
	novaLinha->Inicio = NULL;
	novaLinha->Anterior = NULL;
	novaLinha->Proxima = NULL;

	//A primeira linha obrigatoriamente terá um \n, pois é uma quebra de linha no final das contas
	QuebraLinha->Letra = '\n';
	QuebraLinha->Anterior = NULL;
	QuebraLinha->Proxima = NULL;
	
	//Se for no início da linha
	if ((*atual) == NULL)
	{
		//Se for na primeira linha
		if ((*linhaAtual)->Anterior == NULL)
			*Texto = novaLinha;

		novaLinha->Inicio = QuebraLinha;
		novaLinha->Anterior = (*linhaAtual)->Anterior;
		novaLinha->Proxima  = (*linhaAtual);
		if((*linhaAtual)->Anterior != NULL)
			(*linhaAtual)->Anterior->Proxima = novaLinha;
		(*linhaAtual)->Anterior = novaLinha;

	}
	else 
	{
		//Definições da quebra de linha
		QuebraLinha->Anterior = (*atual);
		QuebraLinha->Proxima = NULL;
		
		novaLinha->Inicio = (*atual)->Proxima;
		if (novaLinha->Inicio != NULL)
			novaLinha->Inicio->Anterior = NULL;

		(*atual)->Proxima = QuebraLinha;

		novaLinha->Anterior = (*linhaAtual);
		novaLinha->Proxima = (*linhaAtual)->Proxima;
		
		if((*linhaAtual)->Proxima != NULL)
			(*linhaAtual)->Proxima->Anterior = novaLinha;
		
		(*linhaAtual)->Proxima = novaLinha;
		(*atual) = NULL;
		
		(*linhaAtual) = novaLinha;
	}
}

int CountCaracteresLine(Linha ** linhaAtual) {
	/* Inicialmente todas as linhas tem 0 caracteres, então: */
	int i = 0;
	Caractere * aux = (*linhaAtual)->Inicio;
	
	/*  */
	if (aux != NULL) 
	{

		while (aux != NULL)
		{
			if(aux->Letra != '\n')
				i++;
			aux = aux->Proxima;
		}
	}
	return i;
}

void InserirCaractere(char letra, Caractere ** atual, Linha ** linhaAtual){
	Caractere * novo = (Caractere *)malloc(sizeof(Caractere));
	novo->Letra = letra;
	novo->Proxima = NULL;
	novo->Anterior = NULL;

	//Inserção no inicio
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
		//Inserção no fim
		if ((*atual)->Proxima == NULL) {
			(*atual)->Proxima = novo;
			novo->Anterior = (*atual);
			(*atual) = novo;
		}
		else
		{
			//Inserção no meio
			novo->Anterior = (*atual);
			novo->Proxima = (*atual)->Proxima;

			(*atual)->Proxima->Anterior = novo;
			(*atual)->Proxima = novo;

			(*atual) = novo;
		}
	}
}

int DeletarCaractere(Linha ** linhaAtual, Caractere ** caractereAtual, Caractere ** caractereRemover) {
	Caractere * aux = (*caractereRemover);

	//Backspace
	if ((*caractereAtual) == (*caractereRemover)) 
	{
		if (aux == NULL) {
			if ((*linhaAtual)->Anterior == NULL)
				return;
			else
			{
				(*linhaAtual) = (*linhaAtual)->Anterior;
			}
		}
		else if ((*caractereRemover)->Letra != '\n') 
		{
			(*caractereAtual) = (*caractereAtual)->Anterior;
			(*caractereAtual)->Proxima = aux->Proxima;
			if (aux->Proxima != NULL)
				aux->Proxima->Anterior = (*caractereAtual);
			free(aux);
		}

	}
	//Delete
	else
	{
		if (aux == NULL) {
			return;
		}

		else if ((*caractereRemover)->Letra != '\n') 
		{
			(*caractereAtual)->Proxima = aux->Proxima;
			if (aux->Proxima != NULL)
				aux->Proxima->Anterior = (*caractereAtual);

			free(aux);
		}
	}
}