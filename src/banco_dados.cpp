#include "../documentation/banco_dados.hpp"
#include "../documentation/usuario.hpp"
#include "../documentation/produto.hpp"
#include "../documentation/mesa.hpp"
#include "../documentation/pedido.hpp"
#include "../documentation/json.hpp"
#include <fstream>
#include <string>
#include <vector>

using json = nlohmann::json;

BancoDados::BancoDados(const std::string& caminhoArquivo) : caminhoArquivo(caminhoArquivo){}

BancoDados::~BancoDados() {
    desconectar();
}

bool BancoDados::conectar() {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return false;
    }
    return true;
}

void BancoDados::desconectar() {

}

bool BancoDados::estaConectado() const {
    std::ifstream arquivo(caminhoArquivo);
    return arquivo.is_open();
}

bool BancoDados::criarEstruturaInicial() {
    json estruturaInicial = {
        {"usuarios", json::array()},
        {"produtos", json::array()},
        {"mesas", json::array()},
        {"pedidos", json::array()}
    };

    std::ofstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    arquivo << estruturaInicial.dump(4);
    arquivo.close();
    return true;
}

bool BancoDados::salvarUsuario(const Usuario& usuario) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    json dados;
    arquivo >> dados;
    arquivo.close();

    json usuarioJson = {
        {"nome", usuario.getNome()},
        {"login", usuario.getLogin()},
        {"senha", usuario.getSenha()}
    };

    dados["usuarios"].push_back(usuarioJson);

    std::ofstream arquivoSaida(caminhoArquivo);
    if (!arquivoSaida.is_open()) {
        return false;
    }

    arquivoSaida << dados.dump(4);
    arquivoSaida.close();
    return true;
}

bool BancoDados::salvarProduto(const Produto& produto) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    json dados;
    arquivo >> dados;
    arquivo.close();

    json produtoJson = {
        {"id", produto.getId()},
        {"nome", produto.getNome()},
        {"preco", produto.getPreco()}
    };

    dados["produtos"].push_back(produtoJson);

    std::ofstream arquivoSaida(caminhoArquivo);
    if (!arquivoSaida.is_open()) {
        return false;
    }

    arquivoSaida << dados.dump(4);
    arquivoSaida.close();
    return true;
}

bool BancoDados::salvarMesa(const Mesa& mesa) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    json dados;
    arquivo >> dados;
    arquivo.close();

    json mesaJson = {
        {"id", mesa.getId()},
        {"numero", mesa.getNumero()},
        {"capacidade", mesa.getCapacidade()}
    };

    dados["mesas"].push_back(mesaJson);

    std::ofstream arquivoSaida(caminhoArquivo);
    if (!arquivoSaida.is_open()) {
        return false;
    }

    arquivoSaida << dados.dump(4);
    arquivoSaida.close();
    return true;
}

bool BancoDados::salvarPedido(const Pedido& pedido) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return false;
    }

    json dados;
    arquivo >> dados;
    arquivo.close();

    json pedidoJson = {
        {"id", pedido.getId()},
        {"mesaId", pedido.getMesa().getId()},
        {"produtos", json::array()}
    };

    for (const auto& produto : pedido.getProdutos()) {
        json produtoJson = {
            {"id", produto.getId()},
            {"quantidade", produto.getQuantidade()}
        };
        pedidoJson["produtos"].push_back(produtoJson);
    }

    dados["pedidos"].push_back(pedidoJson);

    std::ofstream arquivoSaida(caminhoArquivo);
    if (!arquivoSaida.is_open()) {
        return false;
    }

    arquivoSaida << dados.dump(4);
    arquivoSaida.close();
    return true;
}
