#include <stdio.h>
#include <stdlib.h>

// 4.Rodrigo lopes Miguel (04912504-4): Locacoes e Relatorios

struct Locacao {
    int idLocacao;
    int idClienteLocador;
    int idCartuchoAlugado;
    int diasAluguel;
    float valorTotal;
    int devolvido;        
};
struct Locacao historicoLocacoes[50];
int totalLocacoes = 0;

void moduloLocacoesRelatorios() {
    int opcaoLocacao;
    do {
        printf("\n--- [MODULO 4: LOCACOES E RELATORIOS (Rodrigo)] ---\n");
        printf("1. Registrar Nova Locacao (Cruza Cliente + Cartucho)\n");
        printf("2. Listar Historico de Locacoes\n");
        printf("3. Registrar Devolucao / Cancelar Locacao\n");
        printf("4. [RELATORIO] Cartucho Mais Alugado\n");
        printf("5. [RELATORIO] Cliente com Mais Locacoes\n");
        printf("6. [RELATORIO] Locacoes Realizadas por um Cliente Especifico\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoLocacao);
 
        switch (opcaoLocacao) {
            case 1:
                printf("\n[Em construcao] Lancamento de locacao vinculando ID Cliente e ID Cartucho...\n");
                break;
            case 2:
                printf("\n[Em construcao] Exibindo todas as locacoes registradas...\n");
                break;
            case 3:
                printf("\n[Em construcao] Devolucao / cancelamento de locacao por ID...\n");
                break;
            case 4:
                printf("\n[Em construcao] Calculando ranking do cartucho mais alugado...\n");
                break;
            case 5:
                printf("\n[Em construcao] Identificando cliente com mais locacoes...\n");
                break;
            case 6:
                printf("\n[Em construcao] Filtrando locacoes por ID de cliente...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Locacoes!\n");
        }
    } while (opcaoLocacao != 0);
}

int main() {
    moduloLocacoesRelatorios();
    return 0;
}
