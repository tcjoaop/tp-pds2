#include "../documentation/doctest.h"
#include "../documentation/cliente.hpp"

//exemplo de teste unitário usando a biblioteca doctest

TEST_CASE("Testando o cadastro de Cliente") {
    Cliente c(1, "João", "12345678900");

    CHECK(c.getId() == 1);
    CHECK(c.getNome() == "João");
    CHECK(c.getTelefone() == "12345678900");
}

TEST_CASE("Testando validações ou exceções") {
    //aqui é pra testar exceções ou validações, mas como a classe Cliente não tem validações ainda, não há nada a testar
}