#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "header.h"

void criaLista(ListaProduto *lp){
	lp->inicio = NULL;
}

void criaPilha(PilhaProduto *pp) {
    pp->topo = NULL;
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

int atualizaEstoque(ListaProduto *lp, int cod){
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

void listaProdutos(ListaProduto *lp){
	 Nodo *pAux = lp->inicio;
    printf("Cadastro de produtos:\n");
    printf("[codigo] [descricao] [preco]  [estoque]\n");
    while (pAux != NULL) {
        printf("%d %s %.2f %.2f\n", pAux->info.cod, pAux->info.nome, pAux->info.preco, pAux->info.estoque);
        pAux = pAux->prox;
    }
}

int quantidadeProdutos(ListaProduto *lp){
    int conta=0;
    Nodo *pAux;
    
    pAux = lp->inicio;
    while (pAux != NULL) {
           conta++;
           pAux = pAux->prox;
    }
    return(conta);
}

int vendaProduto(ListaProduto *lp, PilhaProduto *pp, Produto *p, int cod, float qtd){
	Nodo *atual = lp->inicio;

    while (atual != NULL) {
        if (atual->info.cod == cod) {
            if (atual->info.estoque >= qtd) {
                atual->info.estoque -= qtd;
                
				*p = atual->info;
                p->estoque = qtd;                
                Produto venda = *p;
                vendaDiaria(pp, venda);
            	gravaVenda(pp);
				              
                return SUCESSO;
            } else{
			  	printf("Estoque insuficiente para venda\n");
            	printf("Estoque disponivel: %f\n", atual->info.estoque);
                return SEM_ESTOQUE;
            }
        }
        atual = atual->prox;
    }
    return CODIGO_INEXISTENTE;
}

int consultaPorCodigo(ListaProduto *lp, int cod){
	Nodo *atual = lp->inicio;
	while(atual != NULL){
		if(atual->info.cod == cod){
			limparTela();
			printf("Dados do item %d\n\n", cod);
			printf("Descricao: %s\n", atual->info.nome);
			printf("Preco: %.2f\n", atual->info.preco);
			printf("Estoque: %f\n", atual->info.estoque);
			return SUCESSO;
		}
		atual = atual->prox;
	}
	return CODIGO_INEXISTENTE;
}

int vendaDiaria(PilhaProduto *pp, Produto p) {
    Nodo *novoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (novoNodo == NULL) {
        return FALTOU_MEMORIA;
    }
		
	novoNodo->info = p;
    novoNodo->prox = pp->topo;
    pp->topo = novoNodo;

    return SUCESSO;
}

void listaVendas(PilhaProduto *pp) {
	float totalVenda;
    if (pp->topo == NULL) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    Nodo *atual = pp->topo;
    printf("Vendas registradas:\n");
    while (atual != NULL) {
        printf("Codigo: %d, Nome: %s, Quantidade vendida: %.2f, Preco unitario: %.2f\n\n", atual->info.cod, atual->info.nome, atual->info.estoque, atual->info.preco);
        totalVenda += (atual->info.preco * atual->info.estoque);
        atual = atual->prox;
    }
    printf("Vendas totais: %f", totalVenda);
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

int buscaVendas(PilhaProduto *pp, char data[9]) {
    FILE *arq;
    char dadosPilha[200];
    Produto p;
    float totalVenda = 0.0;
    Nodo *atual = pp->topo;
    Nodo *temp;
    
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    pp->topo = NULL;

    strcat(data, ".txt");
    arq = fopen(data, "r");

    if (arq == NULL) {
        return LISTA_VAZIA;
    }

    while (fgets(dadosPilha, sizeof(dadosPilha), arq)) {
        if (sscanf(dadosPilha, "%d %49s %f %f", &p.cod, p.nome, &p.estoque, &p.preco) == 4) {
            Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
            if (novo == NULL) {
                fclose(arq);
                return FALTOU_MEMORIA;
            }

            novo->info = p;
            novo->prox = pp->topo;
            pp->topo = novo;
        }
    }

    fclose(arq);

    atual = pp->topo;

	limparTela();
    printf("Vendas registradas:\n");
    while (atual != NULL) {
        printf("Codigo: %d, Nome: %s, Quantidade vendida: %.2f, Preco unitario: %.2f\n", atual->info.cod, atual->info.nome, atual->info.estoque, atual->info.preco);
        totalVenda += atual->info.preco * atual->info.estoque;
        atual = atual->prox;
    }
    printf("Vendas totais: %.2f\n", totalVenda);

    return SUCESSO;
}

int gravaProduto(ListaProduto *lp){
	FILE *arq;
    Nodo *pAux = lp->inicio;
    arq = fopen("listaProduto.txt", "w");
    fprintf(arq, "[codigo] [descricao] [preco]  [estoque]\n");

    while (pAux != NULL) {
        fprintf(arq, "%d %s %.2f %.2f\n", pAux->info.cod, pAux->info.nome, pAux->info.preco, pAux->info.estoque);
        pAux = pAux->prox;
    }
    fclose(arq);
    return SUCESSO;
}

int leProduto(ListaProduto *lp) {
    FILE *arq;
    char dadosLista[200];
    Produto p;

    arq = fopen("listaProduto.txt", "r");

    while (quantidadeProdutos(lp) > 0) {
        Produto temp;
        excluiProduto(lp, &temp, lp->inicio->info.cod);
    }

    while (fgets(dadosLista, sizeof(dadosLista), arq)) {
        if (sscanf(dadosLista, "%d %80s %f %f", &p.cod, p.nome, &p.preco, &p.estoque) == 4) {
            cadastraProduto(lp, p);
        }
    }

    fclose(arq);
    return SUCESSO;
}

int gravaVenda(PilhaProduto *pp){
	FILE *arq;
    Nodo *atual = pp->topo;

 	struct tm *p;
    char data[9];
    time_t seconds;

    time(&seconds);
    p = localtime(&seconds);

    sprintf(data, "%02d%02d%04d", p->tm_mday, p->tm_mon + 1, p->tm_year + 1900);
	strcat(data, ".txt");
  
    arq = fopen(data, "w");
    
    fprintf(arq, "[codigo] [descricao] [qtd vendida] [preco]\n");

    while (atual != NULL) {
        fprintf(arq, "%d %s %.2f %.2f\n", atual->info.cod, atual->info.nome, atual->info.estoque, atual->info.preco);
        atual = atual->prox;
    }
    
    fclose(arq);
    return SUCESSO;
}

int leVendas(PilhaProduto *pp) {
    FILE *arq;
    char dadosPilha[200];
    Produto p;

    struct tm *pData;
    char data[9];
    time_t seconds;

    time(&seconds);
    pData = localtime(&seconds);
    sprintf(data, "%02d%02d%04d", pData->tm_mday, pData->tm_mon + 1, pData->tm_year + 1900);
    strcat(data, ".txt");

    arq = fopen(data, "r");

    while (fgets(dadosPilha, sizeof(dadosPilha), arq)) {
        if (sscanf(dadosPilha, "%d %s %f %f", &p.cod, p.nome, &p.estoque, &p.preco) == 4) {
            vendaDiaria(pp, p);
        }
    }

    fclose(arq);
    return SUCESSO;
}

void limparTela() {
 	#ifdef _WIN32
       system("cls");
    #else
        system("clear");
    #endif
}
