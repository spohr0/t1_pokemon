#include "treinadores/TreinadorNPC.h"
#include "TabelaTipos.h"

//NPC comeca com 2 pocoes e nenhuma pokebola
TreinadorNPC::TreinadorNPC(std::string n) : Treinador(n, 2, 0) {
}

//escolhe o golpe que causa mais dano contra o adversario
int TreinadorNPC::escolherGolpe(Pokemon& adversario) {
    Pokemon& meu = getPokemonAtual();
    int melhor = 0;
    double maiorForca = 0;

    for (int i = 0; i < meu.getQuantidadeGolpes(); i++) {
        Golpe g = meu.getGolpe(i);
        double forca = g.getPoder() * TabelaTipos::calcularMultiplicador(g.getTipo(), adversario.getTipo());
        if (forca > maiorForca) {
            maiorForca = forca;
            melhor = i;
        }
    }
    return melhor;
}