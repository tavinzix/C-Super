#ifndef header_H
#define header_H

#define SUCESSO 0
#define LISTA_VAZIA 1
#define FALTOU_MEMORIA 2
#define CODIGO_INEXISTENTE 3
#define SEM_ESTOQUE 4

typedef struct {
    int cod;
    char nome[50];
    float preco;
    float estoque;
} Produto;
        
typedef struct nodo Nodo;

struct nodo {
    Produto info;
    Nodo *prox;
};

typedef struct {
	Nodo *inicio;
} ListaProduto;

void criaLista(ListaProduto *lp);

int cadastraProduto(ListaProduto *lp, Produto p);
int lancaNota(ListaProduto *lp, int cod);
void exibe(ListaProduto *lp);
int consultaPorCodigo(ListaProduto *lp, int cod);
int quantidadeDeNodos(ListaProduto *lp);
int excluiProduto(ListaProduto *lp, Produto *p, int cod);

int vendaProduto(ListaProduto *lp, Produto *p, int cod, float qtd);
int vendaDiaria(ListaProduto *lp);

int fechaCaixa(ListaProduto *lp);
int gravaArquivo(ListaProduto *lp);
int leArquivo(ListaProduto *lp);

void barran();
void limparTela();

#endif
