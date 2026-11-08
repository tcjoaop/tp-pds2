#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP
#include <string>
#include "produto.hpp"

class Categoria {
private:
    int id;
    std::string nome;
    std::string descricao;

public:
    Categoria(const int id,const std::string& nome,const std::string& descricao);
    
    int getId() const;
    std::string getNome() const;
    std::string getDescricao() const;
   
    void setId(const int id);
    void setNome(const std::string& nome);
    void setDescricao(const std::string& descricao);  
};

#endif