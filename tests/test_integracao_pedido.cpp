#include "../documentation/doctest.h"
#include "../documentation/pedido.hpp"
#include "../documentation/mesa.hpp"
#include "../documentation/produto.hpp"
#include "../documentation/item_pedido.hpp"
#include "../documentation/cliente.hpp"
#include "../documentation/usuario.hpp"
#include "../documentation/pagamento.hpp"

TEST_CASE("Integracao - Ciclo de Vida do Pedido (Itens, Taxa, Pagamento e Fechamento)") {
    // 1. Setup dos objetos colaboradores
    Mesa mesa(1, 10, 4, StatusMesa::LIVRE);
    mesa.setStatus(StatusMesa::OCUPADA);

    Garcom garcom(100, "Carlos", "carlos_garcom", "senha123");
    Cliente cliente(50, "Joao Silva", "11999998888");

    Pedido pedido(1, "2026-11-11 10:00:00", &garcom, &mesa, &cliente);

    CHECK(pedido.getId() == 1);
    CHECK(pedido.getStatus() == StatusPedido::ABERTO);
    CHECK(pedido.getMesa()->getNumero() == 10);
    CHECK(pedido.getAtendente()->getNome() == "Carlos");
    CHECK(pedido.getCliente()->getNome() == "Joao Silva");

    // 2. Adicionar itens de produtos ao pedido
    Produto p1(1, "Parmegiana", 4500, true, 25);
    Produto p2(2, "Refrigerante", 700, true, 2);

    ItemPedido item1(1, p1, 2, 45.0); // 2 x 45 = 90.0
    ItemPedido item2(2, p2, 2, 7.0);  // 2 x 7  = 14.0

    pedido.adicionarItem(item1);
    pedido.adicionarItem(item2);

    CHECK(pedido.getItens().size() == 2);
    CHECK(pedido.calcularTotalSemTaxa() == doctest::Approx(104.0));

    // 3. Aplicacao de taxa de servico (10%)
    pedido.setTaxaServicoPercentual(10.0);
    CHECK(pedido.calcularTaxaServico() == doctest::Approx(10.4));
    CHECK(pedido.calcularTotalComTaxa() == doctest::Approx(114.4));

    // 4. Fluxo de pagamento parcial e saldo restante
    Pagamento pag1(1, FormaPagamento::DINHEIRO, 50.0);
    pedido.adicionarPagamento(pag1);

    CHECK(pedido.calcularTotalPago() == doctest::Approx(50.0));
    CHECK(pedido.calcularSaldoRestante() == doctest::Approx(64.4));
    CHECK(pedido.podeSerFechado() == false);

    // Quitando o restante do saldo
    Pagamento pag2(2, FormaPagamento::PIX, 64.4);
    pedido.adicionarPagamento(pag2);

    // Simula a cozinha preparando e entregando os itens
    for (auto& item : const_cast<std::vector<ItemPedido>&>(pedido.getItens())) {
        item.setStatus(StatusItemPedido::ENTREGUE);
    }

    CHECK(pedido.calcularTotalPago() == doctest::Approx(114.4));
    CHECK(pedido.calcularSaldoRestante() == doctest::Approx(0.0));
    CHECK(pedido.podeSerFechado() == true);

    // 5. Fechamento do pedido e liberacao da mesa
    pedido.fecharPedido("2026-11-11 11:15:00");
    CHECK(pedido.getStatus() == StatusPedido::ENTREGUE);
    CHECK(mesa.getStatus() == StatusMesa::LIVRE);
}

TEST_CASE("Integracao - Cancelamento de Pedido e Itens") {
    Mesa mesa(2, 5, 2, StatusMesa::OCUPADA);
    Garcom garcom(101, "Lucas", "lucas_garcom", "senha123");
    Pedido pedido(2, "2026-11-11 10:30:00", &garcom, &mesa);

    Produto p(3, "Porcao Fritas", 2000, true, 10);
    ItemPedido item(1, p, 1, 20.0);
    pedido.adicionarItem(item);

    CHECK(pedido.getItens().size() == 1);
    pedido.removerItem(1);
    CHECK(pedido.getItens().empty());

    pedido.cancelar();
    CHECK(pedido.getStatus() == StatusPedido::CANCELADO);
}
