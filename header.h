#ifndef header_H
#define header_H

#define SUCESSO 0
#define LISTA_VAZIA 1
#define FALTOU_MEMORIA 2
#define CODIGO_INEXISTENTE 3
#define SEM_ESTOQUE 4

#define PILHA_VAZIA 5

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

typedef struct {
	Nodo *topo;

} PilhaProduto;

void criaLista(ListaProduto *lp);
void criaPilha(PilhaProduto *pp);


int cadastraProduto(ListaProduto *lp, Produto p);
int lancaNota(ListaProduto *lp, int cod);
void exibe(ListaProduto *lp);
int consultaPorCodigo(ListaProduto *lp, int cod);
int quantidadeDeNodos(ListaProduto *lp);
int excluiProduto(ListaProduto *lp, Produto *p, int cod);

int vendaProduto(ListaProduto *lp, PilhaProduto *pp, Produto *p, int cod, float qtd);


int vendaDiaria(PilhaProduto *pp, Produto p);
void listaVendas(PilhaProduto *pp);


//int fechaCaixa(ListaProduto *lp);
int gravaArquivo(ListaProduto *lp);
int leArquivo(ListaProduto *lp);

void data();

void barran();
void limparTela();

#endif
