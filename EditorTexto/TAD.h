/* A linha é uma lista duplamente encadeada, para facilitar a movimentação do cursor entre os caracteres */
#define DELETE_FAILURE		0
#define DELETE_SUCESS		1
#define DELETE_CONCATENADO	2

typedef struct TCaractere {
	char Letra;
	struct TCaractere * Proxima;
	struct TCaractere * Anterior;
}Caractere;

/* A linha é uma lista duplamente encadeada, para facilitar a troca de linha */
typedef struct TLinha {
	struct TLinha * Proxima;
	struct TLinha * Anterior;
	Caractere * Inicio; //Indica o início da linha
}Linha;

void InserirNovaLinha(Linha ** Texto, Linha ** linhaAtual, Caractere ** atual, int * posColuna);
void InserirCaractere(char letra, Caractere ** atual, Linha ** linhaAtual);
int CountCaracteresLine(Linha ** linhaAtual);
int DeletarCaractere(Linha ** linhaAtual, Caractere ** caractereAtual, Caractere ** caractereRemover);
void DestruirTexto(Linha ** Texto, Linha ** linhaAtual, Caractere ** caracterAtual, int * LinhaAtual, int * ColunaAtual);

int DeletarCaractereAtual(Linha ** linhaAtual, Caractere ** caracterAtual);
int DeletarProximoCaractere(Linha ** linhaAtual, Caractere ** caracterAtual, Caractere * prox);
void ConcatenarBackspace(Linha ** linhaAtual);
//void Concatenar(Linha ** linhaSuperior, Linha ** linhaInferior, Linha ** linhaAtual);