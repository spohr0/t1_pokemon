#ifndef JOGO_H
#define JOGO_H

#include <string>
#include "Enums.h"
#include "Pokemon.h"
#include "treinadores/Jogador.h"

class Jogo {
private:
    Jogador jogador;
    EstadoJogo estado;

    void escolherInicial();
    void andarNaGrama();
    void desafiarLider();
    void centroPokemon();
    void verEquipe();

public:
    Jogo(std::string nomeJogador);
    static Pokemon criarPokemon(std::string especie, int nivel);
    void executar();
};

#endif