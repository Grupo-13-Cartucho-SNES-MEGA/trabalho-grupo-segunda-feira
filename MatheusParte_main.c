#include <stdio.h>
#include <stdlib.h>

// 1. Matheus Martins de Souza (04924767-1) : Clientes da Locadora
struct Cliente {
    int idCliente;
    char nome[50];
    char telefone[20];
    float saldoDevedor;
    int ativo; 
};
struct Cliente listaClientes[50];
int totalClientes = 0;

void moduloClientes() {
    int opcaoCliente;
    do {
        printf("\n--- [MODULO 1: GESTAO DE CLIENTES (Matheus)] ---\n");
        printf("1. Cadastrar Novo Cliente\n");
        printf("2. Listar / Buscar Clientes\n");
        printf("3. Editar Dados ou Saldo do Cliente\n");
        printf("4. Remover Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoCliente);
 
        switch (opcaoCliente) {
            case 1:
                printf("\n[Em construcao] Rotina de Cadastro de Cliente...\n");
                printf("Campos previstos: ID, Nome, Telefone e Saldo Devedor.\n");
                break;
            case 2:
                printf("\n[Em construcao] Rotina de Busca e Listagem de Clientes...\n");
                break;
            case 3:
                printf("\n[Em construcao] Rotina de Edicao de Cliente por ID...\n");
                break;
            case 4:
                printf("\n[Em construcao] Rotina de Remocao de Cliente...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Clientes!\n");
        }
    } while (opcaoCliente != 0);
}
int main() {
   moduloClientes();
    return 0;
}
 
