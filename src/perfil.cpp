#include "../documentation/perfil.hpp"
#include <stdexcept>

Perfil::Perfil(const int id, const std::string& nome, const std::vector<std::string>& permissoes)
    : id(id), nome(nome), permissoes(permissoes) {
    if (id <= 0) {
        throw std::invalid_argument("ID do perfil deve ser positivo.");
    }
    if (nome.empty()) {
        throw std::invalid_argument("Nome do perfil nao pode ser vazio.");
    }
}

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
    if (permissao.empty()) {
        throw std::invalid_argument("Permissao nao pode ser vazia.");
    }
    for(size_t i = 0; i < permissoes.size(); i++){
        if(permissoes[i] == permissao){
            return;
        }
    }
    permissoes.push_back(permissao);
}
void Perfil::removerPermissao(const std::string& permissao){
    for(size_t i = 0; i < permissoes.size(); i++){
        if(permissoes[i] == permissao){
            permissoes.erase(permissoes.begin() + i);
            return;
        }
    }
}
bool Perfil::possuiPermissao(const std::string& permissao) const{
    for(size_t i = 0; i < permissoes.size(); i++){
        if(permissoes[i] == permissao){
            return true;
        }
    }
    return false;
}
