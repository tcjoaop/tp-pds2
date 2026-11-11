#include "../documentation/doctest.h"
#include "../documentation/mesa.hpp"
#include "../documentation/produto.hpp"
#include "../documentation/cliente.hpp"
#include "../documentation/item_pedido.hpp"
#include "../documentation/pedido.hpp"
#include "../documentation/pagamento.hpp"
#include <stdexcept>

TEST_CASE("Excecoes - Mesa com parametros invalidos") {
    // ID negativo
    CHECK_THROWS_AS(Mesa(-1, 5, 4, StatusMesa::LIVRE), std::invalid_argument);
    // Numero de mesa invalido
    CHECK_THROWS_AS(Mesa(1, 0, 4, StatusMesa::LIVRE), std::invalid_argument);
    // Capacidade invalida
    CHECK_THROWS_AS(Mesa(1, 5, 0, StatusMesa::LIVRE), std::invalid_argument);

    Mesa m(1, 5, 4, StatusMesa::LIVRE);
    CHECK_THROWS_AS(m.setCapacidade(-2), std::invalid_argument);
    CHECK_THROWS_AS(m.setNumero(0), std::invalid_argument);

    // Ocupar mesa ja ocupada dispara excecao de runtime
    m.ocupar(m);
    CHECK_THROWS_AS(m.ocupar(m), std::runtime_error);
}

TEST_CASE("Excecoes - Produto com parametros invalidos") {
    // ID <= 0
    CHECK_THROWS_AS(Produto(0, "Pizza", 3000, true, 15), std::invalid_argument);
    // Nome vazio
    CHECK_THROWS_AS(Produto(1, "", 3000, true, 15), std::invalid_argument);
    // Preco negativo
    CHECK_THROWS_AS(Produto(1, "Pizza", -500, true, 15), std::invalid_argument);
    // Tempo de preparo negativo
    CHECK_THROWS_AS(Produto(1, "Pizza", 3000, true, -1), std::invalid_argument);

    Produto p(1, "Pizza", 3000, true, 15);
    CHECK_THROWS_AS(p.setNome(""), std::invalid_argument);
    CHECK_THROWS_AS(p.setPreco(-10), std::invalid_argument);
    CHECK_THROWS_AS(p.setTempoPreparo(-5), std::invalid_argument);
}

TEST_CASE("Excecoes - Cliente com parametros invalidos") {
    // ID <= 0
    CHECK_THROWS_AS(Cliente(-5, "Lucas", "99999"), std::invalid_argument);
    // Nome vazio
    CHECK_THROWS_AS(Cliente(1, "", "99999"), std::invalid_argument);

    Cliente c(1, "Lucas", "99999");
    CHECK_THROWS_AS(c.setNome(""), std::invalid_argument);
}

TEST_CASE("Excecoes - ItemPedido e Pagamento com parametros invalidos") {
    Produto prod(1, "Refrigerante", 500, true, 2);

    // Quantidade <= 0
    CHECK_THROWS_AS(ItemPedido(1, prod, 0, 5.0), std::invalid_argument);
    CHECK_THROWS_AS(ItemPedido(1, prod, -3, 5.0), std::invalid_argument);
    // Preco unitario negativo
    CHECK_THROWS_AS(ItemPedido(1, prod, 2, -1.0), std::invalid_argument);

    ItemPedido item(1, prod, 1, 5.0);
    CHECK_THROWS_AS(item.setQuantidade(0), std::invalid_argument);
    CHECK_THROWS_AS(item.setQuantidade(-5), std::invalid_argument);

    // Pagamento com valor <= 0
    CHECK_THROWS_AS(Pagamento(1, FormaPagamento::DINHEIRO, 0.0), std::invalid_argument);
    CHECK_THROWS_AS(Pagamento(1, FormaPagamento::PIX, -20.0), std::invalid_argument);

    Pagamento pag(1, FormaPagamento::CARTAO_CREDITO, 50.0);
    CHECK_THROWS_AS(pag.setValor(0.0), std::invalid_argument);
}

TEST_CASE("Excecoes - Pedido com taxas ou descontos invalidos") {
    Pedido ped(1, "2026-11-11 12:00:00");

    CHECK_THROWS_AS(ped.setTaxaServicoPercentual(-5.0), std::invalid_argument);
    CHECK_THROWS_AS(ped.setDesconto(-10.0), std::invalid_argument);
}
