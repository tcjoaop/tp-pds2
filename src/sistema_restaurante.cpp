#include "../documentation/sistema_restaurante.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>

// Funcoes auxiliares de sanitizacao de entrada
static void limparBufferEntrada() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int lerInteiroSanitizado(const std::string& prompt) {
    int valor;
    while (true) {
        std::cout << prompt;
        std::cin >> valor;
        if (!std::cin.fail()) {
            limparBufferEntrada();
            return valor;
        }
        if (std::cin.eof()) {
            throw std::ios_base::failure("Entrada encerrada.");
        }
        std::cout << "[ERRO] Entrada invalida! Digite apenas numeros inteiros." << std::endl;
        std::cin.clear();
        limparBufferEntrada();
    }
}

static double lerDoubleSanitizado(const std::string& prompt) {
    double valor;
    while (true) {
        std::cout << prompt;
        std::cin >> valor;
        if (!std::cin.fail()) {
            limparBufferEntrada();
            return valor;
        }
        if (std::cin.eof()) {
            throw std::ios_base::failure("Entrada encerrada.");
        }
        std::cout << "[ERRO] Entrada invalida! Digite um valor numerico valido." << std::endl;
        std::cin.clear();
        limparBufferEntrada();
    }
}

static std::string lerTextoSanitizado(const std::string& prompt) {
    std::string valor;
    while (true) {
        std::cout << prompt;
        std::cin >> valor;
        if (!std::cin.fail()) {
            limparBufferEntrada();
            return valor;
        }
        if (std::cin.eof()) {
            throw std::ios_base::failure("Entrada encerrada.");
        }
        std::cout << "[ERRO] Entrada invalida. Tente novamente." << std::endl;
        std::cin.clear();
        limparBufferEntrada();
    }
}

static std::string lerLinhaSanitizada(const std::string& prompt) {
    std::string valor;
    std::cout << prompt;
    if (!std::getline(std::cin, valor)) {
        throw std::ios_base::failure("Entrada encerrada.");
    }
    return valor;
}

static char lerCaractereSanitizado(const std::string& prompt) {
    return lerTextoSanitizado(prompt).front();
}

SistemaRestaurante::SistemaRestaurante(const std::string& caminhoBancoDados)
    : bancoDados(caminhoBancoDados), autenticacao(bancoDados) {}

bool SistemaRestaurante::inicializar() {
    if (!bancoDados.conectar()) {
        std::cerr << "Falha ao conectar ao banco de dados." << std::endl;
        return false;
    }
    return true;
}

void SistemaRestaurante::executar() {
    try {
        if (!autenticacao.estaLogado()) {
            exibirTelaLogin();
        } else {
            exibirTelaPrincipal();
        }
    } catch (const std::ios_base::failure&) {
        std::cout << "\nEntrada encerrada. Finalizando o sistema." << std::endl;
        autenticacao.logout();
        bancoDados.desconectar();
    } catch (const std::exception& e) {
        std::cerr << "\n[ERRO DO SISTEMA] " << e.what() << std::endl;
        bancoDados.desconectar();
    }
}

void SistemaRestaurante::exibirTelaLogin() {
    std::string login, senha;
    std::cout << "=== TELA DE LOGIN ===" << std::endl;
    login = lerTextoSanitizado("Login: ");
    senha = lerTextoSanitizado("Senha: ");
    if (autenticacao.login(login, senha)) {
        std::cout << "Login bem-sucedido!" << std::endl;
        exibirTelaPrincipal();
    } else {
        std::cout << "Falha no login. Tente novamente." << std::endl;
        exibirTelaLogin();
    }
}

void SistemaRestaurante::exibirTelaPrincipal() {
    try {
        std::cout << "\n=== TELA PRINCIPAL ===" << std::endl;
        std::cout << "1. Modulo Mesas" << std::endl;
        std::cout << "2. Modulo Pedidos" << std::endl;
        std::cout << "3. Modulo Cozinha" << std::endl;
        std::cout << "4. Modulo Caixa" << std::endl;
        std::cout << "5. Modulo Relatorios" << std::endl;
        std::cout << "6. Modulo Cadastros" << std::endl;
        std::cout << "7. Logout" << std::endl;
        std::cout << "0. Sair" << std::endl;

        int opcao = lerInteiroSanitizado("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                moduloMesas();
                break;
            case 2:
                moduloPedidos();
                break;
            case 3:
                moduloCozinha();
                break;
            case 4:
                moduloCaixa();
                break;
            case 5:
                moduloRelatorios();
                break;
            case 6:
                moduloCadastros();
                break;
            case 7:
                autenticacao.logout();
                std::cout << "Logout realizado com sucesso." << std::endl;
                exibirTelaLogin();
                return;
            case 0:
                autenticacao.logout();
                bancoDados.desconectar();
                return;
            default:
                std::cout << "Opcao invalida." << std::endl;
                break;
        }
    } catch (const std::ios_base::failure&) {
        throw;
    } catch (const std::invalid_argument& e) {
        std::cout << "\n[ERRO DE VALIDACAO] " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\n[ERRO DO SISTEMA] " << e.what() << std::endl;
    }

    exibirTelaPrincipal(); // Volta para a tela principal após a operação
}

void SistemaRestaurante::moduloMesas() {
    if (!autenticacao.possuiPermissao(PerfilAcesso::GARCOM)) {
        std::cout << "\nAcesso negado. Voce nao possui permissao para acessar o modulo de mesas.\n" << std::endl;
        return;
    }

    int opcao = -1;
    while (opcao != 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "             MODULO DE MESAS            " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Listar todas as mesas" << std::endl;
        std::cout << "2. Ocupar mesa" << std::endl;
        std::cout << "3. Liberar mesa" << std::endl;
        std::cout << "4. Reservar mesa" << std::endl;
        std::cout << "5. Cadastrar nova mesa" << std::endl;
        std::cout << "0. Voltar ao menu principal" << std::endl;
        std::cout << "Escolha uma opcao: ";
        
        opcao = lerInteiroSanitizado("");

        switch (opcao) {
            case 1: {
                std::vector<Mesa> mesas = bancoDados.listarMesas();
                std::cout << "\n--- LISTA DE MESAS ---" << std::endl;
                if (mesas.empty()) {
                    std::cout << "Nenhuma mesa cadastrada no sistema." << std::endl;
                } else {
                    for (const auto& mesa : mesas) {
                        std::string statusStr;
                        switch (mesa.getStatus()) {
                            case StatusMesa::LIVRE: statusStr = "LIVRE"; break;
                            case StatusMesa::OCUPADA: statusStr = "OCUPADA"; break;
                            case StatusMesa::RESERVADA: statusStr = "RESERVADA"; break;
                            case StatusMesa::AGUARDANDO_PAGAMENTO: statusStr = "AGUARDANDO PAGAMENTO"; break;
                            case StatusMesa::INDISPONIVEL: statusStr = "INDISPONIVEL"; break;
                            default: statusStr = "DESCONHECIDO"; break;
                        }
                        std::cout << "Mesa ID: " << mesa.getId()
                                  << " | Numero: " << mesa.getNumero()
                                  << " | Capacidade: " << mesa.getCapacidade() << " lugares"
                                  << " | Status: [" << statusStr << "]" << std::endl;
                    }
                }
                break;
            }
            case 2: {
                int idMesa;
                std::cout << "Digite o ID da mesa que deseja ocupar: ";
                idMesa = lerInteiroSanitizado("");

                Mesa* mesa = bancoDados.buscarMesaPorId(idMesa);
                if (mesa == nullptr) {
                    std::cout << "[ERRO] Mesa com ID " << idMesa << " nao encontrada." << std::endl;
                } else {
                    if (mesa->getStatus() == StatusMesa::OCUPADA) {
                        std::cout << "[AVISO] A mesa " << mesa->getNumero() << " ja esta ocupada." << std::endl;
                    } else {
                        mesa->setStatus(StatusMesa::OCUPADA);
                        if (bancoDados.salvarMesa(*mesa)) {
                            std::cout << "[SUCESSO] Mesa " << mesa->getNumero() << " agora esta OCUPADA." << std::endl;
                        } else {
                            std::cout << "[ERRO] Falha ao atualizar status da mesa no banco de dados." << std::endl;
                        }
                    }
                    delete mesa;
                }
                break;
            }
            case 3: {
                int idMesa;
                std::cout << "Digite o ID da mesa que deseja liberar: ";
                idMesa = lerInteiroSanitizado("");

                Mesa* mesa = bancoDados.buscarMesaPorId(idMesa);
                if (mesa == nullptr) {
                    std::cout << "[ERRO] Mesa com ID " << idMesa << " nao encontrada." << std::endl;
                } else {
                    if (mesa->getStatus() == StatusMesa::LIVRE) {
                        std::cout << "[AVISO] A mesa " << mesa->getNumero() << " ja esta livre." << std::endl;
                    } else {
                        mesa->setStatus(StatusMesa::LIVRE);
                        if (bancoDados.salvarMesa(*mesa)) {
                            std::cout << "[SUCESSO] Mesa " << mesa->getNumero() << " foi LIBERADA com sucesso." << std::endl;
                        } else {
                            std::cout << "[ERRO] Falha ao atualizar status da mesa no banco de dados." << std::endl;
                        }
                    }
                    delete mesa;
                }
                break;
            }
            case 4: {
                int idMesa;
                std::cout << "Digite o ID da mesa que deseja reservar: ";
                idMesa = lerInteiroSanitizado("");

                Mesa* mesa = bancoDados.buscarMesaPorId(idMesa);
                if (mesa == nullptr) {
                    std::cout << "[ERRO] Mesa com ID " << idMesa << " nao encontrada." << std::endl;
                } else {
                    if (mesa->getStatus() != StatusMesa::LIVRE) {
                        std::cout << "[AVISO] Apenas mesas com status LIVRE podem ser reservadas." << std::endl;
                    } else {
                        mesa->setStatus(StatusMesa::RESERVADA);
                        if (bancoDados.salvarMesa(*mesa)) {
                            std::cout << "[SUCESSO] Mesa " << mesa->getNumero() << " agora esta RESERVADA." << std::endl;
                        } else {
                            std::cout << "[ERRO] Falha ao atualizar status da mesa no banco de dados." << std::endl;
                        }
                    }
                    delete mesa;
                }
                break;
            }
            case 5: {
                std::cout << "\n--- CADASTRAR NOVA MESA ---" << std::endl;
                int idMesa, numeroMesa, capacidadeMesa;

                std::cout << "Digite o ID da nova mesa: ";
                idMesa = lerInteiroSanitizado("");

                // Verifica se o ID ja existe
                Mesa* existente = bancoDados.buscarMesaPorId(idMesa);
                if (existente != nullptr) {
                    std::cout << "[ERRO] Ja existe uma mesa com o ID " << idMesa << "." << std::endl;
                    delete existente;
                    break;
                }

                std::cout << "Digite o numero da mesa: ";
                numeroMesa = lerInteiroSanitizado("");

                std::cout << "Digite a capacidade da mesa (lugares): ";
                capacidadeMesa = lerInteiroSanitizado("");
                if (capacidadeMesa <= 0) {
                    std::cout << "[ERRO] Capacidade deve ser maior que 0." << std::endl;
                    break;
                }

                // Cria a nova mesa com status inicial LIVRE
                Mesa novaMesa(idMesa, numeroMesa, capacidadeMesa, StatusMesa::LIVRE);

                if (bancoDados.salvarMesa(novaMesa)) {
                    std::cout << "[SUCESSO] Mesa numero " << numeroMesa << " (ID " << idMesa 
                              << ") cadastrada com sucesso!" << std::endl;
                } else {
                    std::cout << "[ERRO] Falha ao salvar a nova mesa no banco de dados." << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Retornando ao menu principal..." << std::endl;
                break;
            default:
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
                break;
        }
    }
}

void SistemaRestaurante::moduloPedidos() {
    if (!autenticacao.possuiPermissao(PerfilAcesso::GARCOM)) {
        std::cout << "\nAcesso negado. Voce nao possui permissao para acessar o modulo de pedidos.\n" << std::endl;
        return;
    }

    int opcao = -1;
    while (opcao != 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "            MODULO DE PEDIDOS           " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Listar pedidos abertos" << std::endl;
        std::cout << "2. Abrir novo pedido" << std::endl;
        std::cout << "3. Adicionar item a um pedido" << std::endl;
        std::cout << "4. Ver detalhes/extrato de um pedido" << std::endl;
        std::cout << "5. Cancelar um item do pedido" << std::endl;
        std::cout << "6. Cancelar pedido inteiro" << std::endl;
        std::cout << "0. Voltar ao menu principal" << std::endl;
        std::cout << "Escolha uma opcao: ";

        opcao = lerInteiroSanitizado("");

        switch (opcao) {
            case 1: {
                std::vector<Pedido> pedidos = bancoDados.listarPedidos();
                std::cout << "\n--- LISTA DE PEDIDOS ATIVOS ---" << std::endl;
                bool encontrou = false;
                for (const auto& ped : pedidos) {
                    if (ped.getStatus() != StatusPedido::FINALIZANDO && 
                        ped.getStatus() != StatusPedido::CANCELADO) {
                        encontrou = true;
                        std::string statusStr;
                        switch (ped.getStatus()) {
                            case StatusPedido::ABERTO: statusStr = "ABERTO"; break;
                            case StatusPedido::AGUARDANDO_PREPARO: statusStr = "AGUARDANDO PREPARO"; break;
                            case StatusPedido::EM_PREPARO: statusStr = "EM PREPARO"; break;
                            case StatusPedido::PRONTO: statusStr = "PRONTO"; break;
                            case StatusPedido::ENTREGUE: statusStr = "ENTREGUE"; break;
                            case StatusPedido::AGUARDANDO_PAGAMENTO: statusStr = "AGUARDANDO PAGAMENTO"; break;
                            default: statusStr = "OUTRO"; break;
                        }
                        int mesaNum = (ped.getMesa() != nullptr) ? ped.getMesa()->getNumero() : -1;
                        std::cout << "Pedido ID: " << ped.getId()
                                  << " | Mesa: " << (mesaNum != -1 ? std::to_string(mesaNum) : "Balcao")
                                  << " | Status: [" << statusStr << "]"
                                  << " | Itens: " << ped.getItens().size()
                                  << " | Total: R$ " << ped.calcularTotalSemTaxa() << std::endl;
                    }
                }
                if (!encontrou) {
                    std::cout << "Nenhum pedido ativo no momento." << std::endl;
                }
                break;
            }
            case 2: {
                std::cout << "\n--- ABRIR NOVO PEDIDO ---" << std::endl;
                int idPedido, idMesa;

                std::cout << "Digite o ID para o novo pedido: ";
                idPedido = lerInteiroSanitizado("");

                Pedido* existente = bancoDados.buscarPedidoPorId(idPedido);
                if (existente != nullptr) {
                    std::cout << "[ERRO] Ja existe um pedido com o ID " << idPedido << "." << std::endl;
                    delete existente;
                    break;
                }

                std::cout << "Digite o ID da mesa: ";
                idMesa = lerInteiroSanitizado("");

                Mesa* mesa = bancoDados.buscarMesaPorId(idMesa);
                if (mesa == nullptr) {
                    std::cout << "[ERRO] Mesa com ID " << idMesa << " nao encontrada." << std::endl;
                    break;
                }

                // Ocupa a mesa caso esteja livre
                if (mesa->getStatus() == StatusMesa::LIVRE) {
                    mesa->setStatus(StatusMesa::OCUPADA);
                    bancoDados.salvarMesa(*mesa);
                }

                Pedido novoPedido(idPedido, "2026-11-10 12:00:00", autenticacao.getUsuarioLogado(), mesa);

                if (bancoDados.salvarPedido(novoPedido)) {
                    std::cout << "[SUCESSO] Pedido ID " << idPedido << " aberto para a mesa " 
                              << mesa->getNumero() << "!" << std::endl;
                } else {
                    std::cout << "[ERRO] Falha ao salvar o pedido no banco de dados." << std::endl;
                }
                delete mesa;
                break;
            }
            case 3: {
                std::cout << "\n--- ADICIONAR ITEM AO PEDIDO ---" << std::endl;
                int idPedido;
                std::cout << "Digite o ID do pedido: ";
                idPedido = lerInteiroSanitizado("");

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido ID " << idPedido << " nao encontrado." << std::endl;
                    break;
                }

                if (pedido->getStatus() == StatusPedido::CANCELADO || pedido->getStatus() == StatusPedido::FINALIZANDO) {
                    std::cout << "[ERRO] Nao e possivel adicionar itens a um pedido fechado ou cancelado." << std::endl;
                    delete pedido;
                    break;
                }

                // Lista os produtos disponíveis
                std::vector<Produto> produtos = bancoDados.listarProdutos();
                if (produtos.empty()) {
                    std::cout << "[AVISO] Nao ha produtos cadastrados no cardapio." << std::endl;
                    delete pedido;
                    break;
                }

                std::cout << "\n--- CARDAPIO DISPONIVEL ---" << std::endl;
                for (const auto& prod : produtos) {
                    if (prod.getDisponivel()) {
                        std::cout << "ID: " << prod.getId()
                                  << " | Nome: " << prod.getNome()
                                  << " | Preco: R$ " << prod.getPreco()
                                  << " | Tempo: " << prod.getTempoPreparo() << "min" << std::endl;
                    }
                }

                int idProduto, quantidade;
                std::cout << "Digite o ID do produto desejado: ";
                idProduto = lerInteiroSanitizado("");

                Produto* produtoEscolhido = bancoDados.buscarProdutoPorId(idProduto);
                if (produtoEscolhido == nullptr) {
                    std::cout << "[ERRO] Produto nao encontrado." << std::endl;
                    delete pedido;
                    break;
                }

                std::cout << "Digite a quantidade: ";
                quantidade = lerInteiroSanitizado("");
                if (quantidade <= 0) {
                    std::cout << "[ERRO] Quantidade deve ser maior que 0." << std::endl;
                    delete produtoEscolhido;
                    delete pedido;
                    break;
                }

                std::string obs;
                obs = lerLinhaSanitizada("Observacoes (ex: sem cebola) [Pressione ENTER para nenhuma]: ");

                int proximoItemId = static_cast<int>(pedido->getItens().size()) + 1;
                ItemPedido novoItem(proximoItemId, *produtoEscolhido, quantidade, produtoEscolhido->getPreco(), obs);

                pedido->adicionarItem(novoItem);

                if (bancoDados.salvarPedido(*pedido)) {
                    std::cout << "[SUCESSO] Item '" << produtoEscolhido->getNome() 
                              << "' (x" << quantidade << ") adicionado ao pedido!" << std::endl;
                } else {
                    std::cout << "[ERRO] Falha ao atualizar o pedido no banco de dados." << std::endl;
                }

                delete produtoEscolhido;
                delete pedido;
                break;
            }
            case 4: {
                int idPedido;
                std::cout << "Digite o ID do pedido: ";
                idPedido = lerInteiroSanitizado("");

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido ID " << idPedido << " nao encontrado." << std::endl;
                    break;
                }

                std::cout << "\n========================================" << std::endl;
                std::cout << "           EXTRATO DO PEDIDO #" << pedido->getId() << std::endl;
                std::cout << "========================================" << std::endl;
                if (pedido->getMesa() != nullptr) {
                    std::cout << "Mesa: " << pedido->getMesa()->getNumero() << std::endl;
                }
                std::cout << "Itens no Pedido:" << std::endl;

                if (pedido->getItens().empty()) {
                    std::cout << "  (Nenhum item adicionado ate o momento)" << std::endl;
                } else {
                    for (const auto& item : pedido->getItens()) {
                        std::string statusItem;
                        switch (item.getStatus()) {
                            case StatusItemPedido::PENDENTE: statusItem = "PENDENTE"; break;
                            case StatusItemPedido::ENVIADO_COZINHA: statusItem = "NA COZINHA"; break;
                            case StatusItemPedido::EM_PREPARO: statusItem = "PREPARANDO"; break;
                            case StatusItemPedido::PRONTO: statusItem = "PRONTO"; break;
                            case StatusItemPedido::ENTREGUE: statusItem = "ENTREGUE"; break;
                            case StatusItemPedido::CANCELADO: statusItem = "CANCELADO"; break;
                        }
                        std::cout << "  - [" << item.getId() << "] "
                                  << item.getProduto().getNome()
                                  << " x" << item.getQuantidade()
                                  << " (R$ " << item.getPrecoUnitario() << " cada)"
                                  << " = Subtotal: R$ " << item.calcularSubtotal()
                                  << " [" << statusItem << "]";
                        if (!item.getObservacoes().empty()) {
                            std::cout << " (Obs: " << item.getObservacoes() << ")";
                        }
                        std::cout << std::endl;
                    }
                }
                std::cout << "----------------------------------------" << std::endl;
                std::cout << "Subtotal: R$ " << pedido->calcularTotalSemTaxa() << std::endl;
                std::cout << "Taxa de Servico: R$ " << pedido->calcularTaxaServico() << std::endl;
                std::cout << "Total a Pagar: R$ " << pedido->calcularTotalComTaxa() << std::endl;
                std::cout << "Total Pago: R$ " << pedido->calcularTotalPago() << std::endl;
                std::cout << "Saldo Restante: R$ " << pedido->calcularSaldoRestante() << std::endl;
                std::cout << "========================================" << std::endl;

                delete pedido;
                break;
            }
            case 5: {
                int idPedido, idItem;
                std::cout << "Digite o ID do pedido: ";
                idPedido = lerInteiroSanitizado("");

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido nao encontrado." << std::endl;
                    break;
                }

                std::cout << "Digite o ID do item a cancelar: ";
                idItem = lerInteiroSanitizado("");

                ItemPedido* item = pedido->buscarItem(idItem);
                if (item == nullptr) {
                    std::cout << "[ERRO] Item ID " << idItem << " nao encontrado neste pedido." << std::endl;
                } else if (!item->podeSerCancelado()) {
                    std::cout << "[ERRO] Este item ja esta pronto ou foi entregue e nao pode mais ser cancelado!" << std::endl;
                } else {
                    item->setStatus(StatusItemPedido::CANCELADO);
                    bancoDados.salvarPedido(*pedido);
                    std::cout << "[SUCESSO] Item cancelado com sucesso." << std::endl;
                }
                delete pedido;
                break;
            }
            case 6: {
                int idPedido;
                std::cout << "Digite o ID do pedido que deseja cancelar: ";
                idPedido = lerInteiroSanitizado("");

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido nao encontrado." << std::endl;
                    break;
                }

                char confirma;
                std::cout << "Tem certeza que deseja cancelar o pedido #" << idPedido << "? (s/n): ";
                confirma = lerCaractereSanitizado("");

                if (confirma == 's' || confirma == 'S') {
                    pedido->cancelar();
                    if (pedido->getMesa() != nullptr) {
                        pedido->getMesa()->setStatus(StatusMesa::LIVRE);
                        bancoDados.salvarMesa(*pedido->getMesa());
                    }
                    bancoDados.salvarPedido(*pedido);
                    std::cout << "[SUCESSO] Pedido cancelado e mesa liberada." << std::endl;
                } else {
                    std::cout << "Operacao cancelada." << std::endl;
                }
                delete pedido;
                break;
            }
            case 0:
                std::cout << "Retornando ao menu principal..." << std::endl;
                break;
            default:
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
                break;
        }
    }
}

void SistemaRestaurante::moduloCozinha() {
    if (!autenticacao.possuiPermissao(PerfilAcesso::COZINHEIRO)) {
        std::cout << "\nAcesso negado. Voce nao possui permissao para acessar o modulo da cozinha.\n" << std::endl;
        return;
    }

    int opcao = -1;
    while (opcao != 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "            MODULO DA COZINHA           " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Ver fila de itens para preparo" << std::endl;
        std::cout << "2. Iniciar preparo de um item" << std::endl;
        std::cout << "3. Marcar item como pronto" << std::endl;
        std::cout << "4. Marcar item como entregue" << std::endl;
        std::cout << "0. Voltar ao menu principal" << std::endl;
        std::cout << "Escolha uma opcao: ";

        opcao = lerInteiroSanitizado("");

        switch (opcao) {
            case 1: {
                std::vector<Pedido> pedidos = bancoDados.listarPedidos();
                std::cout << "\n--- FILA DE PRODUCAO NA COZINHA ---" << std::endl;
                bool haItens = false;

                for (const auto& ped : pedidos) {
                    if (ped.getStatus() != StatusPedido::CANCELADO &&
                        ped.getStatus() != StatusPedido::FINALIZANDO) {
                        for (const auto& item : ped.getItens()) {
                            if (item.getStatus() == StatusItemPedido::PENDENTE ||
                                item.getStatus() == StatusItemPedido::ENVIADO_COZINHA ||
                                item.getStatus() == StatusItemPedido::EM_PREPARO) {
                                haItens = true;
                                std::string statusStr;
                                switch (item.getStatus()) {
                                    case StatusItemPedido::PENDENTE: statusStr = "PENDENTE"; break;
                                    case StatusItemPedido::ENVIADO_COZINHA: statusStr = "NA FILA"; break;
                                    case StatusItemPedido::EM_PREPARO: statusStr = "NO FOGO / EM PREPARO"; break;
                                    default: statusStr = "OUTRO"; break;
                                }
                                int mesaNum = (ped.getMesa() != nullptr) ? ped.getMesa()->getNumero() : -1;
                                std::cout << "Pedido #" << ped.getId()
                                          << " (Mesa " << (mesaNum != -1 ? std::to_string(mesaNum) : "Balcao") << ")"
                                          << " | Item ID: " << item.getId()
                                          << " | Prato: " << item.getProduto().getNome()
                                          << " x" << item.getQuantidade()
                                          << " | Tempo Est.: " << item.getProduto().getTempoPreparo() << " min"
                                          << " | Status: [" << statusStr << "]";
                                if (!item.getObservacoes().empty()) {
                                    std::cout << " -> OBS: " << item.getObservacoes();
                                }
                                std::cout << std::endl;
                            }
                        }
                    }
                }
                if (!haItens) {
                    std::cout << "Nenhum item pendente na cozinha no momento." << std::endl;
                }
                break;
            }
            case 2: {
                std::cout << "\n--- INICIAR PREPARO DE ITEM ---" << std::endl;
                int idPedido, idItem;
                std::cout << "Digite o ID do pedido: ";
                idPedido = lerInteiroSanitizado("");

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido ID " << idPedido << " nao encontrado." << std::endl;
                    break;
                }

                std::cout << "Digite o ID do item a preparar: ";
                idItem = lerInteiroSanitizado("");

                ItemPedido* item = pedido->buscarItem(idItem);
                if (item == nullptr) {
                    std::cout << "[ERRO] Item ID " << idItem << " nao encontrado no pedido." << std::endl;
                } else if (item->getStatus() == StatusItemPedido::CANCELADO) {
                    std::cout << "[ERRO] Este item foi cancelado." << std::endl;
                } else if (item->getStatus() == StatusItemPedido::EM_PREPARO) {
                    std::cout << "[AVISO] Este item ja esta em preparo." << std::endl;
                } else if (item->getStatus() == StatusItemPedido::PRONTO || item->getStatus() == StatusItemPedido::ENTREGUE) {
                    std::cout << "[AVISO] Este item ja foi concluido ou entregue." << std::endl;
                } else {
                    item->setStatus(StatusItemPedido::EM_PREPARO);
                    pedido->alterarStatus(StatusPedido::EM_PREPARO);
                    if (bancoDados.salvarPedido(*pedido)) {
                        std::cout << "[SUCESSO] Item '" << item->getProduto().getNome() 
                                  << "' agora esta EM PREPARO!" << std::endl;
                    } else {
                        std::cout << "[ERRO] Falha ao atualizar pedido no banco." << std::endl;
                    }
                }
                delete pedido;
                break;
            }
            case 3: {
                std::cout << "\n--- MARCAR ITEM COMO PRONTO ---" << std::endl;
                int idPedido, idItem;
                std::cout << "Digite o ID do pedido: ";
                idPedido = lerInteiroSanitizado("");

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido ID " << idPedido << " nao encontrado." << std::endl;
                    break;
                }

                std::cout << "Digite o ID do item pronto: ";
                idItem = lerInteiroSanitizado("");

                ItemPedido* item = pedido->buscarItem(idItem);
                if (item == nullptr) {
                    std::cout << "[ERRO] Item ID " << idItem << " nao encontrado no pedido." << std::endl;
                } else if (item->getStatus() == StatusItemPedido::CANCELADO) {
                    std::cout << "[ERRO] Este item foi cancelado." << std::endl;
                } else if (item->getStatus() == StatusItemPedido::PRONTO) {
                    std::cout << "[AVISO] Este item ja esta marcado como pronto." << std::endl;
                } else {
                    item->setStatus(StatusItemPedido::PRONTO);
                    
                    // Verifica se todos os itens estao prontos
                    bool todosProntos = true;
                    for (const auto& i : pedido->getItens()) {
                        if (i.getStatus() != StatusItemPedido::PRONTO && 
                            i.getStatus() != StatusItemPedido::ENTREGUE &&
                            i.getStatus() != StatusItemPedido::CANCELADO) {
                            todosProntos = false;
                            break;
                        }
                    }
                    if (todosProntos) {
                        pedido->alterarStatus(StatusPedido::PRONTO);
                    }

                    if (bancoDados.salvarPedido(*pedido)) {
                        std::cout << "[SUCESSO] Item '" << item->getProduto().getNome() 
                                  << "' PRONTO para ser servido!" << std::endl;
                    } else {
                        std::cout << "[ERRO] Falha ao atualizar pedido no banco." << std::endl;
                    }
                }
                delete pedido;
                break;
            }
            case 4: {
                std::cout << "\n--- MARCAR ITEM COMO ENTREGUE ---" << std::endl;
                int idPedido, idItem;
                std::cout << "Digite o ID do pedido: ";
                idPedido = lerInteiroSanitizado("");

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido ID " << idPedido << " nao encontrado." << std::endl;
                    break;
                }

                std::cout << "Digite o ID do item entregue a mesa: ";
                idItem = lerInteiroSanitizado("");

                ItemPedido* item = pedido->buscarItem(idItem);
                if (item == nullptr) {
                    std::cout << "[ERRO] Item ID " << idItem << " nao encontrado no pedido." << std::endl;
                } else if (item->getStatus() != StatusItemPedido::PRONTO) {
                    std::cout << "[AVISO] Apenas itens marcados como PRONTOS podem ser entregues a mesa." << std::endl;
                } else {
                    item->setStatus(StatusItemPedido::ENTREGUE);

                    // Se todos os itens foram entregues, atualiza status do pedido
                    bool todosEntregues = true;
                    for (const auto& i : pedido->getItens()) {
                        if (i.getStatus() != StatusItemPedido::ENTREGUE && 
                            i.getStatus() != StatusItemPedido::CANCELADO) {
                            todosEntregues = false;
                            break;
                        }
                    }
                    if (todosEntregues) {
                        pedido->alterarStatus(StatusPedido::ENTREGUE);
                    }

                    if (bancoDados.salvarPedido(*pedido)) {
                        std::cout << "[SUCESSO] Item '" << item->getProduto().getNome() 
                                  << "' entregue com sucesso a mesa!" << std::endl;
                    } else {
                        std::cout << "[ERRO] Falha ao atualizar pedido no banco." << std::endl;
                    }
                }
                delete pedido;
                break;
            }
            case 0:
                std::cout << "Retornando ao menu principal..." << std::endl;
                break;
            default:
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
                break;
        }
    }
}

void SistemaRestaurante::moduloCaixa() {
    if (!autenticacao.possuiPermissao(PerfilAcesso::CAIXA)) {
        std::cout << "\nAcesso negado. Modulo exclusivo para caixas ou administradores.\n" << std::endl;
        return;
    }

    int opcao = -1;
    while (opcao != 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "             MODULO DE CAIXA            " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Listar pedidos pendentes de pagamento" << std::endl;
        std::cout << "2. Consultar conta/extrato do pedido" << std::endl;
        std::cout << "3. Aplicar taxa de servico / desconto" << std::endl;
        std::cout << "4. Registrar pagamento" << std::endl;
        std::cout << "5. Fechar conta e liberar mesa" << std::endl;
        std::cout << "0. Voltar ao menu principal" << std::endl;
        std::cout << "Escolha uma opcao: ";

        opcao = lerInteiroSanitizado("");

        switch (opcao) {
            case 1: {
                std::vector<Pedido> pedidos = bancoDados.listarPedidos();
                std::cout << "\n--- PEDIDOS AGUARDANDO PAGAMENTO OU ABERTOS ---" << std::endl;
                bool encontrou = false;
                for (const auto& ped : pedidos) {
                    if (ped.getStatus() != StatusPedido::FINALIZANDO &&
                        ped.getStatus() != StatusPedido::CANCELADO) {
                        encontrou = true;
                        int mesaNum = (ped.getMesa() != nullptr) ? ped.getMesa()->getNumero() : -1;
                        std::cout << "Pedido #" << ped.getId()
                                  << " | Mesa: " << (mesaNum != -1 ? std::to_string(mesaNum) : "Balcao")
                                  << " | Total c/ taxa: R$ " << ped.calcularTotalComTaxa()
                                  << " | Pago: R$ " << ped.calcularTotalPago()
                                  << " | Restante: R$ " << ped.calcularSaldoRestante()
                                  << std::endl;
                    }
                }
                if (!encontrou) {
                    std::cout << "Nenhum pedido pendente no momento." << std::endl;
                }
                break;
            }
            case 2: {
                int idPedido;
                std::cout << "Digite o ID do pedido: ";
                idPedido = lerInteiroSanitizado("");

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido ID " << idPedido << " nao encontrado." << std::endl;
                    break;
                }

                std::cout << "\n========================================" << std::endl;
                std::cout << "       EXTRATO FINANCEIRO - PEDIDO #" << pedido->getId() << std::endl;
                std::cout << "========================================" << std::endl;
                if (pedido->getMesa() != nullptr) {
                    std::cout << "Mesa: " << pedido->getMesa()->getNumero() << std::endl;
                }
                std::cout << "Itens Consumidos:" << std::endl;
                for (const auto& item : pedido->getItens()) {
                    if (item.getStatus() != StatusItemPedido::CANCELADO) {
                        std::cout << "  - " << item.getProduto().getNome()
                                  << " x" << item.getQuantidade()
                                  << " (R$ " << item.getPrecoUnitario() << " un) = R$ "
                                  << item.calcularSubtotal() << std::endl;
                    }
                }
                std::cout << "----------------------------------------" << std::endl;
                std::cout << "Subtotal dos itens: R$ " << pedido->calcularTotalSemTaxa() << std::endl;
                std::cout << "Taxa de Servico:    R$ " << pedido->calcularTaxaServico() << std::endl;
                std::cout << "Total a pagar:      R$ " << pedido->calcularTotalComTaxa() << std::endl;
                std::cout << "Total ja pago:      R$ " << pedido->calcularTotalPago() << std::endl;
                std::cout << "Saldo restante:     R$ " << pedido->calcularSaldoRestante() << std::endl;

                if (!pedido->getPagamentos().empty()) {
                    std::cout << "\nPagamentos Realizados:" << std::endl;
                    for (const auto& pag : pedido->getPagamentos()) {
                        std::string formaStr;
                        switch (pag.getFormaPagamento()) {
                            case FormaPagamento::DINHEIRO: formaStr = "DINHEIRO"; break;
                            case FormaPagamento::CARTAO_CREDITO: formaStr = "CREDITO"; break;
                            case FormaPagamento::CARTAO_DEBITO: formaStr = "DEBITO"; break;
                            case FormaPagamento::PIX: formaStr = "PIX"; break;
                        }
                        std::cout << "  - Pagamento #" << pag.getId()
                                  << " | " << formaStr
                                  << " | R$ " << pag.getValor()
                                  << " | " << pag.getDataHoraPagamento() << std::endl;
                    }
                }
                std::cout << "========================================" << std::endl;

                delete pedido;
                break;
            }
            case 3: {
                int idPedido;
                std::cout << "Digite o ID do pedido: ";
                idPedido = lerInteiroSanitizado("");

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido ID " << idPedido << " nao encontrado." << std::endl;
                    break;
                }

                int escolha;
                std::cout << "1. Definir percentual de taxa de servico\n"
                          << "2. Conceder desconto em valor\n"
                          << "Escolha: ";
                escolha = lerInteiroSanitizado("");

                if (escolha == 1) {
                    double taxa;
                    std::cout << "Digite o percentual da taxa (ex: 10 para 10%): ";
                    taxa = lerDoubleSanitizado("");
                    pedido->setTaxaServicoPercentual(taxa);
                    std::cout << "[SUCESSO] Taxa de " << taxa << "% aplicada. Novo total: R$ "
                              << pedido->calcularTotalComTaxa() << std::endl;
                } else if (escolha == 2) {
                    double desc;
                    std::cout << "Digite o valor do desconto (R$): ";
                    desc = lerDoubleSanitizado("");
                    pedido->setDesconto(desc);
                    std::cout << "[SUCESSO] Desconto de R$ " << desc << " aplicado. Novo total: R$ "
                              << pedido->calcularTotalComTaxa() << std::endl;
                }

                bancoDados.salvarPedido(*pedido);
                delete pedido;
                break;
            }
            case 4: {
                int idPedido;
                std::cout << "Digite o ID do pedido a pagar: ";
                idPedido = lerInteiroSanitizado("");

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido ID " << idPedido << " nao encontrado." << std::endl;
                    break;
                }

                double saldo = pedido->calcularSaldoRestante();
                if (saldo <= 0.0) {
                    std::cout << "[AVISO] Este pedido ja foi totalmente quitado!" << std::endl;
                    delete pedido;
                    break;
                }

                std::cout << "\nSaldo restante a pagar: R$ " << saldo << std::endl;
                std::cout << "Escolha a forma de pagamento:\n"
                          << "0. DINHEIRO\n"
                          << "1. CARTAO CREDITO\n"
                          << "2. CARTAO DEBITO\n"
                          << "3. PIX\n"
                          << "Opcao: ";
                int opcForma;
                opcForma = lerInteiroSanitizado("");

                FormaPagamento forma;
                switch (opcForma) {
                    case 0: forma = FormaPagamento::DINHEIRO; break;
                    case 1: forma = FormaPagamento::CARTAO_CREDITO; break;
                    case 2: forma = FormaPagamento::CARTAO_DEBITO; break;
                    case 3: forma = FormaPagamento::PIX; break;
                    default:
                        std::cout << "[ERRO] Forma de pagamento invalida." << std::endl;
                        delete pedido;
                        continue;
                }

                double valorRecebido;
                std::cout << "Digite o valor a pagar (R$): ";
                valorRecebido = lerDoubleSanitizado("");

                if (valorRecebido <= 0.0) {
                    std::cout << "[ERRO] Valor invalido." << std::endl;
                    delete pedido;
                    break;
                }

                double valorGravado = (valorRecebido > saldo) ? saldo : valorRecebido;
                int pagId = static_cast<int>(pedido->getPagamentos().size()) + 1;
                Pagamento novoPagamento(pagId, forma, valorGravado);

                if (forma == FormaPagamento::DINHEIRO && valorRecebido > valorGravado) {
                    double troco = valorRecebido - valorGravado;
                    std::cout << ">>> TROCO A DEVOLVER: R$ " << troco << " <<<" << std::endl;
                }

                pedido->adicionarPagamento(novoPagamento);
                bancoDados.salvarPedido(*pedido);

                std::cout << "[SUCESSO] Pagamento registrado!" << std::endl;
                std::cout << "Novo saldo restante: R$ " << pedido->calcularSaldoRestante() << std::endl;

                delete pedido;
                break;
            }
            case 5: {
                int idPedido;
                std::cout << "Digite o ID do pedido para fechar e liberar a mesa: ";
                idPedido = lerInteiroSanitizado("");

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido ID " << idPedido << " nao encontrado." << std::endl;
                    break;
                }

                if (pedido->calcularSaldoRestante() > 0.0) {
                    std::cout << "[ERRO] O pedido ainda possui saldo pendente de R$ " 
                              << pedido->calcularSaldoRestante() << ". Quite a conta antes de fechar." << std::endl;
                    delete pedido;
                    break;
                }

                pedido->fecharPedido("2026-11-10 13:00:00");
                if (pedido->getMesa() != nullptr) {
                    pedido->getMesa()->setStatus(StatusMesa::LIVRE);
                    bancoDados.salvarMesa(*pedido->getMesa());
                }
                bancoDados.salvarPedido(*pedido);

                std::cout << "[SUCESSO] Pedido #" << idPedido << " encerrado com sucesso e mesa liberada!" << std::endl;
                delete pedido;
                break;
            }
            case 0:
                std::cout << "Retornando ao menu principal..." << std::endl;
                break;
            default:
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
                break;
        }
    }
}

void SistemaRestaurante::moduloRelatorios() {
    std::cout << "=== MODULO RELATORIOS ===" << std::endl;
    // Implementar funcionalidades do módulo de relatórios
}

void SistemaRestaurante::moduloCadastros() {
    if (!autenticacao.possuiPermissao(PerfilAcesso::ADMINISTRADOR)) {
        std::cout << "\nAcesso negado. Modulo exclusivo para administradores.\n" << std::endl;
        return;
    }

    int opcao = -1;
    while (opcao != 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "           MODULO DE CADASTROS          " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Cadastrar novo produto no cardapio" << std::endl;
        std::cout << "2. Listar produtos cadastrados" << std::endl;
        std::cout << "3. Alterar disponibilidade de um produto" << std::endl;
        std::cout << "4. Cadastrar nova mesa" << std::endl;
        std::cout << "5. Cadastrar novo usuario do sistema" << std::endl;
        std::cout << "0. Voltar ao menu principal" << std::endl;
        std::cout << "Escolha uma opcao: ";

        opcao = lerInteiroSanitizado("");

        switch (opcao) {
            case 1: {
                std::cout << "\n--- CADASTRAR PRODUTO ---" << std::endl;
                int id, preco, tempoPreparo;
                std::string nome;

                std::cout << "Digite o ID do produto: ";
                id = lerInteiroSanitizado("");

                Produto* existente = bancoDados.buscarProdutoPorId(id);
                if (existente != nullptr) {
                    std::cout << "[ERRO] Ja existe um produto com o ID " << id << "." << std::endl;
                    delete existente;
                    break;
                }

                nome = lerLinhaSanitizada("Digite o nome do produto: ");

                std::cout << "Digite o preco (inteiro em R$): ";
                preco = lerInteiroSanitizado("");
                if (preco < 0) {
                    std::cout << "[ERRO] Preco invalido." << std::endl;
                    break;
                }

                std::cout << "Digite o tempo estimado de preparo (em minutos): ";
                tempoPreparo = lerInteiroSanitizado("");
                if (tempoPreparo < 0) {
                    std::cout << "[ERRO] Tempo de preparo invalido." << std::endl;
                    break;
                }

                Produto novoProduto(id, nome, preco, true, tempoPreparo);
                if (bancoDados.salvarProduto(novoProduto)) {
                    std::cout << "[SUCESSO] Produto '" << nome << "' cadastrado com sucesso!" << std::endl;
                } else {
                    std::cout << "[ERRO] Falha ao salvar produto no banco de dados." << std::endl;
                }
                break;
            }
            case 2: {
                std::vector<Produto> produtos = bancoDados.listarProdutos();
                std::cout << "\n--- PRODUTOS CADASTRADOS ---" << std::endl;
                if (produtos.empty()) {
                    std::cout << "Nenhum produto cadastrado." << std::endl;
                } else {
                    for (const auto& prod : produtos) {
                        std::cout << "ID: " << prod.getId()
                                  << " | Nome: " << prod.getNome()
                                  << " | Preco: R$ " << prod.getPreco()
                                  << " | Tempo: " << prod.getTempoPreparo() << "min"
                                  << " | Status: " << (prod.getDisponivel() ? "[DISPONIVEL]" : "[INDISPONIVEL]")
                                  << std::endl;
                    }
                }
                break;
            }
            case 3: {
                int id;
                std::cout << "Digite o ID do produto para alternar disponibilidade: ";
                id = lerInteiroSanitizado("");

                Produto* prod = bancoDados.buscarProdutoPorId(id);
                if (prod == nullptr) {
                    std::cout << "[ERRO] Produto ID " << id << " nao encontrado." << std::endl;
                    break;
                }

                prod->setDisponivel(!prod->getDisponivel());
                if (bancoDados.salvarProduto(*prod)) {
                    std::cout << "[SUCESSO] Produto '" << prod->getNome() << "' agora esta "
                              << (prod->getDisponivel() ? "DISPONIVEL" : "INDISPONIVEL") << "!" << std::endl;
                } else {
                    std::cout << "[ERRO] Falha ao atualizar produto." << std::endl;
                }
                delete prod;
                break;
            }
            case 4: {
                std::cout << "\n--- CADASTRAR NOVA MESA ---" << std::endl;
                int idMesa, numeroMesa, capacidadeMesa;

                std::cout << "Digite o ID da nova mesa: ";
                idMesa = lerInteiroSanitizado("");

                Mesa* existente = bancoDados.buscarMesaPorId(idMesa);
                if (existente != nullptr) {
                    std::cout << "[ERRO] Ja existe uma mesa com o ID " << idMesa << "." << std::endl;
                    delete existente;
                    break;
                }

                std::cout << "Digite o numero da mesa: ";
                numeroMesa = lerInteiroSanitizado("");

                std::cout << "Digite a capacidade da mesa (lugares): ";
                capacidadeMesa = lerInteiroSanitizado("");
                if (capacidadeMesa <= 0) {
                    std::cout << "[ERRO] Capacidade invalida." << std::endl;
                    break;
                }

                Mesa novaMesa(idMesa, numeroMesa, capacidadeMesa, StatusMesa::LIVRE);
                if (bancoDados.salvarMesa(novaMesa)) {
                    std::cout << "[SUCESSO] Mesa " << numeroMesa << " cadastrada com sucesso!" << std::endl;
                } else {
                    std::cout << "[ERRO] Falha ao salvar mesa." << std::endl;
                }
                break;
            }
            case 5: {
                std::cout << "\n--- CADASTRAR NOVO USUARIO ---" << std::endl;
                int id, opcaoPerfil;
                std::string nome, login, senha;

                std::cout << "Digite o ID do usuario: ";
                id = lerInteiroSanitizado("");

                nome = lerLinhaSanitizada("Digite o nome completo: ");

                login = lerTextoSanitizado("Digite o login: ");

                Usuario* existente = bancoDados.buscarUsuarioPorLogin(login);
                if (existente != nullptr) {
                    std::cout << "[ERRO] Ja existe um usuario cadastrado com o login '" << login << "'." << std::endl;
                    delete existente;
                    break;
                }

                senha = lerTextoSanitizado("Digite a senha: ");

                std::cout << "Escolha o Perfil de Acesso:\n"
                          << "0. ADMINISTRADOR\n"
                          << "1. CAIXA\n"
                          << "2. GARCOM\n"
                          << "3. COZINHEIRO\n"
                          << "Perfil: ";
                opcaoPerfil = lerInteiroSanitizado("");

                PerfilAcesso perfil;
                switch (opcaoPerfil) {
                    case 0: perfil = PerfilAcesso::ADMINISTRADOR; break;
                    case 1: perfil = PerfilAcesso::CAIXA; break;
                    case 2: perfil = PerfilAcesso::GARCOM; break;
                    case 3: perfil = PerfilAcesso::COZINHEIRO; break;
                    default:
                        std::cout << "[AVISO] Opcao invalida. Definindo como GARCOM por padrao." << std::endl;
                        perfil = PerfilAcesso::GARCOM;
                        break;
                }

                std::hash<std::string> hasher;
                std::string senhaHash = std::to_string(hasher(senha));

                Usuario novoUsuario(id, nome, login, senhaHash, perfil);
                if (bancoDados.salvarUsuario(novoUsuario)) {
                    std::cout << "[SUCESSO] Usuario '" << login << "' cadastrado com sucesso!" << std::endl;
                } else {
                    std::cout << "[ERRO] Falha ao salvar usuario no banco de dados." << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Retornando ao menu principal..." << std::endl;
                break;
            default:
                std::cout << "Opcao invalida. Tente novamente." << std::endl;
                break;
        }
    }
}
