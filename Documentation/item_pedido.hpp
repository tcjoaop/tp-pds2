#ifndef ITEM_PEDIDO_HPP
#define ITEM_PEDIDO_HPP

#include <string>
#include "produto.hpp"
#include "tipos.hpp"

/**
 * @brief Representa um produto e sua quantidade dentro de um pedido.
 *
 * Armazena uma referencia ao produto, o preco unitario usado no pedido,
 * observacoes e o estado de preparacao do item.
 */
class ItemPedido {
private:
    int id;
    Produto* produto;
    int quantidade;
    double precoUnitario;
    std::string observacoes;
    StatusItemPedido status;

public:
    /**
     * @brief Cria um item de pedido com os dados fornecidos.
     * @param id Identificador unico do item.
     * @param produto Produto associado ao item.
     * @param quantidade Quantidade solicitada.
     * @param precoUnitario Preco unitario registrado para este item.
     * @param observacoes Observacoes opcionais do item.
     */
    ItemPedido(int id, 
        const Produto& produto, 
        int quantidade, 
        double precoUnitario, 
        const std::string& observacoes = "");
    /**
     * @brief Cria uma copia de outro item de pedido.
     * @param outro Item cujos dados serao copiados.
     */
    ItemPedido(const ItemPedido& outro);
    /**
     * @brief Substitui os dados deste item pelos dados de outro.
     * @param outro Item usado como origem da atribuicao.
     * @return Referencia a este objeto apos a atribuicao.
     */
    ItemPedido& operator=(const ItemPedido& outro);
    /** @brief Libera os recursos administrados pelo item. */
    ~ItemPedido();

    /** @brief Retorna o identificador do item. @return Identificador do item. */
    int getId() const;
    /** @brief Retorna o produto associado ao item. @return Referencia constante ao produto. */
    const Produto& getProduto() const;
    /** @brief Retorna a quantidade solicitada. @return Quantidade do produto. */
    int getQuantidade() const;
    /** @brief Retorna o preco unitario registrado. @return Preco unitario. */
    double getPrecoUnitario() const;
    /** @brief Retorna as observacoes do item. @return Texto das observacoes. */
    std::string getObservacoes() const;
    /** @brief Retorna o status de preparacao do item. @return Status atual do item. */
    StatusItemPedido getStatus() const;

    /**
     * @brief Atualiza a quantidade solicitada.
     * @param quantidade Nova quantidade.
     */
    void setQuantidade(int quantidade);
    /**
     * @brief Atualiza as observacoes do item.
     * @param observacoes Novo texto de observacoes.
     */
    void setObservacoes(const std::string& observacoes);
    /**
     * @brief Atualiza o status de preparacao do item.
     * @param status Novo status do item.
     */
    void setStatus(StatusItemPedido status);

    /** @brief Calcula o subtotal do item. @return Preco unitario multiplicado pela quantidade. */
    double calcularSubtotal() const;
    /**
     * @brief Verifica se o item pode ser cancelado.
     * @return true se puder ser cancelado; false caso contrario.
     */
    bool podeSerCancelado() const;
};

#endif