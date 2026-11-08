#include <stdio.h>
#include <stdlib.h>

//Apagar depois essa parte, só para ver se iria funcionar

void exibirCabecalho()            { printf("\n=== RETRO CARTRIDGE RENTAL ===\n"); }
void moduloClientes()             { printf("\n[teste] Clientes\n"); }
void moduloCartuchos()            { printf("\n[teste] Cartuchos\n"); }
void moduloAcessorios()           { printf("\n[teste] Acessorios\n"); }
void moduloLocacoesRelatorios()   { printf("\n[teste] Locacoes\n"); }

//Esse bloco era só para testar o menu - lemb de apagar

int main() {
    int opcaoPrincipal;
 
    do {
        exibirCabecalho();
        printf("SELECIONE A PERSPECTIVA DO SISTEMA:\n");
        printf("1. Modulo de Clientes (Matheus)\n");
        printf("2. Modulo de Catalogo de Cartuchos (Samarah)\n");
        printf("3. Modulo de Acessorios e Manutencao (Luiz)\n");
        printf("4. Modulo de Locacoes e Relatorios (Rodrigo)\n");
        printf("0. Encerrar o Sistema\n");
        printf("-------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcaoPrincipal);
 
        switch (opcaoPrincipal) {
            case 1:
                moduloClientes();
                break;
            case 2:
                moduloCartuchos();
                break;
            case 3:
                moduloAcessorios();
                break;
            case 4:
                moduloLocacoesRelatorios();
                break;
            case 0:
                printf("\nEncerrando o sistema Retro Cartridge Rental... Ate logo!\n");
                break;
            default:
                printf("\n[ALERTA] Opcao invalida! Digite um numero de 0 a 4.\n");
        }
    } while (opcaoPrincipal != 0);
 
    return 0;
}
