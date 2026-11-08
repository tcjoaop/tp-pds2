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

void Perfil::adicionarPermissao(const std::string& permissao){
    for(int i = 0; i < permissoes.size(); i++){
        if(permissoes[i] == permissao){
            return;
        }
    }
    permissoes.push_back(permissao);
}
void Perfil::removerPermissao(const std::string& permissao){
    for(int i = 0; i < permissoes.size(); i++){
        if(permissoes[i] == permissao){
            permissoes.erase(permissoes.begin() + i);
            return;
        }
    }
}
bool Perfil::possuiPermissao(const std::string& permissao) const{
    for(int i = 0; i < permissoes.size(); i++){
        if(permissoes[i] == permissao){
            return true;
        }
    }
    return false;
}
