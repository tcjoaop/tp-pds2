#include "../documentation/usuario.hpp"
#include <stdexcept>

Usuario::Usuario(const int id, const std::string& nome, const std::string& login, const std::string& senha, PerfilAcesso perfil)
    : id(id), nome(nome), login(login), senha(senha), perfil(perfil) {
    if (id <= 0) {
        throw std::invalid_argument("ID do usuario deve ser positivo.");
    }
    if (nome.empty()) {
        throw std::invalid_argument("Nome do usuario nao pode ser vazio.");
    }
    if (login.empty()) {
        throw std::invalid_argument("Login do usuario nao pode ser vazio.");
    }
}

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

PerfilAcesso Usuario::getPerfil() const {
    return perfil;
}

void Usuario::setNome(const std::string& nome) {
    if (nome.empty()) {
        throw std::invalid_argument("Nome do usuario nao pode ser vazio.");
    }
    this->nome = nome;
}

void Usuario::setLogin(const std::string& login) {
    if (login.empty()) {
        throw std::invalid_argument("Login do usuario nao pode ser vazio.");
    }
    this->login = login;
}

void Usuario::setSenha(const std::string& senha) {
    this->senha = senha;
}

void Usuario::setPerfil(PerfilAcesso perfil) {
    this->perfil = perfil;
}

bool Usuario::podeAcessar(PerfilAcesso modulo) const {
    if (this->perfil == PerfilAcesso::ADMINISTRADOR) {
        return true;
    }
    return this->perfil == modulo;
}

std::string Usuario::getDescricaoCargo() const {
    return "Usuario Padrao";
}

// Subclasse Administrador
Administrador::Administrador(int id, const std::string& nome, const std::string& login, const std::string& senha)
    : Usuario(id, nome, login, senha, PerfilAcesso::ADMINISTRADOR) {}

bool Administrador::podeAcessar([[maybe_unused]] PerfilAcesso modulo) const {
    return true; // Administrador tem acesso a todos os modulos
}

std::string Administrador::getDescricaoCargo() const {
    return "Administrador do Sistema (Acesso Total)";
}

// Subclasse Garcom
Garcom::Garcom(int id, const std::string& nome, const std::string& login, const std::string& senha)
    : Usuario(id, nome, login, senha, PerfilAcesso::GARCOM) {}

bool Garcom::podeAcessar(PerfilAcesso modulo) const {
    return modulo == PerfilAcesso::GARCOM;
}

std::string Garcom::getDescricaoCargo() const {
    return "Garcom (Mesas e Pedidos)";
}

// Subclasse Cozinheiro
Cozinheiro::Cozinheiro(int id, const std::string& nome, const std::string& login, const std::string& senha)
    : Usuario(id, nome, login, senha, PerfilAcesso::COZINHEIRO) {}

bool Cozinheiro::podeAcessar(PerfilAcesso modulo) const {
    return modulo == PerfilAcesso::COZINHEIRO;
}

std::string Cozinheiro::getDescricaoCargo() const {
    return "Cozinheiro (Fila da Cozinha)";
}

// Subclasse Caixa
Caixa::Caixa(int id, const std::string& nome, const std::string& login, const std::string& senha)
    : Usuario(id, nome, login, senha, PerfilAcesso::CAIXA) {}

bool Caixa::podeAcessar(PerfilAcesso modulo) const {
    return modulo == PerfilAcesso::CAIXA;
}

std::string Caixa::getDescricaoCargo() const {
    return "Operador de Caixa (Fechamento e Pagamento)";
}
