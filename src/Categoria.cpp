#include "../documentation/Categoria.hpp"

Categoria::Categoria(const int id,const std::string& numero,const std::string& descricao) : id(id), nome(numero), descricao(descricao) {}

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
    this->id = id;
}

void Categoria::setNome(const std::string& nome){
    this->nome = nome;
}

void Categoria::setDescricao(const std::string& descricao){
    this->descricao = descricao;
}