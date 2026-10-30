#ifndef POKEBOLA_H
#define POKEBOLA_H

#include "Item.h"

class Pokebola : public Item {
public:
    Pokebola(int quantidade);
    bool usar(Pokemon& alvo);
};

#endif