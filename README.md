# Nome do Projeto / Sistema de Gestão de Restaurante

## 1. Visão Geral do Sistema
- Nosso sistema é um sistema de gerenciamento de pedidos para restaurantes. Ele funciona via terminal e cosnegue integrar o atendimento do garçom com o cozinheiro e com a administração do restaurante. Nossa ideia inicial era que também cobrisse o caixa, mas como um dos nossos integrantes saiu do grupo de última hora, acabamos ficando sem tempo para implementar corretamente.
- O sistema seria utilizado por restaurantes para organizar as demandas e gerenciar mesas e pedidos. Garçons utilizariam o sistema para gerenciar mesas e pedidos, cozinheiros utilizariam para gerenciar pedidos pendentes e o caixa utilizaria para fechar contas e fazer pagamentos.

## 2. Integrantes do Grupo
- João Pedro Teixeira Cunha - 2026013610
- Joaquim Borille Carvalho - 2026013599

## 3. Principais Funcionalidades
- Módulo de Autenticação e Perfis
- Gestão de Mesas
- Gestão de Cardápio / Produtos
- Gestão de Pedidos e Itens
- Módulo de Pagamentos
- Histórico e Clientes

## 4. Requisitos e Modelagem

### 4.1. User Stories
- **US01 -- Autentificar Usuário
Elemento        |     Descrição
-------------------------------------------------
Ator principal   |   Usuário do Sistema
Pré-condição     |   Usuário cadastrado e ativo.           
Fluxo Principal  |   1. O usuário informa login e senha.
                 |   2. O sistema valida as credenciais.
                 |   3. O sistema identifica o perfil e as permissões.
                 |   4. O sistema cria a sessão e apresenta o painel correspondente.
Fluxo Alternativo|  Credenciais inválidas: o sistema nega o acesso e informa a falha sem revelar dados sensíveis. 
Pós-condição     |   Usuário autenticado e identificado nas operações seguintes.
-------------------------------------------------

- **US02 -- Abrir Pedido
Elemento        |     Descrição
-------------------------------------------------
Ator principal   |   Garçom / Atendente
Pré-condição     |   Usuário autenticado; mesa/modalidade disponível.           
Fluxo Principal  |   1. O atendente seleciona a mesa ou modalidade de atendimento.
                 |   2. O sistema verifica disponibilidade.
                 |   3. O atendente confirma a abertura.
                 |   4. O sistema gera o número do pedido, registra data/hora e responsável.
                 |   5. Quando aplicável, a mesa é marcada como ocupada.  
Fluxo Alternativo|   Mesa indisponível: o sistema impede a abertura e exibe o motivo.
Pós-condição     |   Pedido criado no estado ABERTO.
-------------------------------------------------

- **US03 -- Adicionar item ao Pedido
Elemento        |     Descrição
-------------------------------------------------
Ator principal   |   Garçom / Atendente
Pré-condição     |   Pedido aberto.           
Fluxo Principal  |   1. O atendente pesquisa ou seleciona um produto.
                 |   2. Informa quantidade e observações, se houver.
                 |   3. O sistema valida disponibilidade e quantidade.
                 |   4. O sistema registra preço unitário e calcula subtotal.
                 |   5. O total parcial do pedido é atualizado.      
Fluxo Alternativo|   Produto indisponível ou quantidade inválida: inclusão recusada.
Pós-condição     |   Item registrado no pedido.
-------------------------------------------------

- **US04 -- Enviar itens a cozinha
Elemento        |     Descrição
-------------------------------------------------
Ator principal   |   Garçom / Sistema
Pré-condição     |   Pedido com pelo menos um item ainda não enviado.           
Fluxo Principal  |   1. O atendente confirma o envio.
                 |   2. O sistema registra o horário de envio dos itens. 
                 |   3. Os itens aparecem na fila da cozinha.
                 |   4. O status operacional passa a indicar aguardando preparo.     
Fluxo Alternativo|   Nenhum item pendente de envio: o sistema não cria nova remessa.
Pós-condição     |   tens disponíveis para produção.
------------------------------------------------

- **US05 -- Atualizar preparo
Elemento        |     Descrição
-------------------------------------------------
Ator principal   |   Cozinha
Pré-condição     |   Existem itens aguardando preparo.           
Fluxo Principal  |   1. A cozinha seleciona o pedido/item.
                 |   2. Marca como EM PREPARO.  
                 |   3. Ao concluir, marca como PRONTO.
                 |   4. O sistema registra usuário e horários. 
                 |   5. O salão recebe a indicação de que o item pode ser entregue.     
Fluxo Alternativo|   Transição inválida: o sistema rejeita a mudança.
Pós-condição     |   Estado do item atualizado e rastreado.
-------------------------------------------------

- **US06 -- Fechar a Conta
Elemento        |     Descrição
-------------------------------------------------
Ator principal   |   Garçom / Caixa
Pré-condição     |   Pedido ativo com consumo registrado.     
Fluxo Principal  |   1. O usuário solicita o fechamento.
                 |   2. O sistema reúne os itens válidos e calcula subtotal. 
                 |   3. Aplica taxa de serviço configurada.
                 |   4. Aplica desconto quando autorizado.
                 |   5. Exibe total final e saldo a pagar.    
Fluxo Alternativo|   Há inconsistência ou item pendente de validação: o sistema solicita correção antes de prosseguir.
Pós-condição     |   Conta pronta para recebimento.
-------------------------------------------------

- **US07 -- Registrar pagamento e encerrar
Elemento        |     Descrição
-------------------------------------------------
Ator principal   |   Caixa
Pré-condição     |   Conta calculada e usuário autorizado.       
Fluxo Principal  |   1. O caixa seleciona a forma de pagamento.
                 |   2. Informa o valor recebido. 
                 |   3. O sistema atualiza o saldo restante.
                 |   4. Se houver dinheiro, calcula o troco.
                 |   5. Quando o saldo chega a zero, o sistema finaliza o pedido.
                 |   6. A mesa é liberada quando aplicável.    
Fluxo Alternativo|   Pagamento parcial: o pedido permanece aguardando pagamento até completar o total.
Pós-condição     |   Pedido FINALIZADO e pagamento registrado.
-------------------------------------------------

### 4.2. Cartões CRC (Classes, Responsabilidades e Colaboradores)
- Os cartões CRC estão detalhados de forma concisa a partir do modelo do site apresentado no ambiente do Moodle, estando no arquivo 'CRC.json', sendo convertido direto do site para essa forma. 

## 5. Arquitetura e Decisões de Projeto

### 5.1. Conceitos de Orientação a Objetos Aplicados
- **Abstração:** Foi aplicada em todos os hpps, pois modelamos um restaurante inteiro no formato de classes com seus respectivos atributos. Por exemplo, em pedido.hpp, a classe abstrai o ciclo de um consumo de uma mesa (cálculo de subtotal, aplicação de taxa de serviço, controle de pagamentos e encerramento), fazendo com que o consumidor da classe não tenha que se preocupar com os processos e cálculos. Outro exemplo é no banco de dados, que basta chamar salvarPedido() ou buscarUsuarioPorLogin().

- **Encapsulamento:** [Onde e como foi aplicado]

- **Herança:** Foi utilizada nas classes de usuário, sendo Usuario a classe virtual base e Administrador, Garcom, Cozinheiro e Caixa as subclasses filhas.

- **Polimorfismo:** Como utilizamos herança nas classes de usuário, utilizamos polimorfismo na autenticação do usuário. Ao chamar a função Autenticacao::possuiPermissao(PerfilAcesso perfilNecessario), utilizamos o ponteiro do usuário logado para chamar a função possuiAcesso(perfilNecessario), que já retorna true ou false com base no tipo de usuário. Como a função possuiAcesso() está na classe virtual, é garantido que todas as classes vão fazer overide nessa função e implementar as próprias permissões. Com isso, podemos adicionar uma nova classe com novas permissões muito mais facilmente.
- **Modularização:** A estrutura de pastas é bem organizada, contendo um arquivo para cada classe. As classes interagem entre si sem problemas de inclusão de classes.

### 5.2. Programação Defensiva e Tratamento de Exceções


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
```Dockerfile
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    cmake \
    gdb \
    valgrind \
    git \
    && rm -rf /var/lib/apt/lists/*
```

Todos os pré-requisitos são instalados automaticamente durante o build do conteiner Docker, garantindo que a compilação e verificação de erros ocorra de maneira correta e padronizada independentemente da máquina do programador.

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
