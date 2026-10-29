#ifndef GOLPE_H
#define GOLPE_H

#include <string>
#include "Enums.h"

class Golpe {
private:
    std::string nome;
    Tipo tipo;
    int poder;      
    int precisao;   
    CategoriaGolpe categoria;

public:
    Golpe(std::string nome, Tipo tipo, int poder, int precisao, CategoriaGolpe categoria);

    std::string getNome();
    Tipo getTipo();
    int getPoder();
    int getPrecisao();
    CategoriaGolpe getCategoria();
};

#endif