#ifndef ITEM_PEDIDO_HPP
#define ITEM_PEDIDO_HPP

#include <string>
#include "produto.hpp"
#include "tipos.hpp"

class ItemPedido {
private:
    int id;
    Produto* produto;
    int quantidade;
    double precoUnitario;
    std::string observacoes;
    StatusItemPedido status;

public:
    ItemPedido(int id, 
        const Produto& produto, 
        int quantidade, 
        double precoUnitario, 
        const std::string& observacoes = "");
    ~ItemPedido();

    int getId() const;
    const Produto& getProduto() const;
    int getQuantidade() const;
    double getPrecoUnitario() const;
    std::string getObservacoes() const;
    StatusItemPedido getStatus() const;

    void setQuantidade(int quantidade);
    void setObservacoes(const std::string& observacoes);
    void setStatus(StatusItemPedido status);

    double calcularSubtotal() const;
    bool podeSerCancelado() const;
};

#endif