#ifndef JOGADOR_H
#define JOGADOR_H

#include "Treinador.h"

class Jogador : public Treinador {
public:
    Jogador(std::string n);
    int escolherGolpe(Pokemon& adversario);
};

#endif