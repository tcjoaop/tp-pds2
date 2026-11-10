# Nome do Projeto / Sistema de Gestão de Restaurante

## 1. Visão Geral do Sistema
- Nosso sistema é um sistema de gerenciamento de pedidos para restaurantes. Ele funciona via terminal e cosnegue integrar o atendimento do garçom com o cozinheiro e com a administração do restaurante. Nossa ideia inicial era que também cobrisse o caixa, mas como um dos nossos integrantes saiu do grupo de última hora, acabamos ficando sem tempo para implementar corretamente.
- [Público-alvo / Contexto de utilização]

## 2. Integrantes do Grupo
- Nome - Matrícula
- Nome - Matrícula
- Nome - Matrícula

## 3. Principais Funcionalidades
- [Módulo de Autenticação e Perfis]
- [Gestão de Mesas]
- [Gestão de Cardápio / Produtos]
- [Gestão de Pedidos e Itens]
- [Módulo de Pagamentos]
- [Histórico e Clientes]

## 4. Requisitos e Modelagem

### 4.1. User Stories
- **US01 - [Título da História]**
  - **Descrição:** Como *[tipo de usuário]*, quero *[funcionalidade/ação]* para que *[benefício/valor]*.
  - **Critérios de Aceitação/Validação:**
    - Critério 1
    - Critério 2
- **US02 - [Título da História]**
  - **Descrição:** ...
  - **Critérios de Aceitação/Validação:** ...
- **US03 - [Título da História]**
  - ...
- **US04 - [Título da História]**
  - ...
- **US05 - [Título da História]**
  - ...
- **US06 - [Título da História]**
  - ...

### 4.2. Cartões CRC (Classes, Responsabilidades e Colaboradores)
- [Descrição resumida ou referência ao arquivo `CRC.json`]
- [Tabela ou listagem das principais classes, suas responsabilidades e colaborações]

## 5. Arquitetura e Decisões de Projeto

### 5.1. Conceitos de Orientação a Objetos Aplicados
- **Abstração:** [Onde e como foi aplicada]
- **Encapsulamento:** [Onde e como foi aplicado]
- **Herança:** [Diagrama ou descrição da hierarquia de classes utilizada]
- **Polimorfismo:** [Classes base, métodos virtuais e comportamento dinâmico]
- **Modularização:** [Estrutura de pastas, separação em arquivos .hpp e .cpp]

### 5.2. Programação Defensiva e Tratamento de Exceções
- [Estratégia de sanitização e validação de entradas]
- [Exceções utilizadas ou criadas e como são tratadas]

## 6. Estrutura do Repositório
```text
tp-pds2/
├── bin/            # Executáveis gerados
├── documentation/  # Arquivos de cabeçalho (.hpp) e documentação
├── obj/            # Arquivos objeto (.o, .d)
├── src/            # Implementações (.cpp)
├── tests/          # Testes unitários
├── Dockerfile      # Configuração do ambiente Docker
├── compose.yaml    # Orquestração do contêiner
├── makefile        # Script de compilação
└── README.md       # Documentação do projeto
```

## 7. Instruções de Compilação e Execução

### 7.1. Pré-requisitos
- [Compilador g++, Make, Docker, etc.]

### 7.2. Executando via Docker
```bash
docker compose run --rm --build app bash
make
make run
```

### 7.3. Executando Localmente (Sem Docker)
```bash
make
make run
```

## 8. Testes de Unidade e Cobertura

### 8.1. Execução dos Testes
```bash
make test
```

### 8.2. Verificação de Cobertura de Código
- [Comando para gerar relatório de cobertura (gcov/lcov)]
- [Resumo da cobertura atual]

## 9. Documentação da API (Doxygen)
- [Instruções para gerar a documentação Doxygen]
```bash
doxygen Doxyfile
```

## 10. Padronização de Código (Code Style)
- **Nomes de arquivos:** `nome_de_arquivo.extensao`
- **Classes:** `NomeDaClasse` (PascalCase)
- **Métodos e funções:** `nomeDoMetodo()` (lowerCamelCase)
- **Atributos e variáveis:** `nome_atributo` (snake_case)
- **Constantes:** `NOME_CONSTANTE` (SCREAMING_SNAKE_CASE)
