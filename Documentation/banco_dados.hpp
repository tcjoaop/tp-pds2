#ifndef BANCO_DADOS_HPP
#define BANCO_DADOS_HPP
#include <string>
#include <vector>
#include <fstream>
#include "usuario.hpp"
#include "produto.hpp"
#include "pedido.hpp"


/**
 * @brief Fornece operacoes de persistencia e consulta dos dados do restaurante.
 *
 * A implementacao utiliza o arquivo configurado para manter usuarios,
 * produtos, mesas e pedidos.
 */
class BancoDados {
private:
    std::string caminhoArquivo;

public:
    /**
     * @brief Cria o acesso ao banco de dados no caminho informado.
     * @param caminhoArquivo Caminho do arquivo de dados.
     */
    explicit BancoDados(const std::string& caminhoArquivo);
    /** @brief Fecha a conexao e libera os recursos do banco de dados. */
    ~BancoDados();

    /** @brief Abre ou estabelece a conexao com os dados. @return true se conectar; false caso contrario. */
    bool conectar();
    /** @brief Encerra a conexao com os dados. */
    void desconectar();
    /** @brief Verifica se a conexao esta ativa. @return true se conectado; false caso contrario. */
    bool estaConectado() const;

    /**
     * @brief Cria a estrutura inicial de dados do sistema.
     * @return true se a estrutura for criada; false caso contrario.
     */
    bool criarEstruturaInicial();

    /** @brief Persiste os dados de um usuario. @param usuario Usuario a salvar. @return true se salvo; false caso contrario. */
    bool salvarUsuario(const Usuario& usuario);
    /** @brief Persiste os dados de um produto. @param produto Produto a salvar. @return true se salvo; false caso contrario. */
    bool salvarProduto(const Produto& produto);
    /** @brief Persiste os dados de uma mesa. @param mesa Mesa a salvar. @return true se salva; false caso contrario. */
    bool salvarMesa(const Mesa& mesa);
    /** @brief Persiste os dados de um pedido. @param pedido Pedido a salvar. @return true se salvo; false caso contrario. */
    bool salvarPedido(const Pedido& pedido);

    /** @brief Lista os produtos persistidos. @return Vetor contendo os produtos encontrados. */
    std::vector<Produto> listarProdutos();
    /** @brief Lista as mesas persistidas. @return Vetor contendo as mesas encontradas. */
    std::vector<Mesa> listarMesas();
    /** @brief Lista os pedidos persistidos. @return Vetor contendo os pedidos encontrados. */
    std::vector<Pedido> listarPedidos();

    /**
     * @brief Busca um usuario pelo login.
     * @param login Login a consultar.
     * @return Ponteiro para o usuario encontrado ou nullptr se nao existir.
     */
    Usuario* buscarUsuarioPorLogin(const std::string& login);
    /**
     * @brief Busca um produto pelo identificador.
     * @param id Identificador do produto.
     * @return Ponteiro para o produto encontrado ou nullptr se nao existir.
     */
    Produto* buscarProdutoPorId(int id);
    /**
     * @brief Busca uma mesa pelo identificador.
     * @param id Identificador da mesa.
     * @return Ponteiro para a mesa encontrada ou nullptr se nao existir.
     */
    Mesa* buscarMesaPorId(int id);
    /**
     * @brief Busca um pedido pelo identificador.
     * @param id Identificador do pedido.
     * @return Ponteiro para o pedido encontrado ou nullptr se nao existir.
     */
    Pedido* buscarPedidoPorId(int id);
};

#endif