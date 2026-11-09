#include "../documentation/Mesa.hpp"
#include <iostream>
#include "../documentation/tipos.hpp"

Mesa::Mesa(const int id,const int numero,const int capacidade,const StatusMesa status) : id(id), numero(numero), capacidade(capacidade), status(status) {}

int Mesa::getId() const{
    return id;
}

int Mesa::getNumero() const{
    return numero;
}

int Mesa::getCapacidade() const{
    return capacidade;
}

StatusMesa Mesa::getStatus() const{
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

void Mesa::setStatus(const StatusMesa status){
    this->status = status;
}

void Mesa::ocupar(Mesa& Mesa){
    Mesa = StatusMesa::OCUPADA;
}

void Mesa::liberar(Mesa& Mesa){
    Mesa = StatusMesa::LIVRE;
}
