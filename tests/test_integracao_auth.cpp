#include "../documentation/doctest.h"
#include "../documentation/autenticacao.hpp"
#include "../documentation/banco_dados.hpp"
#include "../documentation/usuario.hpp"
#include "../documentation/tipos.hpp"
#include <fstream>

TEST_CASE("Integracao - Autenticacao com Banco de Dados e Permissoes Polimorficas") {
    std::string arquivoTeste = "banco_teste_integracao.json";
    
    // Hash std::hash<std::string> para a senha "123"
    std::string hash123 = std::to_string(std::hash<std::string>{}("123"));

    // Inicializa JSON com usuarios de diferentes cargos
    {
        std::ofstream out(arquivoTeste);
        out << "{\n"
            << "  \"categorias\": [],\n"
            << "  \"produtos\": [],\n"
            << "  \"mesas\": [],\n"
            << "  \"clientes\": [],\n"
            << "  \"pedidos\": [],\n"
            << "  \"usuarios\": [\n"
            << "    {\n"
            << "      \"id\": 1,\n"
            << "      \"nome\": \"Admin Sistema\",\n"
            << "      \"login\": \"admin_test\",\n"
            << "      \"senha\": \"" << hash123 << "\",\n"
            << "      \"perfil\": 0\n"
            << "    },\n"
            << "    {\n"
            << "      \"id\": 2,\n"
            << "      \"nome\": \"Garcom Teste\",\n"
            << "      \"login\": \"garcom_test\",\n"
            << "      \"senha\": \"" << hash123 << "\",\n"
            << "      \"perfil\": 2\n"
            << "    }\n"
            << "  ]\n"
            << "}";
    }

    BancoDados bd(arquivoTeste);
    Autenticacao auth(bd);

    // 1. Antes do login
    CHECK(auth.estaLogado() == false);
    CHECK(auth.possuiPermissao(PerfilAcesso::GARCOM) == false);

    // 2. Login com senha errada
    CHECK(auth.login("admin_test", "senha_incorreta") == false);
    CHECK(auth.estaLogado() == false);

    // 3. Login com sucesso de Administrador (acesso irrestrito)
    CHECK(auth.login("admin_test", "123") == true);
    CHECK(auth.estaLogado() == true);
    CHECK(auth.getUsuarioLogado()->getNome() == "Admin Sistema");
    CHECK(auth.possuiPermissao(PerfilAcesso::ADMINISTRADOR) == true);
    CHECK(auth.possuiPermissao(PerfilAcesso::GARCOM) == true);
    CHECK(auth.possuiPermissao(PerfilAcesso::COZINHEIRO) == true);
    CHECK(auth.possuiPermissao(PerfilAcesso::CAIXA) == true);

    // Logout
    auth.logout();
    CHECK(auth.estaLogado() == false);

    // 4. Login com Garcom (acesso restrito apenas ao modulo de Garcom)
    CHECK(auth.login("garcom_test", "123") == true);
    CHECK(auth.estaLogado() == true);
    CHECK(auth.possuiPermissao(PerfilAcesso::GARCOM) == true);
    CHECK(auth.possuiPermissao(PerfilAcesso::ADMINISTRADOR) == false);
    CHECK(auth.possuiPermissao(PerfilAcesso::CAIXA) == false);

    auth.logout();

    // Limpeza
    std::remove(arquivoTeste.c_str());
}
