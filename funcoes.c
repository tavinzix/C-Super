#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void criaLista(ListaProduto *lp){
	lp->inicio = NULL;
}

int cadastraProduto(ListaProduto *lp, Produto p){
	Nodo *pNodo;
    pNodo = (Nodo *) malloc (sizeof (Nodo));
    if (pNodo == NULL){
    	return(FALTOU_MEMORIA);
	}
    else {
    	pNodo->info = p; 
    	pNodo->prox = NULL;	
    	if (lp->inicio == NULL) {
        	lp->inicio = pNodo;
	    }else {
			Nodo *atual = lp->inicio;
	        while (atual->prox != NULL) {
	            atual = atual->prox;
	        }
	        atual->prox = pNodo;
    }
		return(SUCESSO);
    }
}

int lancaNota(ListaProduto *lp, int cod){
	float estoque;
	Nodo *atual = lp->inicio;

    while (atual != NULL) {
        if (atual->info.cod == cod) {
        	printf("Digite o estoque: "); scanf("%f", &estoque);
			atual->info.estoque += estoque;
            return SUCESSO;
        }
        atual = atual->prox;
    }
    return CODIGO_INEXISTENTE;
}

void exibe(ListaProduto *lp){
	 Nodo *pAux = lp->inicio;
    printf("Cadastro de produtos:\n");
    printf("[codigo] [descricao] [preco]  [estoque]\n");
    while (pAux != NULL) {
        printf("%d %s %.2f %.2f\n", pAux->info.cod, pAux->info.nome, pAux->info.preco, pAux->info.estoque);
        pAux = pAux->prox;
    }
}

int vendaProduto(ListaProduto *lp, Produto *p, int cod, float qtd){
	Nodo *atual = lp->inicio;

    while (atual != NULL) {
        if (atual->info.cod == cod) {
            if (atual->info.estoque >= qtd) {
                atual->info.estoque -= qtd;
                return SUCESSO;
            } else {
            	printf("Estoque insuficiente para venda\n");
            	printf("Estoque disponivel: %f\n", atual->info.estoque);
                return SEM_ESTOQUE;
            }
        }
        atual = atual->prox;
    }
    return CODIGO_INEXISTENTE;
    
    //empilhar vendas
}

int consultaPorCodigo(ListaProduto *lp, int cod){
	Nodo *atual = lp->inicio;
	while(atual != NULL){
		if(atual->info.cod == cod){
			limparTela();
			printf("Dados do item %d\n\n", cod);
			printf("Descricao: %s\n", atual->info.nome);
			printf("Preco: %2.f\n", atual->info.preco);
			printf("Estoque: %f\n", atual->info.estoque);
			return SUCESSO;
		}
		atual = atual->prox;
	}
	return CODIGO_INEXISTENTE;
}

int vendaDiaria(ListaProduto *lp){
	//le vendas do dia e mostra dados do item ou total- lendo txt
}

int fechaCaixa(ListaProduto *lp){
	//soma as vendas do dia
}

int excluiProduto(ListaProduto *lp, Produto *p, int cod){
	Nodo *atual = lp->inicio;
    Nodo *anterior = NULL;

    while (atual != NULL) {
        if (atual->info.cod == cod) {
            *p = atual->info;
            
            if (anterior == NULL) {
                lp->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return SUCESSO;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return CODIGO_INEXISTENTE;
}

int gravaArquivo(ListaProduto lp){
	
}

int leArquivo(ListaProduto *lp){
	
}

void barran(){
	printf("\n\n");
}

void limparTela() {
//	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

   	#ifdef _WIN32
       system("cls");
    #else
        system("clear");
    #endif
}
