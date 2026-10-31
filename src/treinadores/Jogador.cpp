#include "treinadores/Jogador.h"
#include "Excecoes.h"
#include <iostream>

//jogador comeca com 3 pocoes e 5 pokebolas
Jogador::Jogador(std::string n) : Treinador(n, 3, 5) {
}

int Jogador::escolherGolpe(Pokemon& adversario) {
    Pokemon& meu = getPokemonAtual();

    std::cout << "Escolha o golpe:" << std::endl;
    for (int i = 0; i < meu.getQuantidadeGolpes(); i++) {
        Golpe g = meu.getGolpe(i);
        std::cout << i + 1 << " - " << g.getNome()
                  << " (" << tipoParaString(g.getTipo()) << ", poder " << g.getPoder() << ")"
                  << std::endl;
    }

    int opcao;
    std::cin >> opcao;

    if (std::cin.fail()) {          //digitou letra em vez de numero
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        throw EntradaInvalidaException("digite um numero");
    }
    if (opcao < 1 || opcao > meu.getQuantidadeGolpes()) {
        throw EntradaInvalidaException("esse golpe nao existe");
    }
    return opcao - 1;   //o usuario digita 1, 2, 3... mas o vector comeca em 0
}