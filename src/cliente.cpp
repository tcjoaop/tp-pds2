#include "../documentation/cliente.hpp"
#include <stdexcept>

Cliente::Cliente(int id, const std::string& nome, const std::string& telefone) {
    if (id <= 0) {
        throw std::invalid_argument("ID do cliente deve ser positivo.");
    }
    if (nome.empty()) {
        throw std::invalid_argument("Nome do cliente nao pode ser vazio.");
    }
    this->id = id;
    this->nome = nome;
    this->telefone = telefone;
}

int Cliente::getId() const {
    return id;
}

std::string Cliente::getNome() const {
    return nome;
}

std::string Cliente::getTelefone() const {
    return telefone;
}

void Cliente::setNome(const std::string& nome) {
    if (nome.empty()) {
        throw std::invalid_argument("Nome do cliente nao pode ser vazio.");
    }
    this->nome = nome;
}

void Cliente::setTelefone(const std::string& telefone) {
    this->telefone = telefone;
}