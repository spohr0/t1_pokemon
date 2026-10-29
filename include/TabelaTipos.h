#ifndef TABELATIPOS_H
#define TABELATIPOS_H

#include "Enums.h"

class TabelaTipos {
public:
    //retorna 2.0 (super efetivo), 0.5 (pouco efetivo) ou 1.0 (normal)
    static double calcularMultiplicador(Tipo ataque, Tipo defesa);
};

#endif