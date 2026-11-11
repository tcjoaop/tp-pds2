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

        {"preco", produto.getPreco()},

        {"disponivel", produto.getDisponivel()},

        {"tempoPreparo", produto.getTempoPreparo()}

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



    int mesaId = (pedido.getMesa() != nullptr) ? pedido.getMesa()->getId() : -1;



    json pedidoJson = {

        {"id", pedido.getId()},

        {"dataHoraAbertura", "2026-11-10 12:00:00"},

        {"mesaId", mesaId},

        {"status", static_cast<int>(pedido.getStatus())},

        {"itens", json::array()},
        {"pagamentos", json::array()}

    };



    for (const auto& item : pedido.getItens()) {

        json itemJson = {

            {"id", item.getId()},

            {"produtoId", item.getProduto().getId()},

            {"produtoNome", item.getProduto().getNome()},

            {"quantidade", item.getQuantidade()},

            {"precoUnitario", item.getPrecoUnitario()},

            {"observacoes", item.getObservacoes()},

            {"status", static_cast<int>(item.getStatus())}

        };

        pedidoJson["itens"].push_back(itemJson);
    }

    for (const auto& pag : pedido.getPagamentos()) {
        json pagJson = {
            {"id", pag.getId()},
            {"formaPagamento", static_cast<int>(pag.getFormaPagamento())},
            {"valor", pag.getValor()},
            {"dataHoraPagamento", pag.getDataHoraPagamento()}
        };
        pedidoJson["pagamentos"].push_back(pagJson);

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

        bool disponivel = u.contains("disponivel") ? u["disponivel"].get<bool>() : true;

        int tempoPreparo = u.contains("tempoPreparo") ? u["tempoPreparo"].get<int>() : 0;

        Produto produto(u["id"].get<int>(),

                        u["nome"].get<std::string>(),

                        u["preco"].get<int>(),

                        disponivel,

                        tempoPreparo);

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

        std::string dataHora = u.contains("dataHoraAbertura") ? u["dataHoraAbertura"].get<std::string>() : "N/A";

        int mId = u.contains("mesaId") ? u["mesaId"].get<int>() : -1;

        Mesa* mesaPtr = (mId != -1) ? buscarMesaPorId(mId) : nullptr;



        Pedido pedido(u["id"].get<int>(), dataHora, nullptr, mesaPtr);

        if (u.contains("status")) {

            pedido.alterarStatus(static_cast<StatusPedido>(u["status"].get<int>()));

        }



        if (u.contains("itens")) {

            for (const auto& ij : u["itens"]) {

                Produto prod(ij["produtoId"].get<int>(),

                             ij.contains("produtoNome") ? ij["produtoNome"].get<std::string>() : "Produto",

                             static_cast<int>(ij["precoUnitario"].get<double>()),

                             true,

                             15);

                ItemPedido item(ij["id"].get<int>(),

                                prod,

                                ij["quantidade"].get<int>(),

                                ij["precoUnitario"].get<double>(),

                                ij.contains("observacoes") ? ij["observacoes"].get<std::string>() : "");

                if (ij.contains("status")) {

                    item.setStatus(static_cast<StatusItemPedido>(ij["status"].get<int>()));

                }

                pedido.adicionarItem(item);

            }

        }

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

            PerfilAcesso perfil = static_cast<PerfilAcesso>(u["perfil"].get<int>());
            int id = u["id"].get<int>();
            std::string nome = u["nome"].get<std::string>();
            std::string log = u["login"].get<std::string>();
            std::string sen = u["senha"].get<std::string>();

            switch (perfil) {
                case PerfilAcesso::ADMINISTRADOR:
                    return new Administrador(id, nome, log, sen);
                case PerfilAcesso::GARCOM:
                    return new Garcom(id, nome, log, sen);
                case PerfilAcesso::COZINHEIRO:
                    return new Cozinheiro(id, nome, log, sen);
                case PerfilAcesso::CAIXA:
                    return new Caixa(id, nome, log, sen);
                default:
                    return new Usuario(id, nome, log, sen, perfil);
            }

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

            bool disponivel = u.contains("disponivel") ? u["disponivel"].get<bool>() : true;

            int tempoPreparo = u.contains("tempoPreparo") ? u["tempoPreparo"].get<int>() : 0;

            Produto* produto = new Produto(u["id"].get<int>(),

                                            u["nome"].get<std::string>(),

                                            u["preco"].get<int>(),

                                            disponivel,

                                            tempoPreparo);

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

            std::string dataHora = u.contains("dataHoraAbertura") ? u["dataHoraAbertura"].get<std::string>() : "N/A";

            int mId = u.contains("mesaId") ? u["mesaId"].get<int>() : -1;

            Mesa* mesaPtr = (mId != -1) ? buscarMesaPorId(mId) : nullptr;



            Pedido* pedido = new Pedido(u["id"].get<int>(), dataHora, nullptr, mesaPtr);

            if (u.contains("status")) {

                pedido->alterarStatus(static_cast<StatusPedido>(u["status"].get<int>()));

            }



            if (u.contains("itens")) {

                for (const auto& ij : u["itens"]) {

                    Produto prod(ij["produtoId"].get<int>(),

                                 ij.contains("produtoNome") ? ij["produtoNome"].get<std::string>() : "Produto",

                                 static_cast<int>(ij["precoUnitario"].get<double>()),

                                 true,

                                 15);

                    ItemPedido item(ij["id"].get<int>(),

                                    prod,

                                    ij["quantidade"].get<int>(),

                                    ij["precoUnitario"].get<double>(),

                                    ij.contains("observacoes") ? ij["observacoes"].get<std::string>() : "");

                    if (ij.contains("status")) {

                        item.setStatus(static_cast<StatusItemPedido>(ij["status"].get<int>()));

                    }

                    pedido->adicionarItem(item);

                }

            }

            if (u.contains("pagamentos")) {
                for (const auto& pj : u["pagamentos"]) {
                    Pagamento pag(pj["id"].get<int>(),
                                  static_cast<FormaPagamento>(pj["formaPagamento"].get<int>()),
                                  pj["valor"].get<double>());
                    pedido->adicionarPagamento(pag);
                }
            }
            return pedido;

        }

    }



    return nullptr;

}

