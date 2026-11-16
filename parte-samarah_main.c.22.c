// Arquivo: cartuchos.h | Autor: Samarah Tamy de Paula Moura (RGM 04976909-0)
// MODULO 2: CATALOGO DE CARTUCHOS SNES / MEGA DRIVE (persistencia em cartuchos.csv)
#ifndef CARTUCHOS_H
#define CARTUCHOS_H

#include "utils.h"

#define MAX_CARTUCHOS 50

struct Cartucho {
    int idCartucho;
    char titulo[50];
    char console[20];        
    float valorDiaria;
    int copiasDisponiveis;
    int ativo;               
};
struct Cartucho catalogoCartuchos[MAX_CARTUCHOS];
int totalCartuchos = 0;
int cartuchoPossuiLocacaoAberta(int idCartucho);

// 1. PERSISTENCIA: regrava o vetor inteiro em cartuchos.csv
void salvarCartuchosCSV() {
    FILE *arq = fopen("cartuchos.csv", "w");
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar cartuchos.csv!\n");
        return;
    }
    for (int i = 0; i < totalCartuchos; i++) {
        fprintf(arq, "%d;%s;%s;%.2f;%d;%d\n",
                catalogoCartuchos[i].idCartucho,
                catalogoCartuchos[i].titulo,
                catalogoCartuchos[i].console,
                catalogoCartuchos[i].valorDiaria,
                catalogoCartuchos[i].copiasDisponiveis,
                catalogoCartuchos[i].ativo);
    }
    fclose(arq);
}

// 2. PERSISTENCIA: le cartuchos.csv ao abrir o programa
void carregarCartuchosCSV() {
    FILE *arq = fopen("cartuchos.csv", "r");
    if (arq == NULL) return;
    totalCartuchos = 0;
    while (totalCartuchos < MAX_CARTUCHOS &&
           fscanf(arq, "%d;%49[^;];%19[^;];%f;%d;%d\n",
                  &catalogoCartuchos[totalCartuchos].idCartucho,
                  catalogoCartuchos[totalCartuchos].titulo,
                  catalogoCartuchos[totalCartuchos].console,
                  &catalogoCartuchos[totalCartuchos].valorDiaria,
                  &catalogoCartuchos[totalCartuchos].copiasDisponiveis,
                  &catalogoCartuchos[totalCartuchos].ativo) == 6) {
        totalCartuchos++;
    }
    fclose(arq);
}

// 3. Retorna a posicao do ID no vetor, ou -1
int buscarIndiceCartucho(int idProcurado) {
    for (int i = 0; i < totalCartuchos; i++) {
        if (catalogoCartuchos[i].idCartucho == idProcurado) return i;
    }
    return -1;
}

// 4. CADASTRO (trava de ID repetido, console padronizado, grava no CSV)
void cadastrarCartucho() {
    if (totalCartuchos >= MAX_CARTUCHOS) {
        printf("[ERRO] Catalogo lotado (%d)!\n", MAX_CARTUCHOS);
        return;
    }
    int id = lerInteiro("\nID do novo cartucho: ");
    if (id <= 0) { printf("[ERRO] O ID deve ser maior que zero!\n"); return; }
    if (buscarIndiceCartucho(id) != -1) {
        printf("[ERRO] Ja existe um cartucho com o ID %d!\n", id);
        return;
    }
    struct Cartucho *c = &catalogoCartuchos[totalCartuchos];
    c->idCartucho = id;
    lerTexto("Titulo do jogo: ", c->titulo, sizeof(c->titulo));
    int console = 0;
    while (console != 1 && console != 2) {
        console = lerInteiro("Console (1 = SNES | 2 = Mega Drive): ");
    }
    strcpy(c->console, console == 1 ? "SNES" : "Mega Drive");
    c->valorDiaria = lerFloat("Valor da diaria (R$): ");
    if (c->valorDiaria <= 0) { printf("[ERRO] A diaria deve ser maior que zero!\n"); return; }
    c->copiasDisponiveis = lerInteiro("Copias disponiveis: ");
    if (c->copiasDisponiveis < 0) { printf("[ERRO] Quantidade invalida!\n"); return; }
    c->ativo = 1;
    totalCartuchos++;
    salvarCartuchosCSV();
    printf("[OK] Cartucho salvo com sucesso em 'cartuchos.csv'!\n");
}

// 5. LISTAGEM FORMATADA
void listarCartuchos() {
    printf("\n--- ACERVO DE CARTUCHOS (%d titulos) ---\n", totalCartuchos);
    for (int i = 0; i < totalCartuchos; i++) {
        printf("ID: %-3d | %-34s | %-10s | Diaria: R$ %5.2f | Copias: %d | %s\n",
               catalogoCartuchos[i].idCartucho, catalogoCartuchos[i].titulo,
               catalogoCartuchos[i].console, catalogoCartuchos[i].valorDiaria,
               catalogoCartuchos[i].copiasDisponiveis,
               catalogoCartuchos[i].ativo ? "Ativo" : "Fora de circulacao");
    }
}

// 6. BUSCA TEXTUAL por titulo ou console (strstr dentro de contemTexto)
void buscarCartuchoPorTitulo() {
    char termo[50];
    lerTexto("\nDigite parte do titulo ou do console (ex: zelda, sonic, snes): ", termo, sizeof(termo));
    int achou = 0;
    for (int i = 0; i < totalCartuchos; i++) {
        if (contemTexto(catalogoCartuchos[i].titulo, termo) ||
            contemTexto(catalogoCartuchos[i].console, termo)) {
            printf(" -> [%d] %s (%s) R$ %.2f/dia | Copias: %d | %s\n",
                   catalogoCartuchos[i].idCartucho, catalogoCartuchos[i].titulo,
                   catalogoCartuchos[i].console, catalogoCartuchos[i].valorDiaria,
                   catalogoCartuchos[i].copiasDisponiveis,
                   catalogoCartuchos[i].ativo ? "Ativo" : "Fora de circulacao");
            achou++;
        }
    }
    if (!achou) printf("Nenhum cartucho encontrado para '%s'.\n", termo);
}

// 7. EDICAO na memoria + reescrita total do CSV
void editarCartucho() {
    int id = lerInteiro("\nID do cartucho que deseja EDITAR: ");
    int pos = buscarIndiceCartucho(id);
    if (pos == -1) { printf("[ERRO] Cartucho nao encontrado!\n"); return; }
    struct Cartucho *c = &catalogoCartuchos[pos];
    printf("Editando '%s' (Diaria R$ %.2f | Copias %d | %s)\n", c->titulo, c->valorDiaria,
           c->copiasDisponiveis, c->ativo ? "Ativo" : "Fora de circulacao");
    printf("1. Valor da diaria | 2. Copias disponiveis | 3. Titulo | 4. Ativar/Retirar de circulacao | 0. Cancelar\n");
    int campo = lerInteiro("O que deseja alterar? ");
    switch (campo) {
        case 1: {
            float v = lerFloat("Nova diaria (R$): ");
            if (v <= 0) { printf("[ERRO] A diaria deve ser maior que zero!\n"); return; }
            c->valorDiaria = v;
            break;
        }
        case 2: {
            int q = lerInteiro("Novo numero de copias disponiveis: ");
            if (q < 0) { printf("[ERRO] Quantidade invalida!\n"); return; }
            c->copiasDisponiveis = q;
            break;
        }
        case 3: lerTexto("Novo titulo: ", c->titulo, sizeof(c->titulo)); break;
        case 4: c->ativo = !c->ativo; break;
        case 0: printf("Edicao cancelada.\n"); return;
        default: printf("[ERRO] Opcao invalida!\n"); return;
    }
    salvarCartuchosCSV();
    printf("[OK] Cartucho atualizado na memoria e no arquivo CSV!\n");
}

// 8. REMOCAO fisica no vetor + reescrita do CSV
void removerCartucho() {
    int id = lerInteiro("\nID do cartucho que deseja EXCLUIR: ");
    int pos = buscarIndiceCartucho(id);
    if (pos == -1) { printf("[ERRO] Cartucho nao encontrado!\n"); return; }
    if (cartuchoPossuiLocacaoAberta(id)) {
        printf("[ERRO] Cartucho esta alugado no momento. Aguarde a devolucao!\n");
        return;
    }
    if (!confirmar("Confirma a exclusao? (s/n): ")) { printf("Exclusao cancelada.\n"); return; }
    for (int j = pos; j < totalCartuchos - 1; j++) {
        catalogoCartuchos[j] = catalogoCartuchos[j + 1];
    }
    totalCartuchos--;
    salvarCartuchosCSV();
    printf("[OK] Cartucho excluido do acervo e do CSV!\n");
}

// 9. SUBMENU
void moduloCartuchos() {
    int op;
    do {
        limparTela();
        printf("\n--- [MODULO 2: CATALOGO DE CARTUCHOS (Samarah)] ---\n");
        printf("1. Cadastrar Novo Cartucho\n");
        printf("2. Listar Acervo\n");
        printf("3. Buscar Jogo por Titulo ou Console\n");
        printf("4. Alterar Diaria, Copias ou Status\n");
        printf("5. Excluir Cartucho do Acervo\n");
        printf("0. Voltar ao Menu Principal\n");
        op = lerInteiro("Escolha uma acao: ");
        switch (op) {
            case 1: cadastrarCartucho(); pausar(); break;
            case 2: listarCartuchos(); pausar(); break;
            case 3: buscarCartuchoPorTitulo(); pausar(); break;
            case 4: editarCartucho(); pausar(); break;
            case 5: removerCartucho(); pausar(); break;
            case 0: printf("\nRetornando ao menu principal...\n"); break;
            default: printf("\n[ERRO] Opcao invalida no Modulo de Cartuchos!\n"); pausar();
        }
    } while (op != 0);
}

#endif
