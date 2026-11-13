#include "../documentation/categoria.hpp"
#include <stdexcept>

Categoria::Categoria(const int id, const std::string& nome, const std::string& descricao)
    : id(id), nome(nome), descricao(descricao) {
    if (id <= 0) {
        throw std::invalid_argument("ID da categoria deve ser positivo.");
    }
    if (nome.empty()) {
        throw std::invalid_argument("Nome da categoria nao pode ser vazio.");
    }
}

int Categoria::getId() const{
    return id;
}

std::string Categoria::getNome() const{
    return nome;
}

std::string Categoria::getDescricao() const{
    return descricao;
}

void Categoria::setId(const int id){
    if (id <= 0) {
        throw std::invalid_argument("ID da categoria deve ser positivo.");
    }
    this->id = id;
}

void Categoria::setNome(const std::string& nome){
    if (nome.empty()) {
        throw std::invalid_argument("Nome da categoria nao pode ser vazio.");
    }
    this->nome = nome;
}

void Categoria::setDescricao(const std::string& descricao){
    this->descricao = descricao;
}
