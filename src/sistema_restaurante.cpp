#include "../documentation/sistema_restaurante.hpp"
#include <iostream>

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
    if (!autenticacao.estaLogado()) {
        exibirTelaLogin();
    } else {
        exibirTelaPrincipal();
    }
}

void SistemaRestaurante::exibirTelaLogin() {
    std::string login, senha;
    std::cout << "=== TELA DE LOGIN ===" << std::endl;
    std::cout << "Login: ";
    std::cin >> login;
    std::cout << "Senha: ";
    std::cin >> senha;
    if (autenticacao.login(login, senha)) {
        std::cout << "Login bem-sucedido!" << std::endl;
        exibirTelaPrincipal();
    } else {
        std::cout << "Falha no login. Tente novamente." << std::endl;
        exibirTelaLogin();
    }
}

void SistemaRestaurante::exibirTelaPrincipal() {
    std::cout << "=== TELA PRINCIPAL ===" << std::endl;
    std::cout << "1. Modulo Mesas" << std::endl;
    std::cout << "2. Modulo Pedidos" << std::endl;
    std::cout << "3. Modulo Cozinha" << std::endl;
    std::cout << "4. Modulo Caixa" << std::endl;
    std::cout << "5. Modulo Relatorios" << std::endl;
    std::cout << "6. Modulo Cadastros" << std::endl;
    std::cout << "7. Logout" << std::endl;
    std::cout << "0. Sair" << std::endl;

    int opcao;
    std::cout << "Escolha uma opcao: ";
    std::cin >> opcao;

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
        
        if (!(std::cin >> opcao)) {
            std::cin.clear();
            std::string descarte;
            std::cin >> descarte;
            std::cout << "Entrada invalida. Digite um numero." << std::endl;
            continue;
        }

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
                std::cin >> idMesa;

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
                std::cin >> idMesa;

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
                std::cin >> idMesa;

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
                if (!(std::cin >> idMesa)) {
                    std::cin.clear();
                    std::string d;
                    std::cin >> d;
                    std::cout << "[ERRO] ID invalido." << std::endl;
                    break;
                }

                // Verifica se o ID ja existe
                Mesa* existente = bancoDados.buscarMesaPorId(idMesa);
                if (existente != nullptr) {
                    std::cout << "[ERRO] Ja existe uma mesa com o ID " << idMesa << "." << std::endl;
                    delete existente;
                    break;
                }

                std::cout << "Digite o numero da mesa: ";
                if (!(std::cin >> numeroMesa)) {
                    std::cin.clear();
                    std::string d;
                    std::cin >> d;
                    std::cout << "[ERRO] Numero invalido." << std::endl;
                    break;
                }

                std::cout << "Digite a capacidade da mesa (lugares): ";
                if (!(std::cin >> capacidadeMesa) || capacidadeMesa <= 0) {
                    std::cin.clear();
                    std::string d;
                    std::cin >> d;
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

        if (!(std::cin >> opcao)) {
            std::cin.clear();
            std::string d;
            std::cin >> d;
            std::cout << "Entrada invalida. Digite um numero." << std::endl;
            continue;
        }

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
                if (!(std::cin >> idPedido)) {
                    std::cin.clear();
                    std::string d;
                    std::cin >> d;
                    std::cout << "[ERRO] ID invalido." << std::endl;
                    break;
                }

                Pedido* existente = bancoDados.buscarPedidoPorId(idPedido);
                if (existente != nullptr) {
                    std::cout << "[ERRO] Ja existe um pedido com o ID " << idPedido << "." << std::endl;
                    delete existente;
                    break;
                }

                std::cout << "Digite o ID da mesa: ";
                if (!(std::cin >> idMesa)) {
                    std::cin.clear();
                    std::string d;
                    std::cin >> d;
                    std::cout << "[ERRO] ID de mesa invalido." << std::endl;
                    break;
                }

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
                std::cin >> idPedido;

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
                std::cin >> idProduto;

                Produto* produtoEscolhido = bancoDados.buscarProdutoPorId(idProduto);
                if (produtoEscolhido == nullptr) {
                    std::cout << "[ERRO] Produto nao encontrado." << std::endl;
                    delete pedido;
                    break;
                }

                std::cout << "Digite a quantidade: ";
                if (!(std::cin >> quantidade) || quantidade <= 0) {
                    std::cout << "[ERRO] Quantidade deve ser maior que 0." << std::endl;
                    delete produtoEscolhido;
                    delete pedido;
                    break;
                }

                std::cin.ignore();
                std::string obs;
                std::cout << "Observacoes (ex: sem cebola) [Pressione ENTER para nenhuma]: ";
                std::getline(std::cin, obs);

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
                std::cin >> idPedido;

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
                std::cin >> idPedido;

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido nao encontrado." << std::endl;
                    break;
                }

                std::cout << "Digite o ID do item a cancelar: ";
                std::cin >> idItem;

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
                std::cin >> idPedido;

                Pedido* pedido = bancoDados.buscarPedidoPorId(idPedido);
                if (pedido == nullptr) {
                    std::cout << "[ERRO] Pedido nao encontrado." << std::endl;
                    break;
                }

                char confirma;
                std::cout << "Tem certeza que deseja cancelar o pedido #" << idPedido << "? (s/n): ";
                std::cin >> confirma;

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
    std::cout << "=== MODULO COZINHA ===" << std::endl;
    // Implementar funcionalidades do módulo de cozinha
}

void SistemaRestaurante::moduloCaixa() {
    std::cout << "=== MODULO CAIXA ===" << std::endl;
    // Implementar funcionalidades do módulo de caixa
}

void SistemaRestaurante::moduloRelatorios() {
    std::cout << "=== MODULO RELATORIOS ===" << std::endl;
    // Implementar funcionalidades do módulo de relatórios
}

void SistemaRestaurante::moduloCadastros() {
    std::cout << "=== MODULO CADASTROS ===" << std::endl;
    // Implementar funcionalidades do módulo de cadastros
}
