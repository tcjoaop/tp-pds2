#ifndef SISTEMA_RESTAURANTE_HPP
#define SISTEMA_RESTAURANTE_HPP

#include "banco_dados.hpp"
#include "autenticacao.hpp"

class SistemaRestaurante {
    private:
        BancoDados bancoDados;
        Autenticacao autenticacao;

        void exibirTelaLogin();
        void exibirTelaPrincipal();

        void moduloMesas();
        void moduloPedidos();
        void moduloCozinha();
        void moduloCaixa();
        void moduloRelatorios();
        void moduloCadastros();

    public:
        explicit SistemaRestaurante(const std::string& caminhoBancoDados);
        bool inicializar();
        void executar();
};

#endif