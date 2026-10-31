#include "Pokemon.h"
#include "Excecoes.h"

Pokemon::Pokemon(std::string nome, Tipo tipo, int nivel, int hpMax, int ataque, int defesa,
                 int ataqueEspecial, int defesaEspecial, int velocidade) {
    this->nome = nome;
    this->tipo = tipo;
    this->nivel = nivel;
    this->hpMax = hpMax;
    this->hpAtual = hpMax;   //comeca com HP cheio
    this->ataque = ataque;
    this->defesa = defesa;
    this->ataqueEspecial = ataqueEspecial;
    this->defesaEspecial = defesaEspecial;
    this->velocidade = velocidade;
}

void Pokemon::adicionarGolpe(Golpe golpe) {
    if (golpes.size() >= 4) {
        throw PokemonException(nome + " ja sabe 4 golpes!");
    }
    golpes.push_back(golpe);
}

void Pokemon::receberDano(int dano) {
    hpAtual = hpAtual - dano;
    if (hpAtual < 0) {
        hpAtual = 0;   //HP nunca fica negativo
    }
}

void Pokemon::curar(int quantidade) {
    if (estaDesmaiado()) {
        throw PokemonDesmaiadoException(nome);
    }
    if (hpAtual == hpMax) {
        throw PokemonException(nome + " ja esta com o HP cheio!");
    }
    hpAtual = hpAtual + quantidade;
    if (hpAtual > hpMax) {
        hpAtual = hpMax;   //HP nunca passa do maximo
    }
}

void Pokemon::curarTotalmente() {
    hpAtual = hpMax;
}

bool Pokemon::estaDesmaiado() {
    return hpAtual == 0;
}

Golpe Pokemon::getGolpe(int indice) {
    int total = golpes.size();
    if (indice < 0 || indice >= total) {
        throw EntradaInvalidaException("golpe inexistente");
    }
    return golpes[indice];
}

int Pokemon::getQuantidadeGolpes() { return golpes.size(); }

std::string Pokemon::getNome() { return nome; }
Tipo Pokemon::getTipo() { return tipo; }
int Pokemon::getNivel() { return nivel; }
int Pokemon::getHpMax() { return hpMax; }
int Pokemon::getHpAtual() { return hpAtual; }
int Pokemon::getAtaque() { return ataque; }
int Pokemon::getDefesa() { return defesa; }
int Pokemon::getAtaqueEspecial() { return ataqueEspecial; }
int Pokemon::getDefesaEspecial() { return defesaEspecial; }
int Pokemon::getVelocidade() { return velocidade; }