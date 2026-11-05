#include <iostream>
#include "../documentation/cliente.hpp"

int main(){

    Cliente cliente1(1, "João", "123456789");

    std::cout << "ID: " << cliente1.getId() << std::endl;
    std::cout << "Nome: " << cliente1.getNome() << std::endl;

    return 0;
}