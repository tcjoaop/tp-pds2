#include "../documentation/Mesa.hpp"

Mesa::Mesa(const int id,const int numero,const int capacidade,const int status);
    
int Mesa::getId() const{}

int Mesa::getNumero() const{}

int Mesa::getCapacidade() const{}

int Mesa::getStatus() const{}
   
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

void Mesa::ocupar(Mesa& Mesa){}

void Mesa::liberar(Mesa& Mesa){}
