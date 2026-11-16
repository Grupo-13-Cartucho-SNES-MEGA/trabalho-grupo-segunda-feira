// Arquivo: acessorios.h | Autor: Luiz Melo Azevedo (RGM 04965754-2)
// MODULO 3: ACESSORIOS E MANUTENCAO (persistencia em acessorios.csv)
#ifndef ACESSORIOS_H
#define ACESSORIOS_H

#include "utils.h"

#define MAX_ACESSORIOS 50

struct Acessorio {
    int idAcessorio;
    char descricao[40];
    char tipo[20];          
    float custoReparo;
    int quantidadeEstoque;  
    int emManutencao;        
};
struct Acessorio estoqueAcessorios[MAX_ACESSORIOS];
int totalAcessorios = 0;

// 1. PERSISTENCIA: regrava o vetor inteiro em acessorios.csv
void salvarAcessoriosCSV() {
    FILE *arq = fopen("acessorios.csv", "w");
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar acessorios.csv!\n");
        return;
    }
    for (int i = 0; i < totalAcessorios; i++) {
        fprintf(arq, "%d;%s;%s;%.2f;%d;%d\n",
                estoqueAcessorios[i].idAcessorio,
                estoqueAcessorios[i].descricao,
                estoqueAcessorios[i].tipo,
                estoqueAcessorios[i].custoReparo,
                estoqueAcessorios[i].quantidadeEstoque,
                estoqueAcessorios[i].emManutencao);
    }
    fclose(arq);
}

// 2. PERSISTENCIA: le acessorios.csv ao abrir o programa
void carregarAcessoriosCSV() {
    FILE *arq = fopen("acessorios.csv", "r");
    if (arq == NULL) return;
    totalAcessorios = 0;
    while (totalAcessorios < MAX_ACESSORIOS &&
           fscanf(arq, "%d;%39[^;];%19[^;];%f;%d;%d\n",
                  &estoqueAcessorios[totalAcessorios].idAcessorio,
                  estoqueAcessorios[totalAcessorios].descricao,
                  estoqueAcessorios[totalAcessorios].tipo,
                  &estoqueAcessorios[totalAcessorios].custoReparo,
                  &estoqueAcessorios[totalAcessorios].quantidadeEstoque,
                  &estoqueAcessorios[totalAcessorios].emManutencao) == 6) {
        totalAcessorios++;
    }
    fclose(arq);
}

// 3. Retorna a posicao do ID no vetor, ou -1
int buscarIndiceAcessorio(int idProcurado) {
    for (int i = 0; i < totalAcessorios; i++) {
        if (estoqueAcessorios[i].idAcessorio == idProcurado) return i;
    }
    return -1;
}

// 4. CADASTRO (trava de ID repetido + CSV)
void cadastrarAcessorio() {
    if (totalAcessorios >= MAX_ACESSORIOS) {
        printf("[ERRO] Estoque de acessorios lotado (%d)!\n", MAX_ACESSORIOS);
        return;
    }
    int id = lerInteiro("\nID do novo acessorio: ");
    if (id <= 0) { printf("[ERRO] O ID deve ser maior que zero!\n"); return; }
    if (buscarIndiceAcessorio(id) != -1) {
        printf("[ERRO] Ja existe um acessorio com o ID %d!\n", id);
        return;
    }
    struct Acessorio *a = &estoqueAcessorios[totalAcessorios];
    a->idAcessorio = id;
    lerTexto("Descricao (ex: Controle SNES Original): ", a->descricao, sizeof(a->descricao));
    lerTexto("Tipo (Controle, Cabo, Fonte, Adaptador...): ", a->tipo, sizeof(a->tipo));
    a->custoReparo = lerFloat("Custo de reparo/reposicao por unidade (R$): ");
    a->quantidadeEstoque = lerInteiro("Quantidade em estoque: ");
    if (a->custoReparo < 0 || a->quantidadeEstoque < 0) {
        printf("[ERRO] Valores negativos nao sao permitidos!\n");
        return;
    }
    a->emManutencao = 0;
    totalAcessorios++;
    salvarAcessoriosCSV();
    printf("[OK] Acessorio salvo com sucesso em 'acessorios.csv'!\n");
}

// 5. LISTAGEM FORMATADA (estoque + itens em manutencao)
void listarAcessorios() {
    printf("\n--- ESTOQUE DE ACESSORIOS (%d itens) ---\n", totalAcessorios);
    for (int i = 0; i < totalAcessorios; i++) {
        printf("ID: %-3d | %-30s | %-10s | Reparo: R$ %6.2f | Estoque: %2d | Manutencao: %d\n",
               estoqueAcessorios[i].idAcessorio, estoqueAcessorios[i].descricao,
               estoqueAcessorios[i].tipo, estoqueAcessorios[i].custoReparo,
               estoqueAcessorios[i].quantidadeEstoque, estoqueAcessorios[i].emManutencao);
    }
}

// 6. BUSCA TEXTUAL por descricao ou tipo (strstr dentro de contemTexto)
void buscarAcessorio() {
    char termo[40];
    lerTexto("\nDigite parte da descricao ou do tipo (ex: controle, cabo): ", termo, sizeof(termo));
    int achou = 0;
    for (int i = 0; i < totalAcessorios; i++) {
        if (contemTexto(estoqueAcessorios[i].descricao, termo) ||
            contemTexto(estoqueAcessorios[i].tipo, termo)) {
            printf(" -> [%d] %s (%s) | Estoque: %d | Manutencao: %d\n",
                   estoqueAcessorios[i].idAcessorio, estoqueAcessorios[i].descricao,
                   estoqueAcessorios[i].tipo, estoqueAcessorios[i].quantidadeEstoque,
                   estoqueAcessorios[i].emManutencao);
            achou++;
        }
    }
    if (!achou) printf("Nenhum acessorio encontrado para '%s'.\n", termo);
}

// 7. EDICAO na memoria + reescrita total do CSV
void editarAcessorio() {
    int id = lerInteiro("\nID do acessorio que deseja EDITAR: ");
    int pos = buscarIndiceAcessorio(id);
    if (pos == -1) { printf("[ERRO] Acessorio nao encontrado!\n"); return; }
    struct Acessorio *a = &estoqueAcessorios[pos];
    printf("Editando '%s' (Estoque %d | Reparo R$ %.2f)\n", a->descricao, a->quantidadeEstoque, a->custoReparo);
    printf("1. Quantidade em estoque | 2. Custo de reparo | 3. Descricao | 0. Cancelar\n");
    int campo = lerInteiro("O que deseja alterar? ");
    switch (campo) {
        case 1: {
            int q = lerInteiro("Nova quantidade em estoque: ");
            if (q < 0) { printf("[ERRO] Quantidade invalida!\n"); return; }
            a->quantidadeEstoque = q;
            break;
        }
        case 2: {
            float v = lerFloat("Novo custo de reparo (R$): ");
            if (v < 0) { printf("[ERRO] Valor invalido!\n"); return; }
            a->custoReparo = v;
            break;
        }
        case 3: lerTexto("Nova descricao: ", a->descricao, sizeof(a->descricao)); break;
        case 0: printf("Edicao cancelada.\n"); return;
        default: printf("[ERRO] Opcao invalida!\n"); return;
    }
    salvarAcessoriosCSV();
    printf("[OK] Acessorio atualizado na memoria e no arquivo CSV!\n");
}

// 8. BAIXA / REMOCAO fisica no vetor + reescrita do CSV
void removerAcessorio() {
    int id = lerInteiro("\nID do acessorio que deseja dar BAIXA: ");
    int pos = buscarIndiceAcessorio(id);
    if (pos == -1) { printf("[ERRO] Acessorio nao encontrado!\n"); return; }
    if (!confirmar("Confirma a baixa definitiva do item? (s/n): ")) { printf("Baixa cancelada.\n"); return; }
    for (int j = pos; j < totalAcessorios - 1; j++) {
        estoqueAcessorios[j] = estoqueAcessorios[j + 1];
    }
    totalAcessorios--;
    salvarAcessoriosCSV();
    printf("[OK] Acessorio baixado do estoque e do CSV!\n");
}

// 9. REGRA DE NEGOCIO: move unidades do estoque para a manutencao.
// Retorna 1 se deu certo, 0 se o ID nao existe ou nao ha unidades suficientes.
// (Tambem chamada pelo modulo de Locacoes quando um acessorio volta danificado.)
int acessorioEnviarManutencao(int idAcessorio, int quantidade) {
    int pos = buscarIndiceAcessorio(idAcessorio);
    if (pos == -1 || quantidade <= 0 || quantidade > estoqueAcessorios[pos].quantidadeEstoque) return 0;
    estoqueAcessorios[pos].quantidadeEstoque -= quantidade;
    estoqueAcessorios[pos].emManutencao += quantidade;
    salvarAcessoriosCSV();
    return 1;
}

// Devolve o custo de reparo unitario do acessorio (0 se nao existir)
float acessorioCustoReparo(int idAcessorio) {
    int pos = buscarIndiceAcessorio(idAcessorio);
    return (pos == -1) ? 0.0f : estoqueAcessorios[pos].custoReparo;
}

// Soma (custoReparo x unidades em manutencao): usado no relatorio financeiro
float acessoriosCustoManutencaoPendente() {
    float soma = 0;
    for (int i = 0; i < totalAcessorios; i++) {
        soma += estoqueAcessorios[i].custoReparo * estoqueAcessorios[i].emManutencao;
    }
    return soma;
}

void enviarParaManutencaoMenu() {
    int id = lerInteiro("\nID do acessorio com defeito: ");
    if (buscarIndiceAcessorio(id) == -1) { printf("[ERRO] Acessorio nao encontrado!\n"); return; }
    int qtd = lerInteiro("Quantas unidades enviar para manutencao? ");
    if (acessorioEnviarManutencao(id, qtd)) printf("[OK] Unidades movidas do estoque para a manutencao!\n");
    else printf("[ERRO] Quantidade invalida ou maior que o estoque disponivel!\n");
}

void concluirManutencao() {
    int id = lerInteiro("\nID do acessorio consertado: ");
    int pos = buscarIndiceAcessorio(id);
    if (pos == -1) { printf("[ERRO] Acessorio nao encontrado!\n"); return; }
    int qtd = lerInteiro("Quantas unidades voltaram do conserto? ");
    if (qtd <= 0 || qtd > estoqueAcessorios[pos].emManutencao) {
        printf("[ERRO] Quantidade invalida (em manutencao: %d)!\n", estoqueAcessorios[pos].emManutencao);
        return;
    }
    estoqueAcessorios[pos].emManutencao -= qtd;
    estoqueAcessorios[pos].quantidadeEstoque += qtd;
    salvarAcessoriosCSV();
    printf("[OK] Unidades devolvidas ao estoque!\n");
}

// 10. SUBMENU
void moduloAcessorios() {
    int op;
    do {
        limparTela();
        printf("\n--- [MODULO 3: ACESSORIOS E MANUTENCAO (Luiz)] ---\n");
        printf("1. Cadastrar Acessorio (Controle, Cabo, Adaptador)\n");
        printf("2. Consultar Estoque / Itens em Manutencao\n");
        printf("3. Buscar Acessorio por Descricao ou Tipo\n");
        printf("4. Atualizar Quantidade ou Custo de Reparo\n");
        printf("5. Dar Baixa / Remover Item Danificado\n");
        printf("6. Enviar Unidades para Manutencao\n");
        printf("7. Concluir Manutencao (volta ao estoque)\n");
        printf("0. Voltar ao Menu Principal\n");
        op = lerInteiro("Escolha uma acao: ");
        switch (op) {
            case 1: cadastrarAcessorio(); pausar(); break;
            case 2: listarAcessorios(); pausar(); break;
            case 3: buscarAcessorio(); pausar(); break;
            case 4: editarAcessorio(); pausar(); break;
            case 5: removerAcessorio(); pausar(); break;
            case 6: enviarParaManutencaoMenu(); pausar(); break;
            case 7: concluirManutencao(); pausar(); break;
            case 0: printf("\nRetornando ao menu principal...\n"); break;
            default: printf("\n[ERRO] Opcao invalida no Modulo de Acessorios!\n"); pausar();
        }
    } while (op != 0);
}

#endif
