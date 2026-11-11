#include "../documentation/mesa.hpp"
#include <iostream>
#include <stdexcept>
#include "../documentation/tipos.hpp"

Mesa::Mesa(const int id, const int numero, const int capacidade, const StatusMesa status) {
    if (id <= 0) {
        throw std::invalid_argument("ID da mesa deve ser positivo.");
    }
    if (numero <= 0) {
        throw std::invalid_argument("Numero da mesa deve ser positivo.");
    }
    if (capacidade <= 0) {
        throw std::invalid_argument("Capacidade da mesa deve ser maior que zero.");
    }
    this->id = id;
    this->numero = numero;
    this->capacidade = capacidade;
    this->status = status;
}

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
    if (id <= 0) {
        throw std::invalid_argument("ID da mesa deve ser positivo.");
    }
    this->id = id;
}

void Mesa::setNumero(const int numero){
    if (numero <= 0) {
        throw std::invalid_argument("Numero da mesa deve ser positivo.");
    }
    this->numero = numero;
}

void Mesa::setCapacidade(const int capacidade){
    if (capacidade <= 0) {
        throw std::invalid_argument("Capacidade da mesa deve ser maior que zero.");
    }
    this->capacidade = capacidade;
}

void Mesa::setStatus(const StatusMesa status){
    this->status = status;
}

void Mesa::ocupar([[maybe_unused]] Mesa& Mesa){
    if (this->status == StatusMesa::OCUPADA) {
        throw std::runtime_error("A mesa ja esta ocupada.");
    }
    this->status = StatusMesa::OCUPADA;
}

void Mesa::liberar([[maybe_unused]] Mesa& Mesa){
    this->status = StatusMesa::LIVRE;
}
