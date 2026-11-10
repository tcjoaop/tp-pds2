#include "../documentation/item_pedido.hpp"

ItemPedido::ItemPedido(int id, 
        const Produto& produto, 
        int quantidade, 
        double precoUnitario, 
        const std::string& observacoes) : id(id), produto(new Produto(produto)), quantidade(quantidade), precoUnitario(precoUnitario), observacoes(observacoes), status(StatusItemPedido::PENDENTE) {}

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
    if(quantidade > 0){
        this->quantidade = quantidade;
    }
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