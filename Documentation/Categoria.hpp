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
   
    int setId(const int id);
    std::string setNome(const std::string& nome);
    std::string setDescricao(const std::string& descricao);  
};

#endif