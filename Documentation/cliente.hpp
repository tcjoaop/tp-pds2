#ifndef CLIENTE_HPP
#define CLIENTE_HPP
#include <string>

class Cliente {
    private:
        int id;
        std::string nome;
        std::string telefone;
    
    public:
        Cliente(int id, const std::string& nome, const std::string& telefone);
        
        int getId() const;
        std::string getNome() const;
        std::string getTelefone() const;
        
        void setNome(const std::string& nome);
        void setTelefone(const std::string& telefone);

        int getId() const;
        std::string getNome() const;
        std::string getTelefone() const;
}

#endif