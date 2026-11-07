#include "../documentation/Mesa.hpp"

Mesa::Mesa(const int id,const int numero,const int capacidade,const int status) : id(id), numero(numero), capacidade(capacidade), status(status) {}

int Mesa::getId() const{
    return id;
}

int Mesa::getNumero() const{
    return numero;
}

int Mesa::getCapacidade() const{
    return capacidade;
}

int Mesa::getStatus() const{
    return status;
}
   
void Mesa::setId(const int id){
    this->id = id;
}

void Mesa::setNumero(const int numero){
    this->numero = numero;
}

void Mesa::setCapacidade(const int capacidade){
    this->capacidade = capacidade;
}

void Mesa::setStatus(const int status){
    this->status = status;
}

void Mesa::ocupar(Mesa& Mesa){

}

void Mesa::liberar(Mesa& Mesa){
    
}
