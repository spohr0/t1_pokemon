#include "grafico/JogoGrafico.h"
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0));
    JogoGrafico jogo;
    jogo.executar();
    return 0;
}
