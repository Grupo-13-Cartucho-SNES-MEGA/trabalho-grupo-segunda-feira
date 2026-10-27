# 🎮 Locadora Retrô de Cartuchos (SNES & Mega Drive)

Sistema de locação de cartuchos de video-game **SNES** e **Mega Drive**, desenvolvido em **C** (modo console) como projeto da disciplina de **Algoritmos e Pensamento Computacional**.

> Este grupo tem como objetivo desenvolver um sistema de locação de cartuchos de video-game SNES e Mega Drive.

---

## 👥 Equipe

| Integrante | Módulo | Responsabilidade |
|------------|--------|------------------|
| **Matheus** | Módulo 1: Clientes | Cadastro e gestão dos clientes da locadora |
| **Samarah** | Módulo 2: Catálogo de Cartuchos | Acervo de jogos SNES e Mega Drive |
| **Luiz** | Módulo 3: Acessórios e Manutenção | Controles, cabos, adaptadores e itens em reparo |
| **Rodrigo** | Módulo 4: Locações e Relatórios | Locação/devolução e relatórios analíticos |

---

## 📦 Funcionalidades

Cada módulo possui seu próprio submenu com as 4 operações fundamentais (CRUD):

| Módulo | Cadastrar | Listar / Buscar | Editar | Remover |
|--------|-----------|-----------------|--------|---------|
| Clientes | Cadastrar cliente | Listar / buscar por nome ou ID | Editar dados e pontos de fidelidade | Remover cliente |
| Cartuchos | Cadastrar cartucho | Listar catálogo / filtrar por console | Alterar preço ou quantidade | Excluir do catálogo |
| Acessórios | Registrar acessório | Consultar estoque | Atualizar custo / status de reparo | Dar baixa em item danificado |
| Locações | Registrar locação | Listar histórico | Registrar devolução | Cancelar locação |

**Relatórios (Módulo 4):**
- Cartucho mais alugado
- Cliente com mais locações
- Locações de um cliente específico
- Locações em aberto

---

## 🗂️ Estrutura de dados

Os dados ficam em **vetores globais de structs** (tamanho 50) na memória RAM. Cada módulo tem sua struct, seu vetor e seu contador:

| Struct | Vetor | Campos principais |
|--------|-------|-------------------|
| `Cliente` | `listaClientes[50]` | id, nome, telefone, pontos de fidelidade, ativo |
| `Cartucho` | `catalogoCartuchos[50]` | id, título, console, preço da diária, quantidade disponível |
| `Acessorio` | `estoqueAcessorios[50]` | id, descrição, console compatível, custo de reposição, em manutenção |
| `Locacao` | `historicoLocacoes[50]` | id, id do cliente, id do cartucho, dias, valor total, devolvido |

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

- Cada integrante trabalha na própria branch: `modulo-clientes`, `modulo-cartuchos`, `modulo-acessorios`, `modulo-locacoes`.
- Cada pessoa edita **somente a própria seção** do `main.c`, identificada por comentário `// Autor: Nome`.
- Alterações entram na `main` por Pull Request.
- Sempre fazer `git pull` antes de começar a trabalhar.

---

## 🛣️ Status do projeto

**Checkpoint 1 (estrutura base):**
- [x] Repositório criado e compartilhado
- [ ] Structs de cada integrante no escopo global
- [ ] Menu principal em loop (`do-while` + `switch-case`)
- [ ] Submenus com Cadastrar, Listar/Buscar, Editar e Remover
- [ ] Funções `void` separadas com identificação de autoria

**Próximas etapas:**
- [ ] Implementar a lógica real de cada operação
- [ ] Relatórios analíticos
- [ ] Salvar e carregar dados em arquivos (`FILE *`)

---

## 📚 Disciplina

**Algoritmos e Pensamento Computacional**: Projeto do 2º Bimestre, Checkpoint 1 (Gateway 1).
