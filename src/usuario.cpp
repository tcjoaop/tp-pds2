#include "../documentation/usuario.hpp"

Usuario::Usuario(const int id, const std::string& nome, const std::string& login, const std::string& senha, const Perfil& perfil) : id(id), nome(nome), login(login), senha(senha), perfil(perfil) {}

int Usuario::getId() const {
    return id;
}

std::string Usuario::getNome() const {
    return nome;
}

std::string Usuario::getLogin() const {
    return login;
}

std::string Usuario::getSenha() const {
    return senha;
}

Perfil Usuario::getPerfil() const {
    return perfil;
}

void Usuario::setNome(const std::string& nome) {
    this->nome = nome;
}

void Usuario::setLogin(const std::string& login) {
    this->login = login;
}

void Usuario::setSenha(const std::string& senha) {
    this->senha = senha;
}

void Usuario::setPerfil(const Perfil& perfil) {
    this->perfil = perfil;
}