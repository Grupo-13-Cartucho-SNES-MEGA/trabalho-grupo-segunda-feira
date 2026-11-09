#include <stdio.h>
#include <string.h>

struct Acessorio {
    int idAcessorio;
    char descricao[40];    
    char tipo[20];
    float custoReparo;
    int quantidadeEstoque;
    int emManutencao;      // 1 = Em manutencao, 0 = Disponivel
};
struct Acessorio estoqueAcessorios[50];
int totalAcessorios = 0;

void moduloAcessorios() {
    int opcaoAcessorio;
    do {
        printf("\n--- [MODULO 3: ACESSORIOS E MANUTENCAO (Luiz)] ---\n");
        printf("1. Cadastrar Acessorio (Controle, Cabo, Adaptador)\n");
        printf("2. Consultar Estoque / Itens em Manutencao\n");
        printf("3. Atualizar Quantidade ou Custo de Reparo\n");
        printf("4. Dar Baixa / Remover Item Danificado\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoAcessorio);
 
        switch (opcaoAcessorio) {
            case 1:
                printf("\n[Em construcao] Cadastro de acessorio (Controles, Cabos AV)...\n");
                break;
            case 2:
                printf("\n[Em construcao] Listando estoque e itens em manutencao...\n");
                break;
            case 3:
                printf("\n[Em construcao] Editando quantidade em estoque / custo de reparo...\n");
                break;
            case 4:
                printf("\n[Em construcao] Baixa de acessorio danificado...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Acessorios!\n");
        }
    } while (opcaoAcessorio != 0);
}

int main() {
    moduloAcessorios();
    return 0;
}
