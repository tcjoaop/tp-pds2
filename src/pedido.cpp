#include "../documentation/pedido.hpp"
#include <iostream>
#include <stdexcept>

Pedido::Pedido(int id,
          const std::string& dataHoraAbertura,
          Usuario* atendente,
          Mesa* mesa,
          Cliente* cliente) {
    if (id <= 0) {
        throw std::invalid_argument("ID do pedido deve ser positivo.");
    }
    this->id = id;
    this->dataHoraAbertura = dataHoraAbertura;
    this->status = StatusPedido::ABERTO;
    this->mesa = mesa;
    this->atendente = atendente;
    this->cliente = cliente;
    this->taxaServicoPercentual = 0.0;
    this->desconto = 0.0;
}
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

double Pedido::calcularTotalSemTaxa() const{
    double total = 0.0;
    for (int i = 0; i < itens.size(); ++i) {
        if (itens[i].getStatus() != StatusItemPedido::CANCELADO) {
        total += itens[i].calcularSubtotal();
        }
    }
    return total;
}

double Pedido::calcularTaxaServico() const{
    return calcularTotalSemTaxa() * (taxaServicoPercentual / 100.0);
}

double Pedido::calcularTotalComTaxa() const{
    return calcularTotalSemTaxa() + calcularTaxaServico() - desconto;
}

double Pedido::calcularTotalPago() const{
    double total = 0.0;
    for (int i = 0; i < pagamentos.size(); ++i) {
        total += pagamentos[i].getValor();
    }
    return total;
}

double Pedido::calcularSaldoRestante() const{
    return calcularTotalComTaxa() - calcularTotalPago();
}

void Pedido::setTaxaServicoPercentual(double taxa){
    if (taxa < 0.0) {
        throw std::invalid_argument("Taxa de servico nao pode ser negativa.");
    }
    this->taxaServicoPercentual = taxa;
}

void Pedido::setDesconto(double desconto){
    if (desconto < 0.0) {
        throw std::invalid_argument("Desconto nao pode ser negativo.");
    }
    this->desconto = desconto;
}

void Pedido::adicionarPagamento(const Pagamento& pagamento){
    pagamentos.push_back(pagamento);
    if(calcularSaldoRestante() <= 0.0) {
        alterarStatus(StatusPedido::FINALIZANDO);
    }
}

void Pedido::alterarStatus(StatusPedido novoStatus){
    status = novoStatus;
}

void Pedido::fecharPedido(const std::string& dataHoraFechamento){
    if(podeSerFechado()){
        this->dataHoraFechamento = dataHoraFechamento;
        alterarStatus(StatusPedido::ENTREGUE);
        if(mesa != nullptr) {
            mesa->setStatus(StatusMesa::LIVRE);
        }
    } else {
        std::cout << "O pedido não pode ser fechado. Status atual: " << static_cast<int>(status) << std::endl;
    }
}

void Pedido::cancelar(){
    alterarStatus(StatusPedido::CANCELADO);
    if(mesa != nullptr) {
        mesa->setStatus(StatusMesa::LIVRE);
    }
}

bool Pedido::podeSerFechado() const{
    if(status == StatusPedido::CANCELADO||calcularSaldoRestante() > 0.0) {
        return false;
    }
    for(int i = 0; i < itens.size(); ++i) {
        if (itens[i].getStatus() != StatusItemPedido::ENTREGUE && itens[i].getStatus() != StatusItemPedido::CANCELADO) {
            return false;
        }
    }
    return true;
}
