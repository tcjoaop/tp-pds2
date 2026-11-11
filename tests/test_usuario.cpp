#include "../documentation/doctest.h"
#include "../documentation/usuario.hpp"
#include "../documentation/tipos.hpp"

TEST_CASE("Heranca e Polimorfismo - Usuario Administrador") {
    Usuario* admin = new Administrador(1, "Carlos Admin", "admin", "hash123");

    CHECK(admin->getId() == 1);
    CHECK(admin->getNome() == "Carlos Admin");
    CHECK(admin->getPerfil() == PerfilAcesso::ADMINISTRADOR);
    
    // Polimorfismo: Administrador tem acesso a todos os modulos
    CHECK(admin->podeAcessar(PerfilAcesso::ADMINISTRADOR) == true);
    CHECK(admin->podeAcessar(PerfilAcesso::GARCOM) == true);
    CHECK(admin->podeAcessar(PerfilAcesso::COZINHEIRO) == true);
    CHECK(admin->podeAcessar(PerfilAcesso::CAIXA) == true);

    delete admin;
}

TEST_CASE("Heranca e Polimorfismo - Usuario Garcom") {
    Usuario* garcom = new Garcom(2, "Joao Garcom", "garcom1", "hash123");

    CHECK(garcom->getPerfil() == PerfilAcesso::GARCOM);

    // Polimorfismo: Garcom so acessa modulo de garcom
    CHECK(garcom->podeAcessar(PerfilAcesso::GARCOM) == true);
    CHECK(garcom->podeAcessar(PerfilAcesso::ADMINISTRADOR) == false);
    CHECK(garcom->podeAcessar(PerfilAcesso::COZINHEIRO) == false);
    CHECK(garcom->podeAcessar(PerfilAcesso::CAIXA) == false);

    delete garcom;
}

TEST_CASE("Heranca e Polimorfismo - Usuario Cozinheiro") {
    Usuario* cozinheiro = new Cozinheiro(3, "Maria Cozinha", "chefe1", "hash123");

    CHECK(cozinheiro->getPerfil() == PerfilAcesso::COZINHEIRO);

    // Polimorfismo: Cozinheiro so acessa modulo da cozinha
    CHECK(cozinheiro->podeAcessar(PerfilAcesso::COZINHEIRO) == true);
    CHECK(cozinheiro->podeAcessar(PerfilAcesso::GARCOM) == false);
    CHECK(cozinheiro->podeAcessar(PerfilAcesso::CAIXA) == false);

    delete cozinheiro;
}

TEST_CASE("Heranca e Polimorfismo - Usuario Caixa") {
    Usuario* caixa = new Caixa(4, "Ana Caixa", "caixa1", "hash123");

    CHECK(caixa->getPerfil() == PerfilAcesso::CAIXA);

    // Polimorfismo: Caixa so acessa modulo do caixa
    CHECK(caixa->podeAcessar(PerfilAcesso::CAIXA) == true);
    CHECK(caixa->podeAcessar(PerfilAcesso::GARCOM) == false);
    CHECK(caixa->podeAcessar(PerfilAcesso::ADMINISTRADOR) == false);

    delete caixa;
}
