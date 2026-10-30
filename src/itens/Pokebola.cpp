#include "itens/Pokebola.h"
#include <cstdlib>

Pokebola::Pokebola(int quantidade) : Item("Pokebola", quantidade) {
}

bool Pokebola::usar(Pokemon& alvo) {
    int porcentagemHp = alvo.getHpAtual() * 100 / alvo.getHpMax();     //porcentagem de HP que o Pokemon ainda tem (0 a 100)


    //quanto menos HP, maior a chance
    //HP cheio = 10% | metade = 60% | quase zero = ~100%
    int chance = 110 - porcentagemHp;

    int sorteio = rand() % 100;   //numero de 0 a 99
    return sorteio < chance;
}