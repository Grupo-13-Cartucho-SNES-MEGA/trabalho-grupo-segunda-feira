// Arquivo: locacoes.h | Autor: Rodrigo Lopes Miguel (RGM 04912504-4)
// MODULO 4: LOCACOES E RELATORIOS ANALITICOS (persistencia em locacoes.csv)
#ifndef LOCACOES_H
#define LOCACOES_H

#include "utils.h"
#include "clientes.h"
#include "cartuchos.h"
#include "acessorios.h"

#define MAX_LOCACOES 50
#define MAX_DIAS_LOCACAO 30
#define STATUS_ABERTA 0
#define STATUS_DEVOLVIDA 1
#define STATUS_CANCELADA 2

struct Locacao {
    int idLocacao;
    int idClienteLocador;
    int idCartuchoAlugado;
    int diasAluguel;
    float valorTotal;
    int devolvido;          
};
struct Locacao historicoLocacoes[MAX_LOCACOES];
int totalLocacoes = 0;
struct ItemRanking {
    int indice;
    int quantidade;
};

int matrizUso[MAX_CARTUCHOS][MAX_CLIENTES];
void salvarLocacoesCSV() {
    FILE *arq = fopen("locacoes.csv", "w");
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar locacoes.csv!\n");
        return;
    }
    for (int i = 0; i < totalLocacoes; i++) {
        fprintf(arq, "%d;%d;%d;%d;%.2f;%d\n",
                historicoLocacoes[i].idLocacao,
                historicoLocacoes[i].idClienteLocador,
                historicoLocacoes[i].idCartuchoAlugado,
                historicoLocacoes[i].diasAluguel,
                historicoLocacoes[i].valorTotal,
                historicoLocacoes[i].devolvido);
    }
    fclose(arq);
}

// 2. PERSISTENCIA: le locacoes.csv ao abrir o programa (so numeros, entao nao precisa de %[^;])
void carregarLocacoesCSV() {
    FILE *arq = fopen("locacoes.csv", "r");
    if (arq == NULL) return;
    totalLocacoes = 0;
    while (totalLocacoes < MAX_LOCACOES &&
           fscanf(arq, "%d;%d;%d;%d;%f;%d\n",
                  &historicoLocacoes[totalLocacoes].idLocacao,
                  &historicoLocacoes[totalLocacoes].idClienteLocador,
                  &historicoLocacoes[totalLocacoes].idCartuchoAlugado,
                  &historicoLocacoes[totalLocacoes].diasAluguel,
                  &historicoLocacoes[totalLocacoes].valorTotal,
                  &historicoLocacoes[totalLocacoes].devolvido) == 6) {
        totalLocacoes++;
    }
    fclose(arq);
}

int buscarIndiceLocacao(int idProcurado) {
    for (int i = 0; i < totalLocacoes; i++) {
        if (historicoLocacoes[i].idLocacao == idProcurado) return i;
    }
    return -1;
}

int proximoIdLocacao() {
    int maior = 0;
    for (int i = 0; i < totalLocacoes; i++) {
        if (historicoLocacoes[i].idLocacao > maior) maior = historicoLocacoes[i].idLocacao;
    }
    return maior + 1;
}

int clientePossuiLocacaoAberta(int idCliente) {
    for (int i = 0; i < totalLocacoes; i++) {
        if (historicoLocacoes[i].idClienteLocador == idCliente &&
            historicoLocacoes[i].devolvido == STATUS_ABERTA) return 1;
    }
    return 0;
}

int cartuchoPossuiLocacaoAberta(int idCartucho) {
    for (int i = 0; i < totalLocacoes; i++) {
        if (historicoLocacoes[i].idCartuchoAlugado == idCartucho &&
            historicoLocacoes[i].devolvido == STATUS_ABERTA) return 1;
    }
    return 0;
}

const char *textoStatus(int status) {
    if (status == STATUS_ABERTA) return "Em aberto";
    if (status == STATUS_DEVOLVIDA) return "Devolvida";
    return "Cancelada";
}

void imprimirLocacao(int i) {
    int pc = buscarIndiceCliente(historicoLocacoes[i].idClienteLocador);
    int pj = buscarIndiceCartucho(historicoLocacoes[i].idCartuchoAlugado);
    printf("Loc %-3d | %-22s | %-30s | %2d dia(s) | R$ %6.2f | %s\n",
           historicoLocacoes[i].idLocacao,
           pc == -1 ? "(cliente removido)" : listaClientes[pc].nome,
           pj == -1 ? "(cartucho excluido)" : catalogoCartuchos[pj].titulo,
           historicoLocacoes[i].diasAluguel, historicoLocacoes[i].valorTotal,
           textoStatus(historicoLocacoes[i].devolvido));
}

// 3. REGISTRAR LOCACAO: valida cliente e cartucho, calcula o valor, baixa estoque e lanca no saldo do cliente
void registrarLocacao() {
    if (totalLocacoes >= MAX_LOCACOES) { printf("[ERRO] Historico lotado (%d)!\n", MAX_LOCACOES); return; }

    int idCli = lerInteiro("\nID do cliente: ");
    int posCli = buscarIndiceCliente(idCli);
    if (posCli == -1) { printf("[ERRO] Cliente %d nao existe no Modulo de Clientes!\n", idCli); return; }
    if (!listaClientes[posCli].ativo) { printf("[ERRO] Cliente suspenso! Nao pode alugar.\n"); return; }
    if (listaClientes[posCli].saldoDevedor >= LIMITE_DEBITO) {
        printf("[ERRO] Cliente com divida de R$ %.2f (limite R$ %.2f). Quite o saldo antes!\n",
               listaClientes[posCli].saldoDevedor, LIMITE_DEBITO);
        return;
    }

    int idCart = lerInteiro("ID do cartucho: ");
    int posCart = buscarIndiceCartucho(idCart);
    if (posCart == -1) { printf("[ERRO] Cartucho %d nao existe no Catalogo!\n", idCart); return; }
    if (!catalogoCartuchos[posCart].ativo) { printf("[ERRO] Cartucho fora de circulacao!\n"); return; }
    if (catalogoCartuchos[posCart].copiasDisponiveis <= 0) {
        printf("[ERRO] Sem copias disponiveis de '%s' no momento!\n", catalogoCartuchos[posCart].titulo);
        return;
    }

    int dias = lerInteiro("Dias de aluguel: ");
    if (dias < 1 || dias > MAX_DIAS_LOCACAO) {
        printf("[ERRO] O aluguel deve ser de 1 a %d dias!\n", MAX_DIAS_LOCACAO);
        return;
    }

    float valor = dias * catalogoCartuchos[posCart].valorDiaria;
    printf("\n%s para %s: %d dia(s) x R$ %.2f = R$ %.2f\n", catalogoCartuchos[posCart].titulo,
           listaClientes[posCli].nome, dias, catalogoCartuchos[posCart].valorDiaria, valor);
    if (!confirmar("Confirmar locacao? (s/n): ")) { printf("Locacao cancelada.\n"); return; }

    struct Locacao *l = &historicoLocacoes[totalLocacoes];
    l->idLocacao = proximoIdLocacao();
    l->idClienteLocador = idCli;
    l->idCartuchoAlugado = idCart;
    l->diasAluguel = dias;
    l->valorTotal = valor;
    l->devolvido = STATUS_ABERTA;
    totalLocacoes++;

    catalogoCartuchos[posCart].copiasDisponiveis--;      // baixa automatica no estoque
    listaClientes[posCli].saldoDevedor += valor;         // valor lancado na conta do cliente
    salvarLocacoesCSV();
    salvarCartuchosCSV();
    salvarClientesCSV();
    printf("[OK] Locacao %d registrada! Copias restantes: %d | Saldo do cliente: R$ %.2f\n",
           l->idLocacao, catalogoCartuchos[posCart].copiasDisponiveis, listaClientes[posCli].saldoDevedor);
}

// 4. LISTAGEM
void listarLocacoes() {
    printf("\n--- HISTORICO DE LOCACOES (%d registros) ---\n", totalLocacoes);
    for (int i = 0; i < totalLocacoes; i++) imprimirLocacao(i);
}

// 5. BUSCA TEXTUAL por nome do cliente (strstr dentro de contemTexto)
void buscarLocacoesPorNome() {
    char termo[50];
    lerTexto("\nDigite parte do nome do cliente: ", termo, sizeof(termo));
    int achou = 0;
    for (int i = 0; i < totalLocacoes; i++) {
        int pc = buscarIndiceCliente(historicoLocacoes[i].idClienteLocador);
        if (pc != -1 && contemTexto(listaClientes[pc].nome, termo)) {
            imprimirLocacao(i);
            achou++;
        }
    }
    if (!achou) printf("Nenhuma locacao encontrada para '%s'.\n", termo);
}

// 6. EDICAO: altera os dias de uma locacao em aberto (recalcula valor e ajusta o saldo do cliente)
void editarLocacao() {
    int id = lerInteiro("\nID da locacao que deseja EDITAR: ");
    int pos = buscarIndiceLocacao(id);
    if (pos == -1) { printf("[ERRO] Locacao nao encontrada!\n"); return; }
    struct Locacao *l = &historicoLocacoes[pos];
    if (l->devolvido != STATUS_ABERTA) { printf("[ERRO] So e possivel editar locacoes em aberto!\n"); return; }
    int posCart = buscarIndiceCartucho(l->idCartuchoAlugado);
    int posCli = buscarIndiceCliente(l->idClienteLocador);
    if (posCart == -1) { printf("[ERRO] Cartucho da locacao nao existe mais!\n"); return; }

    int novosDias = lerInteiro("Novo numero de dias: ");
    if (novosDias < 1 || novosDias > MAX_DIAS_LOCACAO) {
        printf("[ERRO] O aluguel deve ser de 1 a %d dias!\n", MAX_DIAS_LOCACAO);
        return;
    }
    float novoValor = novosDias * catalogoCartuchos[posCart].valorDiaria;
    if (posCli != -1) {
        listaClientes[posCli].saldoDevedor += (novoValor - l->valorTotal);
        if (listaClientes[posCli].saldoDevedor < 0) listaClientes[posCli].saldoDevedor = 0;
    }
    l->diasAluguel = novosDias;
    l->valorTotal = novoValor;
    salvarLocacoesCSV();
    salvarClientesCSV();
    printf("[OK] Locacao atualizada: %d dia(s), R$ %.2f (memoria e CSV)!\n", novosDias, novoValor);
}

// 7. DEVOLUCAO: devolve a copia ao estoque e permite lancar acessorio danificado (cruza modulos 1, 2 e 3)
void registrarDevolucao() {
    int id = lerInteiro("\nID da locacao a DEVOLVER: ");
    int pos = buscarIndiceLocacao(id);
    if (pos == -1) { printf("[ERRO] Locacao nao encontrada!\n"); return; }
    if (historicoLocacoes[pos].devolvido != STATUS_ABERTA) {
        printf("[ERRO] Esta locacao ja foi %s!\n",
               historicoLocacoes[pos].devolvido == STATUS_DEVOLVIDA ? "devolvida" : "cancelada");
        return;
    }
    int posCart = buscarIndiceCartucho(historicoLocacoes[pos].idCartuchoAlugado);
    if (posCart != -1) catalogoCartuchos[posCart].copiasDisponiveis++;   // copia volta para a prateleira
    historicoLocacoes[pos].devolvido = STATUS_DEVOLVIDA;
    salvarLocacoesCSV();
    salvarCartuchosCSV();
    printf("[OK] Devolucao registrada! A copia voltou ao estoque.\n");

    if (confirmar("Algum acessorio voltou danificado? (s/n): ")) {
        int idAc = lerInteiro("ID do acessorio danificado: ");
        if (acessorioEnviarManutencao(idAc, 1)) {
            float custo = acessorioCustoReparo(idAc);
            int posCli = buscarIndiceCliente(historicoLocacoes[pos].idClienteLocador);
            if (posCli != -1) {
                listaClientes[posCli].saldoDevedor += custo;
                salvarClientesCSV();
            }
            printf("[OK] Acessorio enviado para manutencao. Cobrado R$ %.2f no saldo do cliente.\n", custo);
        } else {
            printf("[AVISO] Acessorio nao encontrado ou sem estoque: nenhuma cobranca feita.\n");
        }
    }
}

// 8. CANCELAMENTO: desfaz a locacao em aberto (estorna estoque e saldo)
void cancelarLocacao() {
    int id = lerInteiro("\nID da locacao a CANCELAR: ");
    int pos = buscarIndiceLocacao(id);
    if (pos == -1) { printf("[ERRO] Locacao nao encontrada!\n"); return; }
    if (historicoLocacoes[pos].devolvido != STATUS_ABERTA) {
        printf("[ERRO] So e possivel cancelar locacoes em aberto!\n");
        return;
    }
    if (!confirmar("Confirma o cancelamento? (s/n): ")) { printf("Cancelamento abortado.\n"); return; }
    int posCart = buscarIndiceCartucho(historicoLocacoes[pos].idCartuchoAlugado);
    int posCli = buscarIndiceCliente(historicoLocacoes[pos].idClienteLocador);
    if (posCart != -1) catalogoCartuchos[posCart].copiasDisponiveis++;
    if (posCli != -1) {
        listaClientes[posCli].saldoDevedor -= historicoLocacoes[pos].valorTotal;
        if (listaClientes[posCli].saldoDevedor < 0) listaClientes[posCli].saldoDevedor = 0;
    }
    historicoLocacoes[pos].devolvido = STATUS_CANCELADA;
    salvarLocacoesCSV();
    salvarCartuchosCSV();
    salvarClientesCSV();
    printf("[OK] Locacao cancelada: estoque e saldo do cliente estornados!\n");
}

// 9. REMOCAO fisica de registro ja encerrado + reescrita do CSV
void removerLocacao() {
    int id = lerInteiro("\nID da locacao a REMOVER do historico: ");
    int pos = buscarIndiceLocacao(id);
    if (pos == -1) { printf("[ERRO] Locacao nao encontrada!\n"); return; }
    if (historicoLocacoes[pos].devolvido == STATUS_ABERTA) {
        printf("[ERRO] Locacao em aberto! Registre a devolucao ou cancele antes de remover.\n");
        return;
    }
    if (!confirmar("Remover apagara o registro dos relatorios. Confirma? (s/n): ")) {
        printf("Remocao cancelada.\n");
        return;
    }
    for (int j = pos; j < totalLocacoes - 1; j++) {
        historicoLocacoes[j] = historicoLocacoes[j + 1];
    }
    totalLocacoes--;
    salvarLocacoesCSV();
    printf("[OK] Registro removido do historico e do CSV!\n");
}

// ---------------------------------------------------------------------------
// RELATORIOS ANALITICOS
// ---------------------------------------------------------------------------

// Preenche a MATRIZ 2D cartucho x cliente com as locacoes validas (ignora canceladas)
void construirMatrizUso() {
    for (int i = 0; i < MAX_CARTUCHOS; i++)
        for (int j = 0; j < MAX_CLIENTES; j++)
            matrizUso[i][j] = 0;
    for (int k = 0; k < totalLocacoes; k++) {
        if (historicoLocacoes[k].devolvido == STATUS_CANCELADA) continue;
        int pj = buscarIndiceCartucho(historicoLocacoes[k].idCartuchoAlugado);
        int pc = buscarIndiceCliente(historicoLocacoes[k].idClienteLocador);
        if (pj != -1 && pc != -1) matrizUso[pj][pc]++;
    }
}

// BUBBLE SORT em vetor de structs: ordem decrescente por quantidade
void ordenarRanking(struct ItemRanking v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j].quantidade < v[j + 1].quantidade) {
                struct ItemRanking aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

void relatorioCartuchoMaisAlugado() {
    construirMatrizUso();
    struct ItemRanking rank[MAX_CARTUCHOS];
    for (int i = 0; i < totalCartuchos; i++) {
        rank[i].indice = i;
        rank[i].quantidade = 0;
        for (int j = 0; j < totalClientes; j++) rank[i].quantidade += matrizUso[i][j]; // soma da linha
    }
    ordenarRanking(rank, totalCartuchos);
    printf("\n--- [RELATORIO] RANKING DE CARTUCHOS MAIS ALUGADOS ---\n");
    if (totalCartuchos == 0 || rank[0].quantidade == 0) { printf("Ainda nao ha locacoes registradas.\n"); return; }
    for (int p = 0; p < totalCartuchos && p < 5 && rank[p].quantidade > 0; p++) {
        printf("%do | %-34s | %-10s | %d locacao(oes)\n", p + 1,
               catalogoCartuchos[rank[p].indice].titulo,
               catalogoCartuchos[rank[p].indice].console, rank[p].quantidade);
    }
    printf("\n>>> Campeao de locacoes: %s\n", catalogoCartuchos[rank[0].indice].titulo);
}

void relatorioClienteMaisLocacoes() {
    construirMatrizUso();
    struct ItemRanking rank[MAX_CLIENTES];
    for (int j = 0; j < totalClientes; j++) {
        rank[j].indice = j;
        rank[j].quantidade = 0;
        for (int i = 0; i < totalCartuchos; i++) rank[j].quantidade += matrizUso[i][j]; // soma da coluna
    }
    ordenarRanking(rank, totalClientes);
    printf("\n--- [RELATORIO] RANKING DE CLIENTES (MAIS LOCACOES) ---\n");
    if (totalClientes == 0 || rank[0].quantidade == 0) { printf("Ainda nao ha locacoes registradas.\n"); return; }
    for (int p = 0; p < totalClientes && p < 5 && rank[p].quantidade > 0; p++) {
        printf("%do | %-24s | %d locacao(oes)\n", p + 1,
               listaClientes[rank[p].indice].nome, rank[p].quantidade);
    }
    printf("\n>>> Cliente VIP: %s\n", listaClientes[rank[0].indice].nome);
}

void relatorioLocacoesPorCliente() {
    int id = lerInteiro("\nID do cliente: ");
    int pc = buscarIndiceCliente(id);
    if (pc == -1) { printf("[ERRO] Cliente nao encontrado!\n"); return; }
    printf("\n--- [RELATORIO] LOCACOES DE %s ---\n", listaClientes[pc].nome);
    int qtd = 0;
    float total = 0;
    for (int i = 0; i < totalLocacoes; i++) {
        if (historicoLocacoes[i].idClienteLocador == id) {
            imprimirLocacao(i);
            if (historicoLocacoes[i].devolvido != STATUS_CANCELADA) {
                qtd++;
                total += historicoLocacoes[i].valorTotal;
            }
        }
    }
    if (qtd == 0) printf("Nenhuma locacao valida para este cliente.\n");
    else printf("\nTotal: %d locacao(oes) validas | Valor movimentado: R$ %.2f | Saldo devedor atual: R$ %.2f\n",
                qtd, total, listaClientes[pc].saldoDevedor);
}

// MATRIZ 2D: linhas = console (SNES, Mega Drive), colunas = status; mais resumo financeiro
void relatorioMatrizEFinanceiro() {
    int contagem[2][3] = {{0}};
    float receita[2][3] = {{0}};
    for (int k = 0; k < totalLocacoes; k++) {
        int pj = buscarIndiceCartucho(historicoLocacoes[k].idCartuchoAlugado);
        if (pj == -1) continue;
        int linha = (strcmp(catalogoCartuchos[pj].console, "SNES") == 0) ? 0 : 1;
        int coluna = historicoLocacoes[k].devolvido;
        if (coluna < 0 || coluna > 2) continue;
        contagem[linha][coluna]++;
        receita[linha][coluna] += historicoLocacoes[k].valorTotal;
    }
    const char *nomes[2] = {"SNES", "Mega Drive"};
    printf("\n--- [RELATORIO] MATRIZ CONSOLE x STATUS (quantidade de locacoes) ---\n");
    printf("%-12s | %-9s | %-10s | %-10s\n", "Console", "Em aberto", "Devolvidas", "Canceladas");
    for (int i = 0; i < 2; i++) {
        printf("%-12s | %-9d | %-10d | %-10d\n", nomes[i], contagem[i][0], contagem[i][1], contagem[i][2]);
    }
    printf("\n--- MATRIZ CONSOLE x STATUS (valores em R$) ---\n");
    for (int i = 0; i < 2; i++) {
        printf("%-12s | %9.2f | %10.2f | %10.2f\n", nomes[i], receita[i][0], receita[i][1], receita[i][2]);
    }
    float realizada = receita[0][1] + receita[1][1];
    float emAberto = receita[0][0] + receita[1][0];
    float manutencao = acessoriosCustoManutencaoPendente();
    float dividas = 0;
    for (int c = 0; c < totalClientes; c++) dividas += listaClientes[c].saldoDevedor;
    printf("\n=== RESUMO FINANCEIRO ===\n");
    printf("Receita de locacoes devolvidas : R$ %.2f\n", realizada);
    printf("Receita em locacoes em aberto  : R$ %.2f\n", emAberto);
    printf("Custo de manutencao pendente   : R$ %.2f\n", manutencao);
    printf("Resultado estimado             : R$ %.2f\n", realizada + emAberto - manutencao);
    printf("Total de dividas dos clientes  : R$ %.2f\n", dividas);
}

// SUBMENU
void moduloLocacoesRelatorios() {
    int op;
    do {
        limparTela();
        printf("\n--- [MODULO 4: LOCACOES E RELATORIOS (Rodrigo)] ---\n");
        printf(" 1. Registrar Nova Locacao (Cruza Cliente + Cartucho)\n");
        printf(" 2. Listar Historico de Locacoes\n");
        printf(" 3. Buscar Locacoes por Nome do Cliente\n");
        printf(" 4. Editar Dias de uma Locacao em Aberto\n");
        printf(" 5. Registrar Devolucao\n");
        printf(" 6. Cancelar Locacao\n");
        printf(" 7. Remover Registro Encerrado do Historico\n");
        printf(" 8. [RELATORIO] Cartucho Mais Alugado (Ranking)\n");
        printf(" 9. [RELATORIO] Cliente com Mais Locacoes (Ranking)\n");
        printf("10. [RELATORIO] Locacoes de um Cliente Especifico\n");
        printf("11. [RELATORIO] Matriz Console x Status + Resumo Financeiro\n");
        printf(" 0. Voltar ao Menu Principal\n");
        op = lerInteiro("Escolha uma acao: ");
        switch (op) {
            case 1: registrarLocacao(); pausar(); break;
            case 2: listarLocacoes(); pausar(); break;
            case 3: buscarLocacoesPorNome(); pausar(); break;
            case 4: editarLocacao(); pausar(); break;
            case 5: registrarDevolucao(); pausar(); break;
            case 6: cancelarLocacao(); pausar(); break;
            case 7: removerLocacao(); pausar(); break;
            case 8: relatorioCartuchoMaisAlugado(); pausar(); break;
            case 9: relatorioClienteMaisLocacoes(); pausar(); break;
            case 10: relatorioLocacoesPorCliente(); pausar(); break;
            case 11: relatorioMatrizEFinanceiro(); pausar(); break;
            case 0: printf("\nRetornando ao menu principal...\n"); break;
            default: printf("\n[ERRO] Opcao invalida no Modulo de Locacoes!\n"); pausar();
        }
    } while (op != 0);
}

#endif
