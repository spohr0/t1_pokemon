#include "Excecoes.h"

PokemonException::PokemonException(std::string mensagem)
    : std::runtime_error(mensagem) {}

PokemonDesmaiadoException::PokemonDesmaiadoException(std::string nomePokemon)
    : PokemonException(nomePokemon + " esta desmaiado!") {}

EquipeCheiaException::EquipeCheiaException()
    : PokemonException("A equipe ja tem 6 Pokemon!") {}

ItemIndisponivelException::ItemIndisponivelException(std::string motivo)
    : PokemonException(motivo) {}

EntradaInvalidaException::EntradaInvalidaException(std::string motivo)
    : PokemonException("Entrada invalida: " + motivo) {}