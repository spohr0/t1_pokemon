#ifndef TREINADORNPC_H
#define TREINADORNPC_H

#include "Treinador.h"

class TreinadorNPC : public Treinador {
public:
    TreinadorNPC(std::string n);
    int escolherGolpe(Pokemon& adversario);
};

#endif