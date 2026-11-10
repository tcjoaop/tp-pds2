#include "../documentation/sistema_restaurante.hpp"
#include <iostream>

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
    std::cout << "=== MODULO MESAS ===" << std::endl;
    // Implementar funcionalidades do módulo de mesas
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
