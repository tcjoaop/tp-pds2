#ifndef PRODUTO_HPP
#define PRODUTO_HPP
#include <string>
#include "categoria.hpp"

/**
 * @brief Representa um produto oferecido pelo restaurante.
 *
 * Armazena o nome, preco, disponibilidade e tempo estimado de preparo.
 */
class Produto {
private:
    int id;
    std::string nome;
    int preco;
    bool disponivel;
    int tempoPreparo;

public:
    /**
     * @brief Cria um produto com os dados informados.
     * @param id Identificador unico do produto.
     * @param nome Nome do produto.
     * @param preco Preco do produto.
     * @param disponivel Indica se o produto esta disponivel para pedido.
     * @param tempoPreparo Tempo estimado de preparo.
     */
    Produto(const int id,const std::string& nome,const int preco,const bool disponivel, const int tempoPreparo);

    /** @brief Retorna o identificador do produto. @return Identificador do produto. */
    int getId() const;
    /** @brief Retorna o nome do produto. @return Nome do produto. */
    std::string getNome() const;
    /** @brief Retorna o preco do produto. @return Preco do produto. */
    int getPreco() const;
    /** @brief Informa se o produto esta disponivel. @return true se disponivel; false caso contrario. */
    bool getDisponivel() const;
    /** @brief Retorna o tempo estimado de preparo. @return Tempo de preparo. */
    int getTempoPreparo() const;

    /** @brief Atualiza o identificador do produto. @param id Novo identificador. */
    void setId(const int id);
    /** @brief Atualiza o nome do produto. @param nome Novo nome. */
    void setNome(const std::string& nome);
    /** @brief Atualiza o preco do produto. @param preco Novo preco. */
    void setPreco(const int preco);
    /** @brief Atualiza a disponibilidade do produto. @param disponivel Novo estado de disponibilidade. */
    void setDisponivel(const bool disponivel);
    /** @brief Atualiza o tempo estimado de preparo. @param tempoPreparo Novo tempo de preparo. */
    void setTempoPreparo(const int tempoPreparo);
};

#endif
