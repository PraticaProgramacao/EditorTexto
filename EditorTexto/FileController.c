/*Autor: Rodrigo José
Descrição:
Cabeçalho das funções com seus respectivos comentarios.
*/

#include <stdio.h>


FILE Criar (char nome[]) {
FILE *arq;

arq = fopen(nome,"w");

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
void GravarString (FILE *arq,char conteudo[])
{
int status;
status=fputs(conteudo,arq);
 if (status == EOF)
	 printf("Erro na gravacao.\n");
 else
	 printf("Conteudo gravado com sucesso.\n");
}
 
void AbrirGravar (char nome[])
{
FILE *arq;
int status;

arq =fopen(nome,"a");

if( arq == NULL)
 printf("Erro ao abrir o arquivo.\n");
else 
	printf("Arquivo aberto com sucesso.\n");
}


void AbrirLer (char nome[])
{
FILE *arq;
int status;

arq = fopen(nome,"r");

if (arq == NULL)
	printf("Erro ao abrir o arquivo.\n");
else
	printf("Arquivo aberto com sucesso.\n");
}

void GravarCaracter (FILE *arq ,char c)
{
int status;

status = fputc(c,arq);

if ( status == EOF)
	printf("Erro na gravacao.\n");
else
	printf("Caracter gravado com sucesso.\n");
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
