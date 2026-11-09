#include "../documentation/pedido.hpp"

Pedido::Pedido(int id,
          const std::string& dataHoraAbertura,
          Mesa* mesa,
          Usuario* atendente,
          Cliente* cliente) : id(id), dataHoraAbertura(dataHoraAbertura), status(StatusPedido::ABERTO), mesa(mesa), atendente(atendente), cliente(cliente), taxaServicoPercentual(0.0), desconto(0.0) {}
Pedido::~Pedido() {}

int Pedido::getId() const {
    return id;
}

StatusPedido Pedido::getStatus() const {
    return status;
}

Mesa* Pedido::getMesa() const {
    return mesa;
}

Usuario* Pedido::getAtendente() const {
    return atendente;
}

Cliente* Pedido::getCliente() const {
    return cliente;
}

const std::vector<ItemPedido>& Pedido::getItens() const {
    return itens;
}

const std::vector<Pagamento>& Pedido::getPagamentos() const {
    return pagamentos;
}

void Pedido::adicionarItem(const ItemPedido& item) {
    itens.push_back(item);
}

void Pedido::removerItem(int itemId) {
    for (int i = 0; i < itens.size(); ++i) {
        if (itens[i].getId() == itemId) {
            itens.erase(itens.begin() + i);
            return;
        }
    }
    std::cout << "Item de ID" << itemId << " não encontrado no pedido." << std::endl;
}

ItemPedido* Pedido::buscarItem(int itemId) {
    for (int i = 0; i < itens.size(); ++i) {
        if (itens[i].getId() == itemId) {
            return &itens[i];
        }
    }
    return nullptr;
}

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
