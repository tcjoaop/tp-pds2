#include "../documentation/pagamento.hpp"
#include <ctime>
#include <stdexcept>

Pagamento::Pagamento(int id, FormaPagamento formaPagamento, double valor) {
    if (id <= 0) {
        throw std::invalid_argument("ID do pagamento deve ser positivo.");
    }
    if (valor <= 0.0) {
        throw std::invalid_argument("Valor do pagamento deve ser maior que zero.");
    }
    this->id = id;
    this->formaPagamento = formaPagamento;
    this->valor = valor;

    std::time_t t = std::time(0);
    dataHoraPagamento = std::ctime(&t);
    if((!this->dataHoraPagamento.empty())&&(this->dataHoraPagamento.back() == '\n')) {
        this->dataHoraPagamento.pop_back();
    }
}

Pagamento::~Pagamento() {}

int Pagamento::getId() const {
    return id;
}

FormaPagamento Pagamento::getFormaPagamento() const {
    return formaPagamento;
}

double Pagamento::getValor() const {
    return valor;
}
const std::string& Pagamento::getDataHoraPagamento() const {
    return dataHoraPagamento;
}

void Pagamento::setFormaPagamento(FormaPagamento formaPagamento) {
    this->formaPagamento = formaPagamento;
}

void Pagamento::setValor(double valor) {
    if (valor <= 0.0) {
        throw std::invalid_argument("Valor do pagamento deve ser maior que zero.");
    }
    this->valor = valor;
}

double Pagamento::calcularTroco(double valorPago) const {
    if((this->valor < valorPago)&&(this->formaPagamento == FormaPagamento::DINHEIRO)){ 
        return valorPago - this->valor;
    } else {
    return 0.0;
    }
}