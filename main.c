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
		
	barran();

    do {
		printf("\n=== Menu Principal ===\n");    
        printf("0. Sair\n");
        printf("1. Funcoes Gerenciais\n");
        printf("2. PDV\n");
        printf("3. debug\n");
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
                
            case 3:
            	//data();
            	break;
        }
    } while (menu != 0);

    return 0;
}

void menuGerencial(ListaProduto *lp, PilhaProduto *pp) {
    int menu, cod;
    Produto p;

    do {
        printf("\n === Funcoes Gerenciais === \n");
        printf("0. Voltar ao menu principal\n");      
        printf("1. Cadastrar Produto - Verificar nome com espaco\n");
        printf("2. Inserir Estoque\n");
        printf("3. Listar produtos cadastrados\n");
        printf("4. Busca produto especifico\n");
        printf("5. Excluir produto\n\n");
        printf("6. Analise de vendas - LISTAR VENDAS PELO TXT\n\n");
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
				//ler dados do arquivo de venda
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
        
        printf("\n\n\n pra empilhar vendas - gravar arquivo com a data e ter opcao de ver vendas de outro dia\n\n\n");
        
        printf("1. Vender Produto - SALVAR PILHA EM TXT\n");
        printf("2. Listar Vendas - LISTAR VENDAS NA DATA\n");
        printf("3. Listar produtos cadastrados\n");
        printf("4. debug\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
            	printf("Digite o codigo do produto e a quantidade. Para encerrar, digite 0.\n\n");   
                
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
                //listaVendas(pp);
                break;

            case 3:
                limparTela();
                listaProdutos(lp);
                break;
                
            case 4:
            	
			    break;
        }
    } while (menu != 0);
}

