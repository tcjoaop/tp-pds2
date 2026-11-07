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
   
    void setId(const int id);
    void setNumero(const int numero);
    void setCapacidade(const int capacidade);
    void setStatus(const int status);

    void ocupar(Mesa& Mesa);
    void liberar(Mesa& Mesa);

};

#endif