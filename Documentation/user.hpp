#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <string>
#include "Perfil.hpp"

class Usuario {
private:
    int id;
    std::string nome;
    std::string login;
    std::string senha;
    Perfil perfil;

public:
    Usuario(int id, const std::string& nome, const std::string& login, const std::string& senha, const Perfil& perfil);

    int getId() const;
    std::string getNome() const;
    std::string getLogin() const;
    std::string getSenha() const;
    Perfil getPerfil() const;

    void setNome(const std::string& nome);
    void setLogin(const std::string& login);
    void setSenha(const std::string& senha);
    void setPerfil(const Perfil& perfil);
};

#endif