#ifndef MESA_HPP
#define MESA_HPP
#include <string>
#include "Pedido.hpp"

class Usuario {
private:
    int id;
    int numero;
    int capacidade;
    int status;

public:
    Mesa(const int id,const int numero,const int capacidade,const int status);
    
    int getId() const;
    int getNumero() const;
    int getCapacidade() const;
    int getStatus() const;
   
    int setId(const int id);
    int setNumero(const int numero);
    int setCapacidade(const int capacidade);
    int setStatus(const int status);

    void ocupar(Mesa& Mesa);
    void liberar(Mesa& Mesa);

};

#endif