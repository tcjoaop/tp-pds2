#include "../documentation/autenticacao.hpp"
#include "../documentation/banco_dados.hpp"

Autenticacao::Autenticacao(BancoDados& bancoDados) : bancoDados(bancoDados), usuarioLogado(nullptr) {}

Autenticacao::~Autenticacao() {
    logout();
}

bool Autenticacao::login(const std::string& login, const std::string& senha) {
    if (estaLogado()) {
        return false; // Ja esta logado
    }

    Usuario* usuario = bancoDados.buscarUsuarioPorLogin(login);
    if (usuario && validarSenha(senha, usuario->getSenha())) {
        usuarioLogado = usuario;
        return true; // Login bem-sucedido
    }

    delete usuario; // Se falhou a validacao, desaloca a busca
    return false;   // Login falhou
}

bool Autenticacao::estaLogado() const {
    return usuarioLogado != nullptr;
}

Usuario* Autenticacao::getUsuarioLogado() const {
    return usuarioLogado;
}

bool Autenticacao::possuiPermissao(PerfilAcesso perfilNecessario) const {
    if (!estaLogado()) {
        return false;
    }

    return usuarioLogado->podeAcessar(perfilNecessario);
}

std::string Autenticacao::hashSenha(const std::string& senha) const {
    std::hash<std::string> hasher;
    return std::to_string(hasher(senha));
}

bool Autenticacao::validarSenha(const std::string& senha, const std::string& hash) const {
    return hashSenha(senha) == hash;
}

void Autenticacao::logout() {
    if (usuarioLogado) {
        delete usuarioLogado;
        usuarioLogado = nullptr;
    }
}
