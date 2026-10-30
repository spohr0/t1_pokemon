#ifndef POCAO_H
#define POCAO_H

#include "Item.h"

class Pocao : public Item {
private:
    int cura;

public:
    Pocao(std::string nome, int quantidade, int cura);
    bool usar(Pokemon& alvo);
};

#endif