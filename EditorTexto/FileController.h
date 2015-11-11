/*Autor: Rodrigo José
Descrição:
Cabeçalho das funções com seus respectivos comentarios.
*/
#include <stdio.h>
#include "TAD.h"

FILE * Criar (char nome[]); /*Cria um arquivo de texto,passando o nome do arquivo*/
void Fechar (FILE *arq);/*Fecha um arquivo,passando o mesmo*/
FILE * Abrir (char nome[]);/*Abrir um arquivo para leitura,passando o nome do arquivo*/
void Salvar (Linha ** Texto, char fileDir[200]);/*Grava um caracter no arquivo de texto,passando o arquivo e o caracter*/
void Remover (char nome[]);/*Remover o arquivo,passando o nome do arquivo*/