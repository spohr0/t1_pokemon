#ifndef BATALHA_H
#define BATALHA_H

#include "Enums.h"
#include "treinadores/Jogador.h"
#include "treinadores/TreinadorNPC.h"

class Batalha {
private:
    Jogador& jogador;
    TreinadorNPC& oponente;
    bool selvagem;   //true = Pokemon selvagem (pode capturar e fugir)

    int calcularDano(Pokemon& atacante, Pokemon& defensor, Golpe golpe);
    void atacar(Pokemon& atacante, Pokemon& defensor, Golpe golpe);
    void oponenteAtaca();
    void mostrarStatus();

public:
    Batalha(Jogador& j, TreinadorNPC& o, bool ehSelvagem);
    ResultadoBatalha executar();
};

#endif