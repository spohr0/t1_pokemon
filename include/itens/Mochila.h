#ifndef MOCHILA_H
#define MOCHILA_H

#include "Pocao.h"
#include "Pokebola.h"

class Mochila {
private:
    Pocao pocao;
    Pokebola pokebola;

public:
    Mochila(int qtdPocoes, int qtdPokebolas);

    bool usarPocao(Pokemon& alvo);
    bool usarPokebola(Pokemon& alvo);
    int getQuantidadePocoes();
    void mostrar();
};

#endif  