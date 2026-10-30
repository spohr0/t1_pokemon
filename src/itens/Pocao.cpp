#include "itens/Pocao.h"

Pocao::Pocao(std::string nome, int quantidade, int cura) : Item(nome, quantidade) {
    this->cura = cura;
}

bool Pocao::usar(Pokemon& alvo) {
    alvo.curar(cura);
    return true;
}