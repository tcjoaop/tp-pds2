#include <iostream>
#include <vector>
#include <string>
#include "../documentation/banco_dados.hpp"
#include "../documentation/autenticacao.hpp"
#include "../documentation/sistema_restaurante.hpp"
#include "../documentation/usuario.hpp"
#include "../documentation/perfil.hpp"

int main() {
    SistemaRestaurante sistema("banco_dados.json");
    if (!sistema.inicializar()) {
        std::cerr << "Falha ao inicializar o sistema." << std::endl;
        return 1;
    }
    sistema.executar();
    return 0;
}