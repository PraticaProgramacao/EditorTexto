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
		novaLinha->Proxima  = (*linhaAtual);
		if((*linhaAtual)->Anterior != NULL)
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
		
		if((*linhaAtual)->Proxima != NULL)
			(*linhaAtual)->Proxima->Anterior = novaLinha;
		
		(*linhaAtual)->Proxima = novaLinha;
		(*atual) = NULL;
		
		(*linhaAtual) = novaLinha;
	}
}

int CountCaracteresLine(Linha ** linhaAtual) {
	/* Inicialmente todas as linhas tem 0 caracteres, ent�o: */
	int i = 0;
	Caractere * aux = (*linhaAtual)->Inicio;
	
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

int DeletarCaractereAtual(Linha ** linhaAtual, Caractere ** caracterAtual) {
	Caractere * toDelete = (*caracterAtual);
	//Juntar linhas (implementar)
	if (toDelete == NULL) 
	{
		Concatenar(&(*linhaAtual)->Anterior, linhaAtual, linhaAtual);
		return DELETE_FAILURE;
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
	if ((*caracterAtual) == NULL)
		toDelete = (*linhaAtual)->Inicio;
	else
		toDelete = (*prox);

	//Juntar linhas (implementar)
	if (toDelete == NULL)
		return DELETE_FAILURE;
	else
	{
		//Remo��o no meio
		if (toDelete->Proxima != NULL && toDelete->Anterior != NULL)
		{
			toDelete->Anterior->Proxima = toDelete->Proxima;
			toDelete->Proxima->Anterior = toDelete->Anterior;
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

void DestruirTexto(Linha ** Texto, Linha ** linhaAtual, Caractere ** caracterAtual, int * LinhaAtual, int * ColunaAtual){
	Linha * lAux = (*Texto), *lAuxProx;
	Caractere * cAux, *cAuxProx;

	while (lAux != NULL)
	{
		lAuxProx = lAux->Proxima;
		cAux = lAux->Inicio;
		while (cAux!=NULL)
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

/**/
void Concatenar(Linha ** linhaSuperior, Linha ** linhaInferior, Linha ** linhaAtual) {
	int count, i = 0;
	Caractere * aux;
	count = CountCaracteresLine(linhaSuperior);
	for (aux = (*linhaSuperior)->Inicio; i < (count -1) ; aux = aux->Proxima, i++);
	
	free(aux->Proxima);
	
	aux->Proxima = (*linhaInferior)->Inicio;
	(*linhaInferior)->Inicio->Anterior = aux;

	(*linhaSuperior)->Proxima = (*linhaInferior)->Proxima;
	
	if ((*linhaInferior)->Proxima != NULL)
		(*linhaInferior)->Proxima->Anterior = (*linhaSuperior);


	if ((*linhaAtual) != (*linhaSuperior)) 
		(*linhaAtual) = (*linhaSuperior);
	
	free((*linhaInferior));
}