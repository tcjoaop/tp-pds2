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

/**
 * @brief Reune os dados e operacoes de um pedido de restaurante.
 *
 * Um pedido associa mesa, atendente e cliente, e acompanha seus itens,
 * pagamentos, valores e ciclo de status.
 */
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
    /**
     * @brief Cria um pedido e associa os dados iniciais informados.
     * @param id Identificador unico do pedido.
     * @param dataHoraAbertura Data e hora de abertura em formato textual.
     * @param atendente Usuario responsavel pelo atendimento; pode ser nulo.
     * @param mesa Mesa associada ao pedido; pode ser nula.
     * @param cliente Cliente associado ao pedido; pode ser nulo.
     */
    Pedido(int id,
          const std::string& dataHoraAbertura,
          Usuario* atendente = nullptr,
          Mesa* mesa = nullptr,
          Cliente* cliente = nullptr);
    /** @brief Libera os recursos administrados pelo pedido. */
    ~Pedido();

    /** @brief Retorna o identificador do pedido. @return Identificador do pedido. */
    int getId() const;
    /** @brief Retorna o status atual do pedido. @return Status do pedido. */
    StatusPedido getStatus() const;
    /** @brief Retorna a mesa associada ao pedido. @return Ponteiro para a mesa ou nullptr. */
    Mesa* getMesa() const;
    /** @brief Retorna o atendente associado ao pedido. @return Ponteiro para o usuario ou nullptr. */
    Usuario* getAtendente() const;
    /** @brief Retorna o cliente associado ao pedido. @return Ponteiro para o cliente ou nullptr. */
    Cliente* getCliente() const;
    /** @brief Fornece acesso somente para leitura aos itens do pedido. @return Referencia constante ao vetor de itens. */
    const std::vector<ItemPedido>& getItens() const;
    /** @brief Fornece acesso somente para leitura aos pagamentos do pedido. @return Referencia constante ao vetor de pagamentos. */
    const std::vector<Pagamento>& getPagamentos() const;

    /**
     * @brief Adiciona um item ao pedido.
     * @param item Item a ser incluido.
     */
    void adicionarItem(const ItemPedido& item);
    /**
     * @brief Remove do pedido o item com o identificador informado.
     * @param itemId Identificador do item a remover.
     */
    void removerItem(int itemId);
    /**
     * @brief Localiza um item pelo identificador.
     * @param itemId Identificador do item procurado.
     * @return Ponteiro para o item encontrado ou nullptr se nao existir.
     */
    ItemPedido* buscarItem(int itemId);

    /**
     * @brief Soma os subtotais dos itens que nao foram cancelados.
     * @return Total dos itens sem taxa de servico.
     */
    double calcularTotalSemTaxa() const;
    /**
     * @brief Calcula a taxa de servico sobre o total dos itens ativos.
     * @return Total sem taxa multiplicado pelo percentual de taxa configurado.
     */
    double calcularTaxaServico() const;
    /**
     * @brief Calcula o total do pedido apos taxa de servico e desconto.
     * @return Total sem taxa, somado a taxa de servico e subtraido do desconto.
     */
    double calcularTotalComTaxa() const;
    /** @brief Soma os pagamentos registrados no pedido. @return Valor total ja pago. */
    double calcularTotalPago() const;
    /** @brief Calcula quanto ainda falta pagar. @return Saldo restante do pedido. */
    double calcularSaldoRestante() const;

    /**
     * @brief Define o percentual usado no calculo da taxa de servico.
     * @param taxa Novo percentual da taxa.
     */
    void setTaxaServicoPercentual(double taxa);
    /**
     * @brief Define o desconto aplicado ao pedido.
     * @param desconto Novo valor do desconto.
     */
    void setDesconto(double desconto);

    /**
     * @brief Registra um pagamento associado ao pedido.
     * @param pagamento Pagamento a ser incluido.
     *
     * Se o saldo resultante for menor ou igual a zero, o status do pedido
     * passa para FINALIZANDO.
     */
    void adicionarPagamento(const Pagamento& pagamento);

    /**
     * @brief Altera o status do pedido.
     * @param novoStatus Status que sera atribuido.
     */
    void alterarStatus(StatusPedido novoStatus);
    /**
     * @brief Fecha o pedido quando ele atende aos criterios de fechamento.
     * @param dataHoraFechamento Data e hora de fechamento em formato textual.
     *
     * Quando o fechamento e permitido, registra a data e hora, altera o
     * status para ENTREGUE e libera a mesa associada, se houver.
     */
    void fecharPedido(const std::string& dataHoraFechamento);
    /** @brief Cancela o pedido. */
    void cancelar();

    /**
     * @brief Verifica se o pedido pode ser fechado.
     * @return true se nao estiver cancelado, nao houver saldo pendente e
     * todos os itens estiverem entregues ou cancelados; false caso contrario.
     */
    bool podeSerFechado() const;

};

#endif