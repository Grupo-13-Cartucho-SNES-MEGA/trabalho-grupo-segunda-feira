#include <stdio.h>
#include <string.h>
 
// ===========================================================================
// MODELAGEM DE DADOS (Catalogo de Cartuchos) Samarah Tamy de Paula Moura (04976909-0)
// ===========================================================================
struct Cartucho {
    int idCartucho;
    char titulo[50];
    char console[20];      // "SNES" ou "Mega Drive"
    float valorDiaria;
    int copiasDisponiveis;
    int ativo;             // 1 = No acervo, 0 = Removido
};
struct Cartucho catalogoCartuchos[50];
int totalCartuchos = 0;

void moduloCartuchos() {
    int opcaoCartucho;
    do {
        printf("\n--- [MODULO 2: CATALOGO DE CARTUCHOS (Samarah)] ---\n");
        printf("1. Cadastrar Novo Cartucho\n");
        printf("2. Listar Acervo / Buscar Jogo\n");
        printf("3. Alterar Diaria ou Copias do Cartucho\n");
        printf("4. Excluir Cartucho do Acervo\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoCartucho);
 
        switch (opcaoCartucho) {
            case 1:
                printf("\n[Em construcao] Cadastrando Cartucho (ID, Titulo, Console, Diaria)...\n");
                break;
            case 2:
                printf("\n[Em construcao] Listando todos os cartuchos do acervo...\n");
                break;
            case 3:
                printf("\n[Em construcao] Atualizando diaria ou copias disponiveis...\n");
                break;
            case 4:
                printf("\n[Em construcao] Removendo cartucho fora do acervo...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Cartuchos!\n");
        }
    } while (opcaoCartucho != 0);
}
 
int main() {
    moduloCartuchos();
    return 0;
}
