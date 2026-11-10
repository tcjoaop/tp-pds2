#ifndef MESA_HPP
#define MESA_HPP
#include "tipos.hpp"

class Mesa {
private:
    int id;
    int numero;
    int capacidade;
    StatusMesa status;

public:
    Mesa(const int id,const int numero,const int capacidade,const StatusMesa status);
    
    int getId() const;
    int getNumero() const;
    int getCapacidade() const;
    StatusMesa getStatus() const;
   
    void setId(const int id);
    void setNumero(const int numero);
    void setCapacidade(const int capacidade);
    void setStatus(const StatusMesa status);

    void ocupar(Mesa& Mesa);
    void liberar(Mesa& Mesa);

};

#endif
