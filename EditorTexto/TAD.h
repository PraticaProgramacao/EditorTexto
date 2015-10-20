/* A linha � uma lista duplamente encadeada, para facilitar a movimenta��o do cursor entre os caracteres */
typedef struct TCaractere {
	char Letra;
	struct TCaractere * Proxima;
	struct TCaractere * Anterior;
}Caractere;

/* A linha � uma lista duplamente encadeada, para facilitar a troca de linha */
typedef struct TLinha {
	struct TLinha * Proxima;
	struct TLinha * Anterior;
	Caractere * Inicio; //Indica o in�cio da linha
}Linha;

void InserirNovaLinha(Linha * texto, int * posLinha, int * qntLinha);
void QuebrarLinha(Linha * texto, int * posLinha, int * qntLinha);