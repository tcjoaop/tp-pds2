#include "../documentation/banco_dados.hpp"
#include "../documentation/usuario.hpp"
#include "../documentation/produto.hpp"
#include "../documentation/mesa.hpp"
#include "../documentation/pedido.hpp"
#include "../documentation/json.hpp"
#include "../documentation/tipos.hpp"
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
    std::ifstream arquivo(caminhoArquivo);
    if (arquivo.is_open()) {
        arquivo.close();
    }
}

bool BancoDados::estaConectado() const {
    std::ifstream arquivo(caminhoArquivo);
    return arquivo.is_open();
}

bool BancoDados::criarEstruturaInicial() {

    std::ifstream arquivo(caminhoArquivo);
    if (arquivo.is_open()) {
        arquivo.close();
        return false; // O arquivo já existe, não criar a estrutura inicial
    }

    json estruturaInicial = {
        {"usuarios", json::array()},
        {"produtos", json::array()},
        {"mesas", json::array()},
        {"pedidos", json::array()}
    };

    std::ofstream NovoArquivo(caminhoArquivo);
    if (!NovoArquivo.is_open()) {
        return false;
    }

    NovoArquivo << estruturaInicial.dump(4);
    NovoArquivo.close();
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
        {"id", usuario.getId()},
        {"login", usuario.getLogin()},
        {"senha", usuario.getSenha()},
        {"perfil", static_cast<int>(usuario.getPerfil())}
    };

    bool encontrado = false;

    for (auto& u : dados["usuarios"]) {
        if (u["id"] == usuario.getId()) {
            u = usuarioJson;
            encontrado = true;
            break;
        }
    }

    if(!encontrado) {
        // Adicionar novo usuário
        dados["usuarios"].push_back(usuarioJson);
    }

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

    bool encontrado = false;

    for (auto& u : dados["produtos"]) {
        if (u["id"] == produto.getId()) {
            u = produtoJson;
            encontrado = true;
            break;
        }
    }

    if(!encontrado) {
        // Adicionar novo produto
        dados["produtos"].push_back(produtoJson);
    }

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
        {"capacidade", mesa.getCapacidade()},
        {"status", static_cast<int>(mesa.getStatus())}
    };

    bool encontrado = false;

    for (auto& u : dados["mesas"]) {
        if (u["id"] == mesa.getId()) {
            u = mesaJson;
            encontrado = true;
            break;
        }
    }

    if(!encontrado) {
        // Adicionar nova mesa
        dados["mesas"].push_back(mesaJson);
    }

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
        {"mesaId", pedido.getMesa()->getId()},
        {"produtos", json::array()}
    };

    for (const auto& item : pedido.getItens()) {
        json produtoJson = {
            {"id", item.getId()},
            {"quantidade", item.getQuantidade()}
        };
        pedidoJson["produtos"].push_back(produtoJson);
    }

    bool encontrado = false;

    for (auto& u : dados["pedidos"]) {
        if (u["id"] == pedido.getId()) {
            u = pedidoJson;
            encontrado = true;
            break;
        }
    }

    if(!encontrado) {
        // Adicionar novo pedido
        dados["pedidos"].push_back(pedidoJson);
    }

    std::ofstream arquivoSaida(caminhoArquivo);
    if (!arquivoSaida.is_open()) {
        return false;
    }

    arquivoSaida << dados.dump(4);
    arquivoSaida.close();
    return true;
}

std::vector<Produto> BancoDados::listarProdutos() {
    std::vector<Produto> produtos;
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return produtos;
    }

    json dados;
    arquivo >> dados;
    arquivo.close();

    for (const auto& u : dados["produtos"]) {
        Produto produto(u["id"].get<int>(),
                        u["nome"].get<std::string>(),
                        u["preco"].get<int>(),
                        u["disponivel"].get<bool>(),
                        u["tempoPreparo"].get<int>());
        produtos.push_back(produto);
    }

    return produtos;
}

std::vector<Mesa> BancoDados::listarMesas() {
    std::vector<Mesa> mesas;
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return mesas;
    }

    json dados;
    arquivo >> dados;
    arquivo.close();

    for (const auto& u : dados["mesas"]) {
        Mesa mesa(u["id"].get<int>(),
                  u["numero"].get<int>(),
                  u["capacidade"].get<int>(),
                  static_cast<StatusMesa>(u["status"].get<int>()));
        mesas.push_back(mesa);
    }

    return mesas;
}

std::vector<Pedido> BancoDados::listarPedidos() {
    std::vector<Pedido> pedidos;
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return pedidos;
    }

    json dados;
    arquivo >> dados;
    arquivo.close();

    for (const auto& u : dados["pedidos"]) {
        Pedido pedido(u["id"].get<int>(),
                      u["dataHoraAbertura"].get<std::string>());
        pedidos.push_back(pedido);
    }

    return pedidos;
}

Usuario* BancoDados::buscarUsuarioPorLogin(const std::string& login) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return nullptr;
    }

    json dados;
    arquivo >> dados;
    arquivo.close();

    for (const auto& u : dados["usuarios"]) {
        if (u["login"] == login) {
            Usuario* usuario = new Usuario(u["id"].get<int>(),
                                           u["nome"].get<std::string>(),
                                           u["login"].get<std::string>(),
                                           u["senha"].get<std::string>(),
                                           static_cast<PerfilAcesso>(u["perfil"].get<int>()));
            return usuario;
        }
    }

    return nullptr;
}

Produto* BancoDados::buscarProdutoPorId(int id) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return nullptr;
    }

    json dados;
    arquivo >> dados;
    arquivo.close();

    for (const auto& u : dados["produtos"]) {
        if (u["id"] == id) {
            Produto* produto = new Produto(u["id"].get<int>(),
                                            u["nome"].get<std::string>(),
                                            u["preco"].get<int>(),
                                            u["disponivel"].get<bool>(),
                                            u["tempoPreparo"].get<int>());
            return produto;
        }
    }

    return nullptr;
}

Mesa* BancoDados::buscarMesaPorId(int id) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return nullptr;
    }

    json dados;
    arquivo >> dados;
    arquivo.close();

    for (const auto& u : dados["mesas"]) {
        if (u["id"] == id) {
            Mesa* mesa = new Mesa(u["id"].get<int>(),
                                   u["numero"].get<int>(),
                                   u["capacidade"].get<int>(),
                                   static_cast<StatusMesa>(u["status"].get<int>()));
            return mesa;
        }
    }

    return nullptr;
}

Pedido* BancoDados::buscarPedidoPorId(int id) {
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        return nullptr;
    }

    json dados;
    arquivo >> dados;
    arquivo.close();

    for (const auto& u : dados["pedidos"]) {
        if (u["id"] == id) {
            Pedido* pedido = new Pedido(u["id"].get<int>(),
                                         u["dataHoraAbertura"].get<std::string>());
            return pedido;
        }
    }

    return nullptr;
}
