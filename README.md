# 🎮 Locadora Retrô de Cartuchos (SNES & Mega Drive)

Sistema de locação de cartuchos de video-game **SNES** e **Mega Drive**, desenvolvido em **C** (modo console) como projeto da disciplina de **Algoritmos e Pensamento Computacional**.

> Este grupo tem como objetivo desenvolver um sistema de locação de cartuchos de video-game SNES e Mega Drive.

---

## 👥 Equipe

| Integrante | Módulo | Responsabilidade |
|------------|--------|------------------|
| **Matheus** | Módulo 1: Clientes (+ utilitários) | Cadastro e gestão dos clientes e funções de apoio (`utils`) |
| **Samarah** | Módulo 2: Catálogo de Cartuchos | Acervo de jogos SNES e Mega Drive |
| **Luiz** | Módulo 3: Acessórios e Manutenção | Controles, cabos, adaptadores e itens em reparo |
| **Rodrigo** | Módulo 4: Locações e Relatórios | Locação/devolução e relatórios analíticos |

---

## 📦 Funcionalidades

| Módulo | Operações |
|--------|-----------|
| Clientes | Cadastrar, listar, buscar por nome, editar (dados, saldo devedor, ativar/suspender) e remover |
| Cartuchos | Cadastrar, listar acervo, buscar por título/console, alterar diária, cópias ou status e excluir |
| Acessórios | Cadastrar, consultar estoque, buscar, atualizar quantidade/custo, dar baixa, **enviar para manutenção** e **concluir manutenção** |
| Locações | Registrar, listar histórico, buscar por nome do cliente, editar dias, registrar devolução, cancelar e remover registro encerrado |

### Relatórios (Módulo 4)
- Ranking de cartuchos mais alugados (campeão de locações)
- Ranking de clientes com mais locações (cliente VIP)
- Locações de um cliente específico (com total movimentado e saldo devedor)
- Matriz **Console × Status** (quantidade e valores) + resumo financeiro (receita realizada, receita em aberto, custo de manutenção pendente, resultado estimado e dívidas dos clientes)

---

## 🔗 Integração entre os módulos

O Módulo 4 cruza os dados dos demais:

- **Registrar locação:** valida o cliente (existe, está ativo e a dívida está abaixo do limite) e o cartucho (existe, está ativo e tem cópia disponível). Depois dá baixa no estoque do cartucho e lança o valor no saldo devedor do cliente.
- **Devolução:** a cópia volta ao estoque. Se um acessório voltou danificado, ele é enviado para manutenção (Módulo 3) e o custo de reparo é cobrado no saldo do cliente.
- **Cancelamento:** estorna o estoque e o saldo do cliente.
- **Exclusões protegidas:** um cliente ou cartucho com locação em aberto não pode ser removido.

### Regras de negócio
- Aluguel de **1 a 30 dias**.
- Limite de dívida do cliente: **R$ 100,00** (acima disso não pode alugar).
- Status da locação: `0` em aberto, `1` devolvida, `2` cancelada.

---

## 🗂️ Estrutura de dados e persistência

Os dados ficam em **vetores globais de structs** (tamanho 50) e são **gravados em arquivos CSV** (separador `;`), carregados ao abrir o programa e regravados a cada alteração.

| Struct | Vetor | Arquivo | Campos principais |
|--------|-------|---------|-------------------|
| `Cliente` | `listaClientes[50]` | `clientes.csv` | id, nome, telefone, saldo devedor, ativo |
| `Cartucho` | `catalogoCartuchos[50]` | `cartuchos.csv` | id, título, console, valor da diária, cópias disponíveis, ativo |
| `Acessorio` | `estoqueAcessorios[50]` | `acessorios.csv` | id, descrição, tipo, custo de reparo, estoque, em manutenção |
| `Locacao` | `historicoLocacoes[50]` | `locacoes.csv` | id, id do cliente, id do cartucho, dias, valor total, status |

Os arquivos `.csv` são criados na pasta em que o programa é executado.

---

## 🧩 Estrutura dos arquivos

Cada integrante mantém o próprio módulo em um arquivo, no formato de cabeçalho (`.h`), com um `main.c` que reúne tudo:

| Arquivo | Responsável | Conteúdo |
|---------|-------------|----------|
| `utils.h` | Matheus | Leitura segura (`lerInteiro`, `lerTexto`, `lerFloat`), `confirmar`, `pausar`, `limparTela`, `contemTexto` |
| `clientes.h` | Matheus | Módulo 1 |
| `cartuchos.h` | Samarah | Módulo 2 |
| `acessorios.h` | Luiz | Módulo 3 |
| `locacoes.h` (`parte-rodrigo.c`) | Rodrigo | Módulo 4 |
| `main.c` | Grupo | Menu principal que chama os quatro módulos |

> Os arquivos de cada parte ainda estão com nomes provisórios no repositório e o `main.c` será atualizado para incluir os cabeçalhos e carregar os CSVs na inicialização.

---

## 🚀 Como compilar e executar

Requisitos: compilador C (**GCC** ou **Dev-C++**).

```bash
gcc main.c -o locadora
./locadora
```

No Windows (PowerShell/CMD):

```bash
gcc main.c -o locadora.exe
locadora.exe
```

---

## 🧭 Navegação

O menu principal roda em loop contínuo e direciona para os submenus de cada integrante:

```
1. Módulo de Clientes
2. Módulo de Cartuchos
3. Módulo de Acessórios e Manutenção
4. Módulo de Locações e Relatórios
0. Encerrar o Sistema
```

Em qualquer submenu, digite **0** para voltar ao menu principal.

---

## 🔀 Fluxo de trabalho no Git

- Cada integrante edita **somente o próprio arquivo**, identificado pelo cabeçalho `// Autor: Nome`.
- Sempre fazer `git pull` antes de começar a trabalhar.
- Adicionar ao commit apenas o próprio arquivo (`git add <arquivo>`), evitando `git add .`.
- Alterações podem ser enviadas por branch + Pull Request ou direto na `main`, conforme combinado pelo grupo.

---

## 🛣️ Status do projeto

**Checkpoint 1 (estrutura base):**
- [x] Repositório criado e compartilhado
- [x] Structs de cada integrante
- [x] Menu principal em loop (`do-while` + `switch-case`)
- [x] Submenus com Cadastrar, Listar/Buscar, Editar e Remover
- [x] Funções `void` separadas com identificação de autoria

**Implementado:**
- [x] Lógica real de cada operação nos quatro módulos
- [x] Relatórios analíticos (rankings, matriz Console × Status e resumo financeiro)
- [x] Salvar e carregar dados em arquivos CSV (`FILE *`)

**Próximas etapas:**
- [ ] Integrar os quatro módulos no `main.c` (incluir os cabeçalhos e chamar os `carregar...CSV()` ao iniciar)
- [ ] Renomear os arquivos de cada parte para `.h`
- [ ] Remover o arquivo de teste `menuarq_main.c`
- [ ] Testes finais com dados reais

---

## 📚 Disciplina

**Algoritmos e Pensamento Computacional**: Projeto do 2º Bimestre, Checkpoint 1 (Gateway 1).
