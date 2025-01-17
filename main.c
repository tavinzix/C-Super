#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

void menuGerencial(ListaProduto *lp, PilhaProduto *pp);
void menuPDV(ListaProduto *lp, PilhaProduto *pp);

int main() {
    int menu;
    ListaProduto lp;
    PilhaProduto pp;

    criaLista(&lp);	
    criaPilha(&pp);
    leProduto(&lp);
    leVendas(&pp);
    
    printf("  ####              #####   ##  ##   #####    ######   #####\n");
	printf(" ##  ##            ###      ##  ##   ##  ##   ##       ##  ##\n");
	printf(" ##       ######    ###     ##  ##   ##  ##   ####     ##  ##\n");
	printf(" ##                  ###    ##  ##   #####    ##       #####\n");
	printf(" ##  ##               ###   ##  ##   ##       ##       ## ##\n");
	printf(" ####              #####     ####    ##       ######   ##  ##\n");
		
    do {
		printf("\n=== Menu Principal ===\n");    
        printf("0. Sair\n");
        printf("1. Funcoes Gerenciais\n");
        printf("2. PDV\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                limparTela();
                menuGerencial(&lp, &pp);
                break;
            case 2:
                limparTela();
                menuPDV(&lp, &pp);
                break;
        }
    } while (menu != 0);

    return 0;
}

void menuGerencial(ListaProduto *lp, PilhaProduto *pp) {
    int menu, cod;
    char data[9];
    Produto p;

    do {
        printf("\n === Funcoes Gerenciais === \n");
        printf("0. Voltar ao menu principal\n");      
        printf("1. Cadastrar Produto\n");
        printf("2. Inserir Estoque\n");
        printf("3. Listar produtos cadastrados\n");
        printf("4. Busca produto especifico\n");
        printf("5. Excluir produto\n");
        printf("6. Analise de vendas\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                printf("Codigo: "); scanf("%d", &p.cod);

                printf("Descricao: ");
                getchar();
                fgets(p.nome, sizeof(p.nome), stdin);
                p.nome[strcspn(p.nome, "\n")] = 0;

                printf("Preco: "); scanf("%f", &p.preco);
                printf("Estoque: "); scanf("%f", &p.estoque);
                
                if(p.cod == 0){
                	printf("impossivel cadastrar codigo 0\n");
                	break;
				}
                
                if(consultaPorCodigo(lp, p.cod) == CODIGO_INEXISTENTE){               	
                	if (cadastraProduto(lp, p) == SUCESSO) {
                    	limparTela();
                    	printf("Operacao Realizada com Sucesso!\n");
                    	gravaProduto(lp);
                	} else {
                    	limparTela();
                    	printf("Operacao NAO realizada: Faltou Memoria!\n");
                	}
				}else{
					printf("Produto ja existe\n");
				}
				   
                break;

            case 2:
                printf("Digite o codigo: "); scanf("%d", &cod);

                if (atualizaEstoque(lp, cod) == CODIGO_INEXISTENTE) {
                    limparTela();
                    printf("Produto nao encontrado\n");
                } else {
                    limparTela();
                    printf("Estoque do item atualizado!\n");
                    gravaProduto(lp);
                }
                break;

            case 3:
                limparTela();
                listaProdutos(lp);
                break;

            case 4:
            	printf("Digite o codigo: "); scanf("%d", &cod);

                if (consultaPorCodigo(lp, cod) == CODIGO_INEXISTENTE) {
                    limparTela();
                    printf("Produto nao encontrado\n");
                }
                break;
                
            case 5:
            	printf("Digite o codigo: "); scanf("%d", &cod);
				
				if(excluiProduto(lp, &p, cod) == CODIGO_INEXISTENTE){
					limparTela();
					printf("Produto nao encontrado\n");
				}else{
					limparTela();
					printf("Produto excluido\n\n");
					printf("Cod: %d\nDescricao: %s\nPreco: %.2f\nEstoque %.2f\n", p.cod, p.nome, p.preco, p.estoque);
					gravaProduto(lp);
				}
				break;
			
			case 6:
				printf("Digite a data que deseja buscar as vendas\nFormato DDMMYYYY\n\n"); scanf("%s", data);
				
				int resultado = buscaVendas(pp, data);

				if (resultado == LISTA_VAZIA) {
    				limparTela();
   					printf("Nao foram encontradas vendas no dia informado\n");
				} else if(resultado == FALTOU_MEMORIA){
					printf("Nao foi possivel buscar as vendas");
				}
				break;
        }
    } while (menu != 0);
}

void menuPDV(ListaProduto *lp, PilhaProduto *pp) {
    int menu, cod;
    float qtd;
    Produto p;
    do {
        printf("\n === PDV === \n");
        printf("0. Voltar ao Menu Principal\n");
      	printf("1. Vender Produto\n");
        printf("2. Listar Vendas\n");
        printf("3. Listar produtos cadastrados\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
            	printf("\nDigite o codigo do produto e a quantidade.\nPara encerrar, digite 0.\n\n");   
                
                while (1) {
			      	printf("Codigo do item: "); scanf("%d", &cod);
			      	
			        if (cod == 0) {
			            break;
			        }

			        printf("Digite a quantidade: "); scanf("%f", &qtd);
			        
			        if(qtd <= 0){
			        	limparTela();
			        	printf("Informe uma quantidade valida\n");
			        	break;
					}
			        
			        int resultado = vendaProduto(lp, pp, &p, cod, qtd);
			
			        if (resultado == CODIGO_INEXISTENTE) {
			            limparTela();
			            printf("Produto nao encontrado\n");
			        } else if(resultado == SUCESSO){           
			            printf("Produto vendido com sucesso\n");
			            gravaProduto(lp);
			        }
			    }
                break;

            case 2:
                limparTela();
                listaVendas(pp);
                break;

            case 3:
                limparTela();
                listaProdutos(lp);
                break;
        }
    } while (menu != 0);
}
