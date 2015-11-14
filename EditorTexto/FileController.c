/*Autor: Rodrigo José
Descrição:
Cabeçalho das funções com seus respectivos comentarios.
*/
#include "FileController.h"

FILE * Criar(char nome[]) {
	FILE *arq;
	arq = fopen(nome, "w+");
	return arq;
}

void Fechar(FILE *arq)
{
	int status;
	status = fclose(arq);

	if (status == 0)
		printf("Arquivo fechado com sucesso.\n");
	else
		printf("Erro no fechamento do arquivo.\n");
}


FILE * Abrir(char nome[])
{
	FILE * arq;
	int status;
	arq = fopen(nome, "r");
	return arq;
}



int Salvar(Linha ** Texto, char fileDir[200]) {
	FILE * arq = Criar(fileDir);
	if (arq == NULL)
		return FAILURE;
	Linha * lAux = (*Texto);
	Caractere * cAux;
	while (lAux != NULL)
	{
		cAux = lAux->Inicio;
		while (cAux != NULL)
		{
			fputc(cAux->Letra, arq);
			cAux = cAux->Proxima;
		}
		lAux = lAux->Proxima;
	}
	if (fclose(arq) == 0)
		return SUCESSO;
	else return FAILURE;
}