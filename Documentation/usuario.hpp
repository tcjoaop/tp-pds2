#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include "tipos.hpp"

/**
 * @brief Representa um usuario do sistema e seu perfil de acesso.
 *
 * Serve como classe base para os tipos de usuario com cargos especificos.
 */
class Usuario {
protected:
    int id;
    std::string nome;
    std::string login;
    std::string senha;
    PerfilAcesso perfil;

public:
    /**
     * @brief Cria um usuario com credenciais e perfil definidos.
     * @param id Identificador unico do usuario.
     * @param nome Nome do usuario.
     * @param login Nome de acesso ao sistema.
     * @param senha Senha do usuario.
     * @param perfil Perfil de acesso associado ao usuario.
     */
    Usuario(int id, const std::string& nome, const std::string& login, const std::string& senha, PerfilAcesso perfil);
    /** @brief Destroi o usuario por meio de um destrutor virtual. */
    virtual ~Usuario() = default;

    /** @brief Retorna o identificador do usuario. @return Identificador do usuario. */
    int getId() const;
    /** @brief Retorna o nome do usuario. @return Nome do usuario. */
    std::string getNome() const;
    /** @brief Retorna o login do usuario. @return Login do usuario. */
    std::string getLogin() const;
    /** @brief Retorna a senha armazenada do usuario. @return Senha armazenada. */
    std::string getSenha() const;
    /** @brief Retorna o perfil de acesso do usuario. @return Perfil de acesso. */
    PerfilAcesso getPerfil() const;

    /** @brief Atualiza o nome do usuario. @param nome Novo nome. */
    void setNome(const std::string& nome);
    /** @brief Atualiza o login do usuario. @param login Novo login. */
    void setLogin(const std::string& login);
    /** @brief Atualiza a senha do usuario. @param senha Nova senha. */
    void setSenha(const std::string& senha);
    /** @brief Atualiza o perfil de acesso. @param perfil Novo perfil. */
    void setPerfil(PerfilAcesso perfil);

    /**
     * @brief Verifica se o usuario pode acessar um modulo.
     * @param modulo Perfil exigido pelo modulo.
     * @return true se o acesso for permitido; false caso contrario.
     */
    virtual bool podeAcessar(PerfilAcesso modulo) const;
    /** @brief Retorna a descricao do cargo do usuario. @return Descricao do cargo. */
    virtual std::string getDescricaoCargo() const;
};

/** @brief Usuario com o cargo de administrador. */
class Administrador : public Usuario {
public:
    /**
     * @brief Cria um administrador com os dados de usuario informados.
     * @param id Identificador unico.
     * @param nome Nome do administrador.
     * @param login Nome de acesso.
     * @param senha Senha de acesso.
     */
    Administrador(int id, const std::string& nome, const std::string& login, const std::string& senha);
    /**
     * @brief Verifica a permissao de acesso do administrador.
     * @param modulo Perfil exigido pelo modulo.
     * @return true se o acesso for permitido; false caso contrario.
     */
    bool podeAcessar(PerfilAcesso modulo) const override;
    /** @brief Retorna a descricao do cargo. @return Descricao do cargo de administrador. */
    std::string getDescricaoCargo() const override;
};

/** @brief Usuario com o cargo de garcom. */
class Garcom : public Usuario {
public:
    /**
     * @brief Cria um garcom com os dados de usuario informados.
     * @param id Identificador unico.
     * @param nome Nome do garcom.
     * @param login Nome de acesso.
     * @param senha Senha de acesso.
     */
    Garcom(int id, const std::string& nome, const std::string& login, const std::string& senha);
    /**
     * @brief Verifica a permissao de acesso do garcom.
     * @param modulo Perfil exigido pelo modulo.
     * @return true se o acesso for permitido; false caso contrario.
     */
    bool podeAcessar(PerfilAcesso modulo) const override;
    /** @brief Retorna a descricao do cargo. @return Descricao do cargo de garcom. */
    std::string getDescricaoCargo() const override;
};

/** @brief Usuario com o cargo de cozinheiro. */
class Cozinheiro : public Usuario {
public:
    /**
     * @brief Cria um cozinheiro com os dados de usuario informados.
     * @param id Identificador unico.
     * @param nome Nome do cozinheiro.
     * @param login Nome de acesso.
     * @param senha Senha de acesso.
     */
    Cozinheiro(int id, const std::string& nome, const std::string& login, const std::string& senha);
    /**
     * @brief Verifica a permissao de acesso do cozinheiro.
     * @param modulo Perfil exigido pelo modulo.
     * @return true se o acesso for permitido; false caso contrario.
     */
    bool podeAcessar(PerfilAcesso modulo) const override;
    /** @brief Retorna a descricao do cargo. @return Descricao do cargo de cozinheiro. */
    std::string getDescricaoCargo() const override;
};

/** @brief Usuario com o cargo de caixa. */
class Caixa : public Usuario {
public:
    /**
     * @brief Cria um caixa com os dados de usuario informados.
     * @param id Identificador unico.
     * @param nome Nome do caixa.
     * @param login Nome de acesso.
     * @param senha Senha de acesso.
     */
    Caixa(int id, const std::string& nome, const std::string& login, const std::string& senha);
    /**
     * @brief Verifica a permissao de acesso do caixa.
     * @param modulo Perfil exigido pelo modulo.
     * @return true se o acesso for permitido; false caso contrario.
     */
    bool podeAcessar(PerfilAcesso modulo) const override;
    /** @brief Retorna a descricao do cargo. @return Descricao do cargo de caixa. */
    std::string getDescricaoCargo() const override;
};

#endif
