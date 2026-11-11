#include "../documentation/doctest.h"
#include "../documentation/item_pedido.hpp"
#include "../documentation/produto.hpp"
#include "../documentation/tipos.hpp"

TEST_CASE("Modelo ItemPedido - Criacao e Calculo de Subtotal") {
    Produto prod(1, "Hamburguer Artesanal", 3000, true, 15);
    ItemPedido item(1, prod, 2, 30.0, "Sem cebola");

    CHECK(item.getId() == 1);
    CHECK(item.getQuantidade() == 2);
    CHECK(item.getPrecoUnitario() == doctest::Approx(30.0));
    CHECK(item.getObservacoes() == "Sem cebola");
    CHECK(item.getStatus() == StatusItemPedido::PENDENTE);
    CHECK(item.calcularSubtotal() == doctest::Approx(60.0));
}

TEST_CASE("Modelo ItemPedido - Alteracoes de Quantidade e Observacoes") {
    Produto prod(2, "Refrigerante Lata", 600, true, 2);
    ItemPedido item(2, prod, 1, 6.0);

    item.setQuantidade(3);
    item.setObservacoes("Com gelo e limao");

    CHECK(item.getQuantidade() == 3);
    CHECK(item.getObservacoes() == "Com gelo e limao");
    CHECK(item.calcularSubtotal() == doctest::Approx(18.0));
}

TEST_CASE("Modelo ItemPedido - Regra de Cancelamento por Status") {
    Produto prod(3, "Pizza Especial", 5000, true, 25);
    ItemPedido item(3, prod, 1, 50.0);

    // No estado PENDENTE pode ser cancelado
    CHECK(item.podeSerCancelado() == true);

    // Quando vai para a cozinha ainda pode ou nao dependendo da regra
    item.setStatus(StatusItemPedido::ENVIADO_COZINHA);
    CHECK(item.podeSerCancelado() == true);

    // Quando entra em preparo ou entregue, nao pode ser cancelado
    item.setStatus(StatusItemPedido::EM_PREPARO);
    CHECK(item.podeSerCancelado() == false);

    item.setStatus(StatusItemPedido::PRONTO);
    CHECK(item.podeSerCancelado() == false);

    item.setStatus(StatusItemPedido::ENTREGUE);
    CHECK(item.podeSerCancelado() == false);
}

TEST_CASE("Modelo ItemPedido - Construtor de Copia e Operador de Atribuicao") {
    Produto prod(4, "Sobremesa Pudim", 1200, true, 5);
    ItemPedido original(4, prod, 2, 12.0, "Extra calda");

    ItemPedido copia = original;
    CHECK(copia.getId() == original.getId());
    CHECK(copia.calcularSubtotal() == doctest::Approx(24.0));
    CHECK(copia.getObservacoes() == "Extra calda");

    ItemPedido outro(5, prod, 1, 10.0);
    outro = original;
    CHECK(outro.getObservacoes() == "Extra calda");
    CHECK(outro.getQuantidade() == 2);
}
