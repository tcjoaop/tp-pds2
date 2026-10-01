#ifndef PERFIL_HPP
#define PERFIL_HPP
#include <string>
#include <vector>

class Perfil {
private:
    int id;
    std::string nome;
    std::vector<std::string> permissoes;

public:
    Perfil(int id, const std::string& nome, const std::vector<std::string>& permissoes);

    int getId() const;
    std::string getNome() const;
    std::vector<std::string> getPermissoes() const;

    void adicionarPermissao(const std::string& permissao);
    void removerPermissao(const std::string& permissao);
    bool possuiPermissao(const std::string& permissao) const;
};

#endif