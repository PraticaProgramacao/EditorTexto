/*Autor: Rodrigo José
Descrição:
Cabeçalho das funções com seus respectivos comentarios.
*/
#include "FileController.h"

FILE * Criar (char nome[]) {
	FILE *arq;
	arq = fopen(nome, "w+");

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



void Salvar(Linha ** Texto, char fileDir[200]) {
	FILE * arq = Criar(fileDir);
	Linha * lAux = (*Texto);
	Caractere * cAux;
	while (lAux != NULL)
	{
		cAux = lAux->Inicio;
		while (cAux != NULL)
		{
			if (fputc(cAux->Letra, arq) == cAux->Letra)
				printf("char adicionado com sucesso!");
			cAux = cAux->Proxima;
		}
		lAux = lAux->Proxima;
	}
	fclose(arq);
}