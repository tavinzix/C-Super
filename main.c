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
                menuGerencial(&lp);
                break;
            case 2:
                limparTela();
                menuPDV(&lp);
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
        
        printf("\n\n\n quando entrar aqui ler os dados do txt. quando sair, gravar os dados\n\n\n");
        
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

                if (cadastraProduto(lp, p) == SUCESSO) {
                    limparTela();
                    printf("Operacao Realizada com Sucesso!\n");
                } else {
                    limparTela();
                    printf("Operacao NAO realizada: Faltou Memoria!\n");
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
				}
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
        
        printf("1. Vender Produto\n");
        printf("2. Fechar Caixa\n");
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

