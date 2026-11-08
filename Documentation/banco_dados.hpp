#ifndef BANCO_DADOS_HPP
#define BANCO_DADOS_HPP
#include <string>
#include <vector>
#include "usuario.hpp"
#include "produto.hpp"
#include "mesa.hpp"
#include "pedido.hpp"


class BancoDados {
private:
    std::string caminhoArquivo;
    void* conexao; // Ponteiro para a conexão com o banco de dados

public:
    explicit BancoDados(const std::string& caminhoArquivo);
    ~BancoDados();
    
    bool conectar();
    void desconectar();
    bool estaConectado() const;

    bool criarEstruturaInicial();

    bool salvarUsuario(const Usuario& usuario);
    bool salvarProduto(const Produto& produto);
    bool salvarMesa(const Mesa& mesa);
    bool salvarPedido(const Pedido& pedido);

    std::vector<Produto> listarProdutos();
    std::vector<Mesa> listarMesas();
    std::vector<Pedido> listarPedidos();

    Usuario* buscarUsuarioPorLogin(const std::string& login);
    Produto* buscarProdutoPorId(int id);
    Mesa* buscarMesaPorId(int id);
    Pedido* buscarPedidoPorId(int id);
};

#endif