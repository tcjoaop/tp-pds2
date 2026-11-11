#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include "tipos.hpp"

class Usuario {
protected:
    int id;
    std::string nome;
    std::string login;
    std::string senha;
    PerfilAcesso perfil;

public:
    Usuario(int id, const std::string& nome, const std::string& login, const std::string& senha, PerfilAcesso perfil);
    virtual ~Usuario() = default;

    int getId() const;
    std::string getNome() const;
    std::string getLogin() const;
    std::string getSenha() const;
    PerfilAcesso getPerfil() const;

    void setNome(const std::string& nome);
    void setLogin(const std::string& login);
    void setSenha(const std::string& senha);
    void setPerfil(PerfilAcesso perfil);

    virtual bool podeAcessar(PerfilAcesso modulo) const;
    virtual std::string getDescricaoCargo() const;
};

class Administrador : public Usuario {
public:
    Administrador(int id, const std::string& nome, const std::string& login, const std::string& senha);
    bool podeAcessar(PerfilAcesso modulo) const override;
    std::string getDescricaoCargo() const override;
};

class Garcom : public Usuario {
public:
    Garcom(int id, const std::string& nome, const std::string& login, const std::string& senha);
    bool podeAcessar(PerfilAcesso modulo) const override;
    std::string getDescricaoCargo() const override;
};

class Cozinheiro : public Usuario {
public:
    Cozinheiro(int id, const std::string& nome, const std::string& login, const std::string& senha);
    bool podeAcessar(PerfilAcesso modulo) const override;
    std::string getDescricaoCargo() const override;
};

class Caixa : public Usuario {
public:
    Caixa(int id, const std::string& nome, const std::string& login, const std::string& senha);
    bool podeAcessar(PerfilAcesso modulo) const override;
    std::string getDescricaoCargo() const override;
};

#endif
