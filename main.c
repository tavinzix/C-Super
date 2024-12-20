#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

void menuGerencial(ListaProduto *lp);
void menuPDV(ListaProduto *lp);

int main() {
    int menu;
    ListaProduto lp;

    criaLista(&lp);	
    leArquivo(&lp);
    
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
                menuGerencial(&lp);
                break;
            case 2:
                limparTela();
                menuPDV(&lp);
                break;
                
            case 3:
            	
            	break;
        }
    } while (menu != 0);

    return 0;
}

void menuGerencial(ListaProduto *lp) {
    int menu, cod;
    Produto p;

    do {
        printf("\n === Funcoes Gerenciais === \n");
        printf("0. Voltar ao menu principal\n");      
        printf("1. Cadastrar Produto - Verificar nome com espaço\n");
        printf("2. Inserir Estoque\n");
        printf("3. Listar produtos cadastrados\n");
        printf("4. Busca produto especifico\n");
        printf("5. Excluir produto\n\n");
        printf("6. Analise de vendas - NADA FEITO\n\n");
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
                    	gravaArquivo(lp);
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

                if (lancaNota(lp, cod) == CODIGO_INEXISTENTE) {
                    limparTela();
                    printf("Produto nao encontrado\n");
                } else {
                    limparTela();
                    printf("Estoque do item atualizado!\n");
                    gravaArquivo(lp);
                }
                break;

            case 3:
                limparTela();
                exibe(lp);
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
					gravaArquivo(lp);
				}
				break;
			
			case 6:
				//ler dados do arquivo de venda
				break;
        }
    } while (menu != 0);
}

void menuPDV(ListaProduto *lp) {
    int menu, cod;
    float qtd;
    Produto p;
    do {
        printf("\n === PDV === \n");
        printf("0. Voltar ao Menu Principal\n");
        
        printf("\n\n\n pra empilhar vendas - gravar arquivo com a data e ter opcao de ver vendas de outro dia\n\n\n");
        
        printf("1. Vender Produto - empilhar vendas\n");
        printf("2. Fechar Caixa - NADA FEITO\n");
        printf("3. Listar produtos cadastrados\n");
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
			        
			        int resultado = vendaProduto(lp, &p, cod, qtd);
			
			        if (resultado == CODIGO_INEXISTENTE) {
			            limparTela();
			            printf("Produto nao encontrado\n");
			        } else if(resultado == SUCESSO){           
			            printf("Produto vendido com sucesso\n");
			            gravaArquivo(lp);
			        }
			    }
                break;

            case 2:
                printf("Fechar Caixa\n");
                break;

            case 3:
                limparTela();
                exibe(lp);
                break;
        }
    } while (menu != 0);
}

