#include "../documentation/produto.hpp"
#include <stdexcept>

Produto::Produto(const int id, const std::string& nome, const int preco, const bool disponivel, const int tempoPreparo) {
    if (id <= 0) {
        throw std::invalid_argument("ID do produto deve ser positivo.");
    }
    if (nome.empty()) {
        throw std::invalid_argument("Nome do produto nao pode ser vazio.");
    }
    if (preco < 0) {
        throw std::invalid_argument("Preco do produto nao pode ser negativo.");
    }
    if (tempoPreparo < 0) {
        throw std::invalid_argument("Tempo de preparo nao pode ser negativo.");
    }
    this->id = id;
    this->nome = nome;
    this->preco = preco;
    this->disponivel = disponivel;
    this->tempoPreparo = tempoPreparo;
}

int Produto::getId() const{
    return id;
}

std::string Produto::getNome() const{
    return nome;
}

int Produto::getPreco() const{
    return preco;
}

bool Produto::getDisponivel() const{
    return disponivel;
}

int Produto::getTempoPreparo() const{
    return tempoPreparo;
}

void Produto::setId(const int id){
    if (id <= 0) {
        throw std::invalid_argument("ID do produto deve ser positivo.");
    }
    this->id = id;
}

void Produto::setNome(const std::string& nome){
    if (nome.empty()) {
        throw std::invalid_argument("Nome do produto nao pode ser vazio.");
    }
    this->nome = nome;
}

void Produto::setPreco(const int preco){
    if (preco < 0) {
        throw std::invalid_argument("Preco do produto nao pode ser negativo.");
    }
    this->preco = preco;
}

void Produto::setDisponivel(const bool disponivel){
    this->disponivel = disponivel;
}

void Produto::setTempoPreparo(const int tempoPreparo){
    if (tempoPreparo < 0) {
        throw std::invalid_argument("Tempo de preparo nao pode ser negativo.");
    }
    this->tempoPreparo = tempoPreparo;
}
