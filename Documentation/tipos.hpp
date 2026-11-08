#ifndef TIPOS_HPP
#define TIPOS_HPP

// Aqui são nossos enums

enum class PerfilAcesso {
    ADMINISTRADOR,
    CAIXA,
    GARCOM,
    COZINHEIRO
};

enum class StatusPedido {
    ABERTO,
    AGUARDANDO_PREPARO,
    EM_PREPARO,
    PRONTO,
    ENTREGUE,
    AGUARDANDO_PAGAMENTO,
    FINALIZANDO,
    CANCELADO
};

enum class StatusMesa {
    LIVRE,
    OCUPADA,
    RESERVADA,
    AGUARDANDO_PAGAMENTO,
    INDISPONIVEL
};

enum class StatusItemPedido {
    PENDENTE,
    ENVIADO_COZINHA,
    EM_PREPARO,
    PRONTO,
    ENTREGUE,
    CANCELADO
};

enum class FormaPagamento {
    DINHEIRO,
    CARTAO_CREDITO,
    CARTAO_DEBITO,
    PIX
};

#endif