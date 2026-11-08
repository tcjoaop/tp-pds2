#include "../documentation/autenticacao.hpp"
#include "../documentation/banco_dados.hpp"

Autenticacao::Autenticacao(BancoDados& bancoDados) : bancoDados(bancoDados), usuarioLogado(nullptr) {}

Autenticacao::~Autenticacao() {
    logout();
}

bool Autenticacao::login(const std::string& login, const std::string& senha) {
    if (estaLogado()) {
        return false; // Já está logado
    }

    Usuario* usuario = bancoDados.buscarUsuarioPorLogin(login);
    if (usuario && validarSenha(senha, usuario->getSenha())) {
        usuarioLogado = usuario;
        return true; // Login bem-sucedido
    }

    return false; // Login falhou
}

bool Autenticacao::estaLogado() const {
    return usuarioLogado != nullptr;
}

Usuario* Autenticacao::getUsuarioLogado() const {
    return usuarioLogado;
}

bool Autenticacao::possuiPermissao(const std::string& permissao) const {
    if (!estaLogado()) {
        return false; // Nenhum usuário logado
    }

    Perfil perfil = usuarioLogado->getPerfil();
    return perfil.possuiPermissao(permissao);
}

std::string Autenticacao::hashSenha(const std::string& senha) const {
    // Implementação de hash de senha (exemplo simples)
    std::hash<std::string> hasher;
    return std::to_string(hasher(senha));
}

bool Autenticacao::validarSenha(const std::string& senha, const std::string& hash) const {
    return hashSenha(senha) == hash;
}

void Autenticacao::logout() {
    usuarioLogado = nullptr;
}