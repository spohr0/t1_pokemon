#include "Enums.h"

std::string tipoParaString(Tipo tipo) {
    if (tipo == Tipo::FOGO) {
        return "Fogo";
    } else if (tipo == Tipo::AGUA) {
        return "Agua";
    } else if (tipo == Tipo::PLANTA) {
        return "Planta";
    } else if (tipo == Tipo::ELETRICO) {
        return "Eletrico";
    } else {
        return "Normal";
    }
}