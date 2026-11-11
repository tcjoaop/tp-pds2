#include "../documentation/doctest.h"
#include "../documentation/produto.hpp"
#include "../documentation/categoria.hpp"

TEST_CASE("Modelo Categoria - Criacao e Modificacao") {
    Categoria cat(1, "Bebidas", "Sucos e refrigerantes");
    CHECK(cat.getId() == 1);
    CHECK(cat.getNome() == "Bebidas");
    CHECK(cat.getDescricao() == "Sucos e refrigerantes");

    cat.setNome("Bebidas Geladas");
    cat.setDescricao("Sucos naturais e refrigerantes");
    cat.setId(10);

    CHECK(cat.getId() == 10);
    CHECK(cat.getNome() == "Bebidas Geladas");
    CHECK(cat.getDescricao() == "Sucos naturais e refrigerantes");
}

TEST_CASE("Modelo Produto - Criacao e Getters") {
    Produto prod(101, "Suco de Laranja", 850, true, 5); // preco 850 centavos (ou 8.50)
    CHECK(prod.getId() == 101);
    CHECK(prod.getNome() == "Suco de Laranja");
    CHECK(prod.getPreco() == 850);
    CHECK(prod.getDisponivel() == true);
    CHECK(prod.getTempoPreparo() == 5);
}

TEST_CASE("Modelo Produto - Setters e Atualizacoes") {
    Produto prod(102, "Prato do Dia", 2500, true, 20);

    prod.setNome("Prato Executivo");
    prod.setPreco(2800);
    prod.setDisponivel(false);
    prod.setTempoPreparo(25);

    CHECK(prod.getNome() == "Prato Executivo");
    CHECK(prod.getPreco() == 2800);
    CHECK(prod.getDisponivel() == false);
    CHECK(prod.getTempoPreparo() == 25);
}
