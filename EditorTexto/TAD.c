#include "TAD.h"



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