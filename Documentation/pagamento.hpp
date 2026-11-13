#ifndef PAGAMENTO_HPP
#define PAGAMENTO_HPP

#include <string>
#include "tipos.hpp"


/**
 * @brief Registra uma transacao de pagamento de um pedido.
 *
 * Armazena a forma, o valor e a data e hora associadas ao pagamento.
 */
class Pagamento {
private:
    int id;
    FormaPagamento formaPagamento;
    double valor;
    std::string dataHoraPagamento;

public:
    /**
     * @brief Cria um pagamento com identificador, forma e valor.
     * @param id Identificador unico do pagamento.
     * @param formaPagamento Forma utilizada para pagar.
     * @param valor Valor registrado para o pagamento.
     */
    Pagamento(int id, FormaPagamento formaPagamento, double valor);
    /** @brief Destroi o pagamento. */
    ~Pagamento();

    /** @brief Retorna o identificador do pagamento. @return Identificador do pagamento. */
    int getId() const;
    /** @brief Retorna a forma de pagamento utilizada. @return Forma de pagamento. */
    FormaPagamento getFormaPagamento() const;
    /** @brief Retorna o valor registrado. @return Valor do pagamento. */
    double getValor() const;
    /** @brief Retorna a data e hora do pagamento. @return Referencia constante ao texto de data e hora. */
    const std::string& getDataHoraPagamento() const;

    /** @brief Atualiza a forma de pagamento. @param formaPagamento Nova forma de pagamento. */
    void setFormaPagamento(FormaPagamento formaPagamento);
    /** @brief Atualiza o valor do pagamento. @param valor Novo valor. */
    void setValor(double valor);

    /**
     * @brief Calcula o troco a partir do valor entregue.
     * @param valorPago Valor recebido do pagador.
     * @return Valor de troco calculado.
     */
    double calcularTroco(double valorPago) const;
};


#endif