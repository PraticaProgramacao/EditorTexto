/*Autor: Rodrigo José
Descrição:
Cabeçalho das funções com seus respectivos comentarios.
*/

#include <stdio.h>

FILE Criar (char nome[]) {
FILE *arq;

arq = fopen(nome,"wt");

   if (arq == NULL)
   {
	printf("Erro ao criar o arquivo.\n");
	return;
   } else 
     {
    printf("Arquivo criado  com sucesso.\n");
    return *arq;
	 }
}

void Fechar (FILE *arq)
{
int status;
status = fclose(arq);

 if ( status == 0)
	 printf("Arquivo fechado com sucesso.\n");
 else
	 printf("Erro no fechamento do arquivo.\n");
}


void Gravar (FILE *arq,char conteudo[])
{
int status;
status=fputs(conteudo,arq);
 if (status == EOF)
	 printf("Erro na gravacao.\n");
 else
	 printf("Conteudo gravado com sucesso.\n");
}
 


