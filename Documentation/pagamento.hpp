#ifndef PAGAMENTO_HPP
#define PAGAMENTO_HPP

#include <string>
#include "tipos.hpp"


class Pagamento {
private:
    int id;
    FormaPagamento formaPagamento;
    double valor;
    std::string dataHoraPagamento;

public:
    Pagamento(int id, FormaPagamento formaPagamento, double valor);
    ~Pagamento();

    int getId() const;
    FormaPagamento getFormaPagamento() const;
    double getValor() const;
    const std::string& getDataHoraPagamento() const;

    void setFormaPagamento(FormaPagamento formaPagamento);
    void setValor(double valor);

    double calcularTroco(double valorPago) const;
};
