#include "itens/Mochila.h"
#include "Excecoes.h"
#include <iostream>
#include "itens/Mochila.h"
#include <iostream>

Mochila::Mochila(int qtdPocoes, int qtdPokebolas)
    : pocao("Pocao", qtdPocoes, 20), pokebola(qtdPokebolas) {
}

bool Mochila::usarPocao(Pokemon& alvo) {
    if (pocao.getQuantidade() == 0) {
        throw ItemIndisponivelException("Voce nao tem mais Pocoes!");
    }
    bool resultado = pocao.usar(alvo);   //se o HP estiver cheio, lanca excecao e nao gasta
    pocao.consumir();
    return resultado;
}

bool Mochila::usarPokebola(Pokemon& alvo) {
    if (pokebola.getQuantidade() == 0) {
        throw ItemIndisponivelException("Voce nao tem mais Pokebolas!");
    }
    pokebola.consumir();             //a pokebola  gasta mesmo se o Pokemon escapar
    return pokebola.usar(alvo);
}

int Mochila::getQuantidadePocoes() {
    return pocao.getQuantidade();
}

void Mochila::mostrar() {
    std::cout << "1 - Pocao (x" << pocao.getQuantidade() << ")" << std::endl;
    std::cout << "2 - Pokebola (x" << pokebola.getQuantidade() << ")" << std::endl;
}