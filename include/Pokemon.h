#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include "Enums.h"
#include "Golpe.h"

class Pokemon {
private:
    std::string nome;
    Tipo tipo;
    int nivel;
    int hpMax;
    int hpAtual;
    int ataque;
    int defesa;
    int ataqueEspecial;
    int defesaEspecial;
    int velocidade;
    std::vector<Golpe> golpes;   //maximo 4

public:
    Pokemon(std::string nome, Tipo tipo, int nivel, int hpMax, int ataque, int defesa,
            int ataqueEspecial, int defesaEspecial, int velocidade);

    void adicionarGolpe(Golpe golpe);
    void receberDano(int dano);
    void curar(int quantidade);
    void curarTotalmente();
    bool estaDesmaiado();

    Golpe getGolpe(int indice);
    int getQuantidadeGolpes();

    std::string getNome();
    Tipo getTipo();
    int getNivel();
    int getHpMax();
    int getHpAtual();
    int getAtaque();
    int getDefesa();
    int getAtaqueEspecial();
    int getDefesaEspecial();
    int getVelocidade();
};

#endif