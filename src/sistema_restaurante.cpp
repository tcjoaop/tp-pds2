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
    std::cout << "=== MODULO PEDIDOS ===" << std::endl;
    // Implementar funcionalidades do módulo de pedidos
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
