#ifndef EXCECOES_H
#define EXCECOES_H

#include <stdexcept>
#include <string>

//Excecao base do jogo
class PokemonException : public std::runtime_error {
public:
    PokemonException(std::string mensagem);
};

// Quando tenta usar ou trocar para um Pokemon sem HP
class PokemonDesmaiadoException : public PokemonException {
public:
    PokemonDesmaiadoException(std::string nomePokemon);
};

//Quando tenta colocar um 7o Pokemon na equipe
class EquipeCheiaException : public PokemonException {
public:
    EquipeCheiaException();
};

//item acabou ou nao pode ser usado agora
class ItemIndisponivelException : public PokemonException {
public:
    ItemIndisponivelException(std::string motivo);
};

//digita algo invalido
class EntradaInvalidaException : public PokemonException {
public:
    EntradaInvalidaException(std::string motivo);
};

#endif