#ifndef SISTEMA_RESTAURANTE_HPP
#define SISTEMA_RESTAURANTE_HPP

#include "banco_dados.hpp"
#include "autenticacao.hpp"

/**
 * @brief Coordena a inicializacao e a execucao do sistema de restaurante.
 *
 * Mantem os servicos de persistencia e autenticacao e encaminha a interacao
 * para as telas e modulos da aplicacao.
 */
class SistemaRestaurante {
    private:
        BancoDados bancoDados;
        Autenticacao autenticacao;

        /** @brief Exibe a tela de autenticacao do sistema. */
        void exibirTelaLogin();
        /** @brief Exibe a tela principal apos o acesso ao sistema. */
        void exibirTelaPrincipal();

        /** @brief Executa o modulo de gerenciamento de mesas. */
        void moduloMesas();
        /** @brief Executa o modulo de gerenciamento de pedidos. */
        void moduloPedidos();
        /** @brief Executa o modulo de acompanhamento da cozinha. */
        void moduloCozinha();
        /** @brief Executa o modulo de caixa e pagamentos. */
        void moduloCaixa();
        /** @brief Executa o modulo de relatorios. */
        void moduloRelatorios();
        /** @brief Executa o modulo de cadastros. */
        void moduloCadastros();

    public:
        /**
         * @brief Cria o sistema usando o caminho do arquivo de dados.
         * @param caminhoBancoDados Caminho do arquivo usado pelo banco de dados.
         */
        explicit SistemaRestaurante(const std::string& caminhoBancoDados);
        /**
         * @brief Inicializa os recursos necessarios para a aplicacao.
         * @return true se a inicializacao for concluida com sucesso; false caso contrario.
         */
        bool inicializar();
        /** @brief Inicia o fluxo principal de execucao da aplicacao. */
        void executar();
};

#endif