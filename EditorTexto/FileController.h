/*Autor: Rodrigo Jos�
Descri��o:
Cabe�alho das fun��es com seus respectivos comentarios.
*/
FILE Criar (char nome[]); /*Cria um arquivo de texto,passando o nome do arquivo*/
	
void Fechar (FILE *arq);/*Fecha um arquivo,passando o mesmo*/

void GravarString (FILE *arq,char conteudo[]);/*Grava um conteudo(String) no arquivo de texto,passando o arquivo e o conteudo*/

void AbrirGravar (char nome[]);/*Abrir um arquivo para grava��o,passando o nome do arquivo*/

void AbrirLer (char nome[]);/*Abrir um arquivo para leitura,passando o nome do arquivo*/

void GravarCaracter (FILE *arq ,char c);/*Grava um caracter no arquivo de texto,passando o arquivo e o caracter*/

void Remover (char nome[]);/*Remover o arquivo,passando o nome do arquivo*/