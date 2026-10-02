#ifndef PRODUTO_HPP
#define PRODUTO_HPP
#include <string>
#include "Categoria.hpp"
#include "ItemPedido"

class Usuario {
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
   
    int setId(const int id);
    std::string setNome(const std::string& nome);
    int setPreco(const int preco);
    bool setDisponivel(const bool disponivel);
    int setTempoPreparo(const int tempoPreparo);
};

#endif