#include "Jogo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0));   // para os sorteios mudarem a cada execucao

    std::cout << "=== POKEMON ===" << std::endl;
    std::cout << "Qual o seu nome? ";
    std::string nome;
    std::cin >> nome;

    Jogo jogo(nome);
    jogo.executar();
    return 0;
}