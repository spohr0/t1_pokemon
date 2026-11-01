#ifndef ENUMS_H
#define ENUMS_H

#include <string>

// Tipos elementais
enum class Tipo {
    NORMAL,
    FOGO,
    AGUA,
    PLANTA,
    ELETRICO
};

enum class CategoriaGolpe {
    FISICO,   // usa ataque / defesa
    ESPECIAL  // usa ataqueEspecial / defesaEspecial
};

// Estados do jogo
enum class EstadoJogo {
    MENU,
    VITORIA,
    DERROTA
};

// Como a batalha terminou
enum class ResultadoBatalha {
    VITORIA,
    DERROTA,
    FUGA,
    CAPTURA
};

// Converte o Tipo em texto para mostrar na tela
std::string tipoParaString(Tipo tipo);


#endif