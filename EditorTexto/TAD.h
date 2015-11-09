/* A linha é uma lista duplamente encadeada, para facilitar a movimentação do cursor entre os caracteres */
#define DELETE_SUCESS	1
#define DELETE_FAILURE	0

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