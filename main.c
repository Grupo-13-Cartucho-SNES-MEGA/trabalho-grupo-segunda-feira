#include <stdio.h>
#include <string.h>

// ===========================================================================
// PROJETO: RETRO CARTRIDGE RENTAL - LOCADORA DE CARTUCHOS SNES / MEGA DRIVE
// Disciplina: Algoritmos e Pensamento Computacional - Checkpoint 1 
// Equipe: Matheus Martins de Souza (RGM 04924767-1) | Samarah Tamy de Paula Moura (RGM 04976909-0) | Luiz Melo Azevedo (RGM 04965754-2) | Rodrigo lopes Miguel (RGM 04912504-4)
// ===========================================================================

// ===========================================================================
// PARTE 1: MODELAGEM DE DADOS (ESCOPO GLOBAL - 1 STRUCT POR INTEGRANTE)
// ===========================================================================

// 1.Matheus Martins de Souza (04924767-1): Clientes da Locadora
struct Cliente {
    int idCliente;
    char nome[50];
    char telefone[20];
    float saldoDevedor;
    int ativo; 
};
struct Cliente listaClientes[50];
int totalClientes = 0;

// 2.Samarah Tamy de Paula Moura (04976909-0): Catalogo de Cartuchos
struct Cartucho {
    int idCartucho;
    char titulo[50];
    char console[20];      
    float valorDiaria;
    int copiasDisponiveis;
    int ativo;            
};
struct Cartucho catalogoCartuchos[50];
int totalCartuchos = 0;

// 3.Luiz Melo de Azevedo (04965754-2 ): Acessorios e Manutencao
struct Acessorio {
    int idAcessorio;
    char descricao[40];    
    char tipo[20];
    float custoReparo;
    int quantidadeEstoque;
    int emManutencao;     
};
struct Acessorio estoqueAcessorios[50];
int totalAcessorios = 0;

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

// ===========================================================================
// PARTE 2: Funcao Visual Comum
// ===========================================================================

void exibirCabecalho() {
    printf("\n=======================================================\n");
    printf("   RETRO CARTRIDGE RENTAL - LOCADORA SNES / MEGA DRIVE  \n");
    printf("=======================================================\n");
}

// ---------------------------------------------------------------------------
// MODULO 1: PERSPECTIVA DE CLIENTES
// Autor: 1.Matheus Martins de Souza (04924767-1)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// MODULO 2: PERSPECTIVA DO CATALOGO DE CARTUCHOS
// Autor: Samarah Tamy de Paula Moura (04976909-0)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// MODULO 3: PERSPECTIVA DE ACESSORIOS E MANUTENCAO
// Autor: Luiz Melo Azevedo (04965754-2)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// MODULO 4: PERSPECTIVA DE LOCACOES E RELATORIOS ANALITICOS (CRUZAMENTO DE DADOS)
// Autor: Rodrigo lopes Miguel (04912504-4)
// ---------------------------------------------------------------------------
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

// ===========================================================================
// PARTE 3: FUNCAO PRINCIPAL (MAIN) - DESPACHANTE DE MENUS
// ===========================================================================
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
