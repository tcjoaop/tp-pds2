#include "../Documentation/cliente.hpp"

Cliente::Cliente(int id, const std::string& nome, const std::string& telefone) : id(id), nome(nome), telefone(telefone) {}

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
    this->nome = nome;
}

void Cliente::setTelefone(const std::string& telefone) {
    this->telefone = telefone;
}