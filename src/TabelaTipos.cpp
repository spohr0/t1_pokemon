#include "TabelaTipos.h"

double TabelaTipos::calcularMultiplicador(Tipo ataque, Tipo defesa) {
    //super efetivo (2x)
    if (ataque == Tipo::FOGO && defesa == Tipo::PLANTA) return 2.0;
    if (ataque == Tipo::AGUA && defesa == Tipo::FOGO) return 2.0;
    if (ataque == Tipo::PLANTA && defesa == Tipo::AGUA) return 2.0;
    if (ataque == Tipo::ELETRICO && defesa == Tipo::AGUA) return 2.0;

    //pouco efetivo (0.5x)
    if (ataque == Tipo::FOGO && defesa == Tipo::AGUA) return 0.5;
    if (ataque == Tipo::AGUA && defesa == Tipo::PLANTA) return 0.5;
    if (ataque == Tipo::PLANTA && defesa == Tipo::FOGO) return 0.5;
    if (ataque == Tipo::ELETRICO && defesa == Tipo::PLANTA) return 0.5;

    //mesmo tipo resiste a si mesmo (menos normal)
    if (ataque == defesa && ataque != Tipo::NORMAL) return 0.5;

    //qualquer outro caso
    return 1.0;
}