#include "treinadores/Treinador.h"
#include "Excecoes.h"
#include <iostream>

Treinador::Treinador(std::string n, int pocoes, int pokebolas) : mochila(pocoes, pokebolas) {
    nome = n;
    atual = 0;
}

void Treinador::adicionarPokemon(Pokemon p) {
    if (equipe.size() >= 6) {
        throw EquipeCheiaException();
    }
    equipe.push_back(p);
}

Pokemon& Treinador::getPokemonAtual() {
    return equipe[atual];
}

bool Treinador::temPokemonVivo() {
    for (int i = 0; i < equipe.size(); i++) {
        if (!equipe[i].estaDesmaiado()) {
            return true;
        }
    }
    return false;
}

void Treinador::trocarParaProximo() {
    // lambda que diz se um Pokemon ainda pode lutar
    auto podeLutar = [](Pokemon p) {
        return !p.estaDesmaiado();
    };

    for (int i = 0; i < equipe.size(); i++) {
        if (podeLutar(equipe[i])) {
            atual = i;
            return;
        }
    }
}

void Treinador::curarEquipe() {
    for (int i = 0; i < equipe.size(); i++) {
        equipe[i].curarTotalmente();
    }
}

void Treinador::mostrarEquipe() {
    for (int i = 0; i < equipe.size(); i++) {
        std::cout << i + 1 << " - " << equipe[i].getNome()
                  << " (" << tipoParaString(equipe[i].getTipo()) << ") "
                  << "Nv." << equipe[i].getNivel()
                  << " HP: " << equipe[i].getHpAtual() << "/" << equipe[i].getHpMax()
                  << std::endl;
    }
}

Mochila& Treinador::getMochila() {
    return mochila;
}

std::string Treinador::getNome() {
    return nome;
}