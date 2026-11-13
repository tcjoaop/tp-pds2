#ifndef PERFIL_HPP
#define PERFIL_HPP
#include <string>
#include <vector>

/**
 * @brief Representa um perfil de acesso configuravel.
 *
 * Mantem o nome do perfil e a lista de permissoes associadas.
 */
class Perfil {
private:
    int id;
    std::string nome;
    std::vector<std::string> permissoes;

public:
    /**
     * @brief Cria um perfil com nome e permissoes iniciais.
     * @param id Identificador unico do perfil.
     * @param nome Nome do perfil.
     * @param permissoes Lista de permissoes iniciais.
     */
    Perfil(int id, const std::string& nome, const std::vector<std::string>& permissoes);

    /** @brief Retorna o identificador do perfil. @return Identificador do perfil. */
    int getId() const;
    /** @brief Retorna o nome do perfil. @return Nome do perfil. */
    std::string getNome() const;
    /** @brief Retorna a lista de permissoes do perfil. @return Copia da lista de permissoes. */
    std::vector<std::string> getPermissoes() const;

    /**
     * @brief Adiciona uma permissao ao perfil.
     * @param permissao Permissao a incluir.
     */
    void adicionarPermissao(const std::string& permissao);
    /**
     * @brief Remove do perfil a permissao informada.
     * @param permissao Permissao a remover.
     */
    void removerPermissao(const std::string& permissao);
    /**
     * @brief Verifica se o perfil contem uma permissao.
     * @param permissao Permissao a consultar.
     * @return true se a permissao estiver presente; false caso contrario.
     */
    bool possuiPermissao(const std::string& permissao) const;
};

#endif