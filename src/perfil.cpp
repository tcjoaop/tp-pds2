#include "../documentation/perfil.hpp"

Perfil::Perfil(const int id, const std::string& nome, const std::vector<std::string>& permissoes) : id(id), nome(nome), permissoes(permissoes) {}

int Perfil::getId() const {
    return id;
}

std::string Perfil::getNome() const {
    return nome;
}

std::vector<std::string> Perfil::getPermissoes() const {
    return permissoes;
}

void Perfil::adicionarPermissao(const std::string& permissao){}
void Perfil::removerPermissao(const std::string& permissao){}
bool Perfil::possuiPermissao(const std::string& permissao) const{}