/*Autor: Rodrigo José
Descrição:
Cabeçalho das funções com seus respectivos comentarios.
*/

FILE Criar (char nome[]); /*Cria um arquivo de texto,passando o nome do arquivo*/
	
void Fechar (FILE *arq);/*Fecha um arquivo,passando o mesmo*/

void Gravar (FILE *arq,char conteudo[]);/*Grava um conteudo em um arquivo de texto,passando o arquivo e o conteudo*/