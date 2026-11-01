#include "Jogo.h"
#include "Batalha.h"
#include "Excecoes.h"
#include "Entrada.h"
#include <iostream>
#include <cstdlib>

Jogo::Jogo(std::string nomeJogador) : jogador(nomeJogador) {
    estado = EstadoJogo::MENU;
}

//cria um Pokemon da especie pedida, ja com os atributos e golpes
Pokemon Jogo::criarPokemon(std::string especie, int nivel) {
    // Golpes disponiveis
    Golpe investida("Investida", Tipo::NORMAL, 40, 100, CategoriaGolpe::FISICO);
    Golpe arranhao("Arranhao", Tipo::NORMAL, 40, 100, CategoriaGolpe::FISICO);
    Golpe ataqueRapido("Ataque Rapido", Tipo::NORMAL, 40, 100, CategoriaGolpe::FISICO);
    Golpe brasas("Brasas", Tipo::FOGO, 40, 100, CategoriaGolpe::ESPECIAL);
    Golpe jatoDeAgua("Jato de Agua", Tipo::AGUA, 40, 100, CategoriaGolpe::ESPECIAL);
    Golpe chicoteDeVinha("Chicote de Vinha", Tipo::PLANTA, 45, 100, CategoriaGolpe::FISICO);
    Golpe choqueDoTrovao("Choque do Trovao", Tipo::ELETRICO, 40, 100, CategoriaGolpe::ESPECIAL);

    //atributos crescem com o nivel: base * nivel / 50 + 5
    int n = nivel;

    if (especie == "Bulbasaur") {
        Pokemon p("Bulbasaur", Tipo::PLANTA, n, 45*n/50 + n + 10, 49*n/50 + 5, 49*n/50 + 5, 65*n/50 + 5, 65*n/50 + 5, 45*n/50 + 5);
        p.adicionarGolpe(investida);
        p.adicionarGolpe(chicoteDeVinha);
        return p;
    } else if (especie == "Charmander") {
        Pokemon p("Charmander", Tipo::FOGO, n, 39*n/50 + n + 10, 52*n/50 + 5, 43*n/50 + 5, 60*n/50 + 5, 50*n/50 + 5, 65*n/50 + 5);
        p.adicionarGolpe(arranhao);
        p.adicionarGolpe(brasas);
        return p;
    } else if (especie == "Squirtle") {
        Pokemon p("Squirtle", Tipo::AGUA, n, 44*n/50 + n + 10, 48*n/50 + 5, 65*n/50 + 5, 50*n/50 + 5, 64*n/50 + 5, 43*n/50 + 5);
        p.adicionarGolpe(investida);
        p.adicionarGolpe(jatoDeAgua);
        return p;
    } else if (especie == "Pikachu") {
        Pokemon p("Pikachu", Tipo::ELETRICO, n, 35*n/50 + n + 10, 55*n/50 + 5, 40*n/50 + 5, 50*n/50 + 5, 50*n/50 + 5, 90*n/50 + 5);
        p.adicionarGolpe(ataqueRapido);
        p.adicionarGolpe(choqueDoTrovao);
        return p;
    } else if (especie == "Rattata") {
        Pokemon p("Rattata", Tipo::NORMAL, n, 30*n/50 + n + 10, 56*n/50 + 5, 35*n/50 + 5, 25*n/50 + 5, 35*n/50 + 5, 72*n/50 + 5);
        p.adicionarGolpe(investida);
        p.adicionarGolpe(ataqueRapido);
        return p;
    } else if (especie == "Oddish") {
        Pokemon p("Oddish", Tipo::PLANTA, n, 45*n/50 + n + 10, 50*n/50 + 5, 55*n/50 + 5, 75*n/50 + 5, 65*n/50 + 5, 30*n/50 + 5);
        p.adicionarGolpe(investida);
        p.adicionarGolpe(chicoteDeVinha);
        return p;
    } else if (especie == "Vulpix") {
        Pokemon p("Vulpix", Tipo::FOGO, n, 38*n/50 + n + 10, 41*n/50 + 5, 40*n/50 + 5, 50*n/50 + 5, 65*n/50 + 5, 65*n/50 + 5);
        p.adicionarGolpe(ataqueRapido);
        p.adicionarGolpe(brasas);
        return p;
    } else if (especie == "Poliwag") {
        Pokemon p("Poliwag", Tipo::AGUA, n, 40*n/50 + n + 10, 50*n/50 + 5, 40*n/50 + 5, 40*n/50 + 5, 40*n/50 + 5, 90*n/50 + 5);
        p.adicionarGolpe(investida);
        p.adicionarGolpe(jatoDeAgua);
        return p;
    } else {
        // Voltorb
        Pokemon p("Voltorb", Tipo::ELETRICO, n, 40*n/50 + n + 10, 30*n/50 + 5, 50*n/50 + 5, 55*n/50 + 5, 55*n/50 + 5, 100*n/50 + 5);
        p.adicionarGolpe(investida);
        p.adicionarGolpe(choqueDoTrovao);
        return p;
    }
}

void Jogo::escolherInicial() {
    std::cout << "Escolha seu Pokemon inicial:" << std::endl;
    std::cout << "1 - Bulbasaur (Planta)" << std::endl;
    std::cout << "2 - Charmander (Fogo)" << std::endl;
    std::cout << "3 - Squirtle (Agua)" << std::endl;

    int opcao = 0;
    while (opcao == 0) {
        try {
            opcao = lerOpcao(1, 3);
        } catch (EntradaInvalidaException& e) {
            std::cout << e.what() << std::endl;
        }
    }

    if (opcao == 1) {
        jogador.adicionarPokemon(criarPokemon("Bulbasaur", 6));
    } else if (opcao == 2) {
        jogador.adicionarPokemon(criarPokemon("Charmander", 6));
    } else {
        jogador.adicionarPokemon(criarPokemon("Squirtle", 6));
    }
    std::cout << "Voce escolheu " << jogador.getPokemonAtual().getNome() << "!" << std::endl;
}

void Jogo::andarNaGrama() {
    //sorteia um Pokemon selvagem
    std::string especies[6] = {"Pikachu", "Rattata", "Oddish", "Vulpix", "Poliwag", "Voltorb"};
    std::string especie = especies[rand() % 6];
    int nivel = 3 + rand() % 3;   // nivel 3, 4 ou 5

    // o Pokemon selvagem e tratado como um "treinador" com um Pokemon so
    TreinadorNPC selvagem("Selvagem");
    selvagem.adicionarPokemon(criarPokemon(especie, nivel));

    Batalha batalha(jogador, selvagem, true);
    ResultadoBatalha resultado = batalha.executar();

    if (resultado == ResultadoBatalha::VITORIA) {
        std::cout << "Voce venceu a batalha!" << std::endl;
    } else if (resultado == ResultadoBatalha::DERROTA) {
        // Como no jogo original: voce desmaia e acorda no Centro Pokemon
        std::cout << "Seus Pokemon desmaiaram! Voce correu para o Centro Pokemon..." << std::endl;
        centroPokemon();
    }
}

void Jogo::desafiarLider() {
    TreinadorNPC lider("Lider Surge");
    lider.adicionarPokemon(criarPokemon("Voltorb", 6));
    lider.adicionarPokemon(criarPokemon("Pikachu", 7));

    Batalha batalha(jogador, lider, false);
    ResultadoBatalha resultado = batalha.executar();

    if (resultado == ResultadoBatalha::VITORIA) {
        estado = EstadoJogo::VITORIA;
    } else {
        estado = EstadoJogo::DERROTA;
    }
}

void Jogo::centroPokemon() {
    jogador.curarEquipe();
    jogador.trocarParaProximo();
    std::cout << "Seus Pokemon foram curados! Volte sempre!" << std::endl;
}

void Jogo::verEquipe() {
    std::cout << "--- Equipe de " << jogador.getNome() << " ---" << std::endl;
    jogador.mostrarEquipe();
    std::cout << "--- Mochila ---" << std::endl;
    jogador.getMochila().mostrar();
}

void Jogo::executar() {
    std::cout << "Ola, " << jogador.getNome() << "! Bem-vindo ao mundo Pokemon!" << std::endl;
    escolherInicial();

    while (estado == EstadoJogo::MENU) {
        std::cout << std::endl << "O que voce quer fazer?" << std::endl;
        std::cout << "1 - Andar na grama" << std::endl;
        std::cout << "2 - Desafiar o Lider do Ginasio" << std::endl;
        std::cout << "3 - Ir ao Centro Pokemon" << std::endl;
        std::cout << "4 - Ver equipe e mochila" << std::endl;
        std::cout << "0 - Sair" << std::endl;

        try {
            int opcao = lerOpcao(0, 4);
            if (opcao == 1) {
                andarNaGrama();
            } else if (opcao == 2) {
                desafiarLider();
            } else if (opcao == 3) {
                centroPokemon();
            } else if (opcao == 4) {
                verEquipe();
            } else {
                std::cout << "Ate a proxima!" << std::endl;
                return;
            }
        } catch (PokemonException& e) {
            std::cout << e.what() << std::endl;
        }
    }

    if (estado == EstadoJogo::VITORIA) {
        std::cout << std::endl << "Parabens! Voce derrotou o Lider e venceu o jogo!" << std::endl;
    } else {
        std::cout << std::endl << "Todos os seus Pokemon desmaiaram... Fim de jogo." << std::endl;
    }
}