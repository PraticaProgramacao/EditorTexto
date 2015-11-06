#include "TAD.h"
#include <stdio.h>


//Not implemented fully (yet)
void InserirNovaLinha(Linha * texto, int * posLinha, int * qntLinha) {
	int i = 0;
	Linha * novaLinha;
	//Percorre até a posição do ponteiro
	for (texto; i < posLinha; texto = texto->Proxima, i++);

	//Aloca a nova linha
	novaLinha = (Linha *)malloc(sizeof(Linha));

	//Coloca a nova linha no local correto
	novaLinha->Proxima = texto->Proxima;
	texto->Proxima = novaLinha;
	novaLinha->Anterior = texto;

}

void InserirCaractere(char letra, Caractere ** atual, Linha ** linhaAtual){
	Caractere * novo = (Caractere *)malloc(sizeof(Caractere));
	novo->Letra = letra;
	novo->Proxima = NULL;
	novo->Anterior = NULL;


	if ((*atual) == NULL)
	{
		*atual = novo;
		(*linhaAtual)->Inicio = (*atual);
	}
	else
	{
		if ((*atual)->Anterior == NULL && (*atual)->Proxima != NULL) {
			novo->Proxima = atual;
			(*atual) = novo;
		}
		else if ((*atual)->Proxima == NULL) {
			(*atual)->Proxima = novo;
			(*atual) = novo;
		}
		else
		{
			novo->Anterior = (*atual);
			novo->Proxima = (*atual)->Proxima;
			(*atual) = novo;
		}
	}
	
}