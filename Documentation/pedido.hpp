#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <string>
#include <vector>
#include "tipos.hpp"
#include "item_pedido.hpp"
#include "mesa.hpp"
#include "usuario.hpp"
#include "cliente.hpp"
#include "pagamento.hpp"

class Pedido {

private:
    int id;
    std::string dataHoraAbertura;
    std::string dataHoraFechamento;
    StatusPedido status;

    Mesa* mesa;
    Usuario* atendente;
    Cliente* cliente;

    std::vector<ItemPedido> itens;
    std::vector<Pagamento> pagamentos;

    double taxaServicoPercentual;
    double desconto;

public:
    Pedido(int id,
          const std::string& dataHoraAbertura,
          Usuario* atendente = nullptr,
          Mesa* mesa = nullptr,
          Cliente* cliente = nullptr);
    ~Pedido();

    int getId() const;
    StatusPedido getStatus() const;
    Mesa* getMesa() const;
    Usuario* getAtendente() const;
    Cliente* getCliente() const;
    const std::vector<ItemPedido>& getItens() const;
    const std::vector<Pagamento>& getPagamentos() const;

    void adicionarItem(const ItemPedido& item);
    void removerItem(int itemId);
    ItemPedido* buscarItem(int itemId);

    double calcularTotalSemTaxa() const;
    double calcularTaxaServico() const;
    double calcularTotalComTaxa() const;
    double calcularTotalPago() const;
    double calcularSaldoRestante() const;

    void setTaxaServicoPercentual(double taxa);
    void setDesconto(double desconto);

    void adicionarPagamento(const Pagamento& pagamento);

    void alterarStatus(StatusPedido novoStatus);
    void fecharPedido(const std::string& dataHoraFechamento);
    void cancelar();

    bool podeSerFechado() const;

};

#endif