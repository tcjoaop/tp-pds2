#include "../documentation/Produto.hpp"

Produto::Produto(const int id,const std::string& nome,const int preco,const bool disponivel, const int tempoPreparo) : id(id), nome(nome), preco(preco), disponivel(disponivel), tempoPreparo(tempoPreparo) {}

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
    this->id = id;
}

void Produto::setNome(const std::string& nome){
    this->nome = nome;
}

void Produto::setPreco(const int preco){
    this->preco = preco;
}

void Produto::setDisponivel(const bool disponivel){
    this->disponivel = disponivel;
}

void Produto::setTempoPreparo(const int tempoPreparo){
    this->tempoPreparo = tempoPreparo;
}