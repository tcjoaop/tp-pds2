#ifndef AUTENTICACAO_HPP
#define AUTENTICACAO_HPP

#include <string>
#include "banco_dados.hpp"
#include "usuario.hpp"
#include "tipos.hpp"

/**
 * @brief Gerencia a autenticacao e a sessao do usuario.
 *
 * Consulta o banco de dados para autenticar credenciais e disponibiliza
 * verificacoes do usuario e das permissoes da sessao atual.
 */
class Autenticacao {
private:
    BancoDados& bancoDados;
    Usuario* usuarioLogado;

public:
    /**
     * @brief Cria o servico de autenticacao associado a um banco de dados.
     * @param bancoDados Banco de dados usado nas consultas de usuario.
     */
    explicit Autenticacao(BancoDados& bancoDados);
    /** @brief Libera os recursos associados a sessao de autenticacao. */
    ~Autenticacao();

    /**
     * @brief Tenta autenticar um usuario com as credenciais informadas.
     * @param login Login informado.
     * @param senha Senha informada.
     * @return true se a autenticacao for bem-sucedida; false caso contrario.
     */
    bool login(const std::string& login, const std::string& senha);
    /** @brief Encerra a sessao do usuario autenticado. */
    void logout();

    /** @brief Informa se existe uma sessao autenticada. @return true se houver usuario logado. */
    bool estaLogado() const;
    /** @brief Retorna o usuario da sessao atual. @return Usuario logado ou nullptr. */
    Usuario* getUsuarioLogado() const;

    /**
     * @brief Verifica se o usuario atual possui o perfil necessario.
     * @param perfilNecessario Perfil exigido para a operacao.
     * @return true se a permissao estiver presente; false caso contrario.
     */
    bool possuiPermissao(PerfilAcesso perfilNecessario) const;

private:
    /**
     * @brief Produz a representacao hash de uma senha.
     * @param senha Senha em texto a processar.
     * @return Representacao hash produzida.
     */
    std::string hashSenha(const std::string& senha) const;
    /**
     * @brief Compara uma senha informada com sua representacao armazenada.
     * @param senha Senha em texto a validar.
     * @param hash Representacao armazenada para comparacao.
     * @return true se a senha corresponder; false caso contrario.
     */
    bool validarSenha(const std::string& senha, const std::string& hash) const;
};

#endif
