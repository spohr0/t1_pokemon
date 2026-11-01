#include "Entrada.h"
#include "Excecoes.h"
#include <iostream>
#include <cstdlib>

int lerOpcao(int min, int max) {
    int opcao;
    std::cin >> opcao;

    if (std::cin.eof()) {           //a entrada acabou
        std::cout << "Saindo..." << std::endl;
        exit(0);
    }
    if (std::cin.fail()) {          //digitou letra em vez de numero
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        throw EntradaInvalidaException("digite um numero");
    }
    if (opcao < min || opcao > max) {
        throw EntradaInvalidaException("escolha entre " + std::to_string(min) + " e " + std::to_string(max));
    }
    return opcao;
}