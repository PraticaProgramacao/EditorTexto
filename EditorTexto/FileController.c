/*Autor: Rodrigo José
Descrição:
Cabeçalho das funções com seus respectivos comentarios.
*/
#include "FileController.h"

FILE * Criar (char nome[]) {
	FILE *arq;
	arq = fopen(nome, "a+");

	if (arq == NULL)
		printf("Erro ao criar o arquivo.\n");
	else 
		printf("Arquivo criado  com sucesso.\n");
		
	return arq;
	
}

void Fechar (FILE *arq)
{
	int status;
	status = fclose(arq);

	if (status == 0)
		printf("Arquivo fechado com sucesso.\n");
	else
		printf("Erro no fechamento do arquivo.\n");
}
 

FILE * Abrir (char nome[])
{
	FILE * arq;
	int status;
	arq = fopen(nome,"r");
	return arq;
}


void Remover (char nome[])
{
	int status;

	status = remove(nome);
	if (status == 0)
		printf("Arquvo excluido com sucesso.\n");
	else
		printf("Erro ao excluir o arquivo.\n");
}

void Salvar(Linha ** Texto, char fileDir[200]) {
	FILE * arq = Criar(fileDir);
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
}