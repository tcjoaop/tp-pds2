#ifndef TIPOS_HPP
#define TIPOS_HPP

/**
 * @brief Perfis de acesso usados no controle de permissoes do sistema.
 */
enum class PerfilAcesso {
    ADMINISTRADOR, /**< Acesso de administrador. */
    CAIXA,         /**< Acesso ao modulo de caixa. */
    GARCOM,        /**< Acesso de atendimento como garcom. */
    COZINHEIRO     /**< Acesso ao modulo de cozinha. */
};

/**
 * @brief Estados possiveis para o ciclo de vida de um pedido.
 */
enum class StatusPedido {
    ABERTO,                 /**< Pedido aberto para edicao e inclusao de itens. */
    AGUARDANDO_PREPARO,     /**< Pedido aguardando inicio do preparo. */
    EM_PREPARO,             /**< Pedido em preparo pela cozinha. */
    PRONTO,                 /**< Pedido pronto para ser entregue. */
    ENTREGUE,               /**< Pedido entregue ao cliente. */
    AGUARDANDO_PAGAMENTO,   /**< Pedido aguardando pagamento. */
    FINALIZANDO,            /**< Pedido em processo de fechamento. */
    CANCELADO               /**< Pedido cancelado. */
};

/**
 * @brief Estados operacionais possiveis para uma mesa.
 */
enum class StatusMesa {
    LIVRE,                  /**< Mesa disponivel para ocupacao. */
    OCUPADA,                /**< Mesa em uso. */
    RESERVADA,              /**< Mesa reservada. */
    AGUARDANDO_PAGAMENTO,   /**< Mesa aguardando a quitacao da conta. */
    INDISPONIVEL            /**< Mesa temporariamente indisponivel. */
};

/**
 * @brief Estados possiveis para a preparacao de um item de pedido.
 */
enum class StatusItemPedido {
    PENDENTE,           /**< Item ainda nao enviado para preparo. */
    ENVIADO_COZINHA,    /**< Item encaminhado para a cozinha. */
    EM_PREPARO,         /**< Item em preparo. */
    PRONTO,             /**< Item pronto para entrega. */
    ENTREGUE,           /**< Item entregue ao cliente. */
    CANCELADO           /**< Item cancelado. */
};

/**
 * @brief Formas de pagamento aceitas pelo sistema.
 */
enum class FormaPagamento {
    DINHEIRO,           /**< Pagamento em dinheiro. */
    CARTAO_CREDITO,     /**< Pagamento com cartao de credito. */
    CARTAO_DEBITO,      /**< Pagamento com cartao de debito. */
    PIX                 /**< Pagamento por PIX. */
};

#endif