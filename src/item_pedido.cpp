#include "../documentation/item_pedido.hpp"

item_pedido::ItemPedido(int id, 
        const Produto& produto, 
        int quantidade, 
        double precoUnitario, 
        const std::string& observacoes = "")
item_pedido::~ItemPedido()

int item_pedido::getId() const{
    return id;
}
const Produto& item_pedido::getProduto() const{
    return produto;
}
int item_pedido::getQuantidade() const{
    return quantidade;
}
double item_pedido::getPrecoUnitario() const{
    return precoUnitario;
}
std::string item_pedido::getObservacoes() const{
    return observacoes;
}
StatusItemPedido item_pedido::getStatus() const{
    return status;
}

void item_pedido::setQuantidade(int quantidade){}
void item_pedido::setObservacoes(const std::string& observacoes){}
void item_pedido::setStatus(StatusItemPedido status){}

double item_pedido::calcularSubtotal() const{}
bool item_pedido::podeSerCancelado() const{}