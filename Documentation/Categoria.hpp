#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP
#include <string>
#include "Produto.hpp"

class Usuario {
private:
    int id;
    std::string nome;
    std::string descricao;

public:
    Categoria(const int id,const std::string& numero,const std::string& descricao);
    
    int getId() const;
    int getNome() const;
    int getDescricao() const;
   
    void setId(const int id);
    void setNome(const std::string& nome);
    void setDescricao(const std::string& descricao);  
};

#endif