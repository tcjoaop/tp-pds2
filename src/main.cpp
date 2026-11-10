#include <iostream>
#include <vector>
#include <string>
#include "../documentation/banco_dados.hpp"
#include "../documentation/autenticacao.hpp"
#include "../documentation/usuario.hpp"
#include "../documentation/perfil.hpp"

int main() {
    std::cout << "=== TESTE DE BANCO DE DADOS E AUTENTICACAO ===" << std::endl;
    // 1. Inicializa o banco de dados
    BancoDados bd("banco_teste.json");
    bd.criarEstruturaInicial();
    // 2. Cria um usuário de teste (caso ainda não exista)
    // OBS: Como sua Autenticacao usa hash simples, geramos o hash da senha "admin123"
    std::hash<std::string> hasher;
    std::string senhaHash = std::to_string(hasher("admin123"));
    std::vector<std::string> permissoes = {"ADMIN", "GERENTE", "CAIXA"};
    Perfil perfilAdmin(1, "Administrador", permissoes);
    Usuario usuarioAdmin(1, "Joao Administrador", "admin", senhaHash, perfilAdmin);
    // Salva o usuário no banco JSON
    if (bd.salvarUsuario(usuarioAdmin)) {
        std::cout << "[OK] Usuario 'admin' salvo com sucesso no banco!" << std::endl;
    } else {
        std::cout << "[ERRO] Falha ao salvar usuario no banco." << std::endl;
    }
    // 3. Inicializa o módulo de Autenticação
    Autenticacao auth(bd);
    // 4. Teste interativo de login
    std::string loginInput, senhaInput;
    std::cout << "\n--- TELA DE LOGIN ---" << std::endl;
    std::cout << "Digite o login: ";
    std::cin >> loginInput;
    std::cout << "Digite a senha: ";
    std::cin >> senhaInput;
    if (auth.login(loginInput, senhaInput)) {
        std::cout << "\n>>> Login realizado com sucesso!" << std::endl;
        std::cout << "Bem-vindo, " << auth.getUsuarioLogado()->getNome() << "!" << std::endl;
        // Testando verificação de permissões
        if (auth.possuiPermissao("ADMIN")) {
            std::cout << "[Permissao] Usuario possui acesso de ADMIN." << std::endl;
        }
        // Testando logout
        auth.logout();
        std::cout << "Logout realizado. Esta logado? " 
                  << (auth.estaLogado() ? "Sim" : "Nao") << std::endl;
    } else {
        std::cout << "\n>>> Falha no login: credenciais invalidas." << std::endl;
    }
    return 0;
}