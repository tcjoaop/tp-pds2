#include "../documentation/item_pedido.hpp"
#include <stdexcept>

ItemPedido::ItemPedido(int id, 
        const Produto& produto, 
        int quantidade, 
        double precoUnitario, 
        const std::string& observacoes) {
    if (id <= 0) {
        throw std::invalid_argument("ID do item do pedido deve ser positivo.");
    }
    if (quantidade <= 0) {
        throw std::invalid_argument("Quantidade de itens deve ser maior que zero.");
    }
    if (precoUnitario < 0.0) {
        throw std::invalid_argument("Preco unitario nao pode ser negativo.");
    }
    this->id = id;
    this->produto = new Produto(produto);
    this->quantidade = quantidade;
    this->precoUnitario = precoUnitario;
    this->observacoes = observacoes;
    this->status = StatusItemPedido::PENDENTE;
}

ItemPedido::ItemPedido(const ItemPedido& outro)
    : id(outro.id),
      produto(outro.produto ? new Produto(*outro.produto) : nullptr),
      quantidade(outro.quantidade),
      precoUnitario(outro.precoUnitario),
      observacoes(outro.observacoes),
      status(outro.status) {}

ItemPedido& ItemPedido::operator=(const ItemPedido& outro) {
    if (this != &outro) {
        delete produto;
        id = outro.id;
        produto = outro.produto ? new Produto(*outro.produto) : nullptr;
        quantidade = outro.quantidade;
        precoUnitario = outro.precoUnitario;
        observacoes = outro.observacoes;
        status = outro.status;
    }
    return *this;
}

ItemPedido::~ItemPedido(){
    delete produto;
}

int ItemPedido::getId() const{
    return id;
}
const Produto& ItemPedido::getProduto() const{
    return *produto;
}
int ItemPedido::getQuantidade() const{
    return quantidade;
}
double ItemPedido::getPrecoUnitario() const{
    return precoUnitario;
}
std::string ItemPedido::getObservacoes() const{
    return observacoes;
}
StatusItemPedido ItemPedido::getStatus() const{
    return status;
}

void ItemPedido::setQuantidade(int quantidade){
    if (quantidade <= 0) {
        throw std::invalid_argument("Quantidade de itens deve ser maior que zero.");
    }
    this->quantidade = quantidade;
}
void ItemPedido::setObservacoes(const std::string& observacoes){
    this->observacoes = observacoes;
}
void ItemPedido::setStatus(StatusItemPedido status){
    this->status = status;
}

double ItemPedido::calcularSubtotal() const{
    return quantidade * precoUnitario;
}
bool ItemPedido::podeSerCancelado() const{
    if ((status == StatusItemPedido::PENDENTE)||(status == StatusItemPedido::ENVIADO_COZINHA)){
        return true;
    } else {
        return false;
    }
}