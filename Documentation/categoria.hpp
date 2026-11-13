#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP
#include <string>
#include "produto.hpp"

/**
 * @brief Agrupa produtos em uma categoria identificada por nome e descricao.
 */
class Categoria {
private:
    int id;
    std::string nome;
    std::string descricao;

public:
    /**
     * @brief Cria uma categoria com os dados informados.
     * @param id Identificador unico da categoria.
     * @param nome Nome da categoria.
     * @param descricao Descricao da categoria.
     */
    Categoria(const int id,const std::string& nome,const std::string& descricao);

    /** @brief Retorna o identificador da categoria. @return Identificador da categoria. */
    int getId() const;
    /** @brief Retorna o nome da categoria. @return Nome da categoria. */
    std::string getNome() const;
    /** @brief Retorna a descricao da categoria. @return Descricao da categoria. */
    std::string getDescricao() const;

    /** @brief Atualiza o identificador da categoria. @param id Novo identificador. */
    void setId(const int id);
    /** @brief Atualiza o nome da categoria. @param nome Novo nome. */
    void setNome(const std::string& nome);
    /** @brief Atualiza a descricao da categoria. @param descricao Nova descricao. */
    void setDescricao(const std::string& descricao);  
};

#endif
