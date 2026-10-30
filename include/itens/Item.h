#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "Pokemon.h"

//classe base de todos os itens
class Item {
protected:
    std::string nome;
    int quantidade;

public:
    Item(std::string nome, int quantidade);
    virtual ~Item();

    //cada item implementa o seu: a pocao cura, a pokebola captura
    virtual bool usar(Pokemon& alvo) = 0;

    void adicionar(int qtd);
    void consumir();
    std::string getNome();
    int getQuantidade();
};

#endif