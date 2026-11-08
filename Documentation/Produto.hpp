#ifndef PRODUTO_HPP
#define PRODUTO_HPP
#include <string>
#include "Categoria.hpp"

class Produto {
private:
    int id;
    std::string nome;
    int preco;
    bool disponivel;
    int tempoPreparo;

public:
    Produto(const int id,const std::string& nome,const int preco,const bool disponivel, const int tempoPreparo);
    
    int getId() const;
    std::string getNome() const;
    int getPreco() const;
    bool getDisponivel() const;
    int getTempoPreparo() const;
   
    void setId(const int id);
    void setNome(const std::string& nome);
    void setPreco(const int preco);
    void setDisponivel(const bool disponivel);
    void setTempoPreparo(const int tempoPreparo);
};

#endif