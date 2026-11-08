#ifndef AUTENTICACAO_HPP
#define AUTENTICACAO_HPP
#include <string>
#include "banco_dados.hpp"
#include "usuario.hpp"

class Autenticacao {
private:
    BancoDados& bancoDados;
    Usuario* usuarioLogado;

public:
    explicit Autenticacao(BancoDados& bancoDados);
    ~Autenticacao();

    bool login(const std::string& login, 
                const std::string& senha);
    
    void logout();

    bool estaLogado() const;
    Usuario* getUsuarioLogado() const;

    bool possuiPermissao(const std::string& permissao) const;

private:
        std::string hashSenha(const std::string& senha) const;
        bool validarSenha(const std::string& senha, 
                        const std::string& hash) const;

};

#endif