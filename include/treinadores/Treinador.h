#ifndef TREINADOR_H
#define TREINADOR_H

#include <string>
#include <vector>
#include "Pokemon.h"
#include "itens/Mochila.h"

class Treinador {
protected:
    std::string nome;
    std::vector<Pokemon> equipe;   //maximo 6
    Mochila mochila;
    int atual;                     //posicao do pokemon que esta lutando

public:
    Treinador(std::string n, int pocoes, int pokebolas);

    //cada treinador escolhe o golpe do seu jeito
    virtual int escolherGolpe(Pokemon& adversario) = 0;

    void adicionarPokemon(Pokemon p);
    Pokemon& getPokemonAtual();
    bool temPokemonVivo();
    void trocarParaProximo();
    void curarEquipe();
    void mostrarEquipe();
    Mochila& getMochila();
    std::string getNome();
};

#endif