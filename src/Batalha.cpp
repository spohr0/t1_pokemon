#include "Batalha.h"
#include "TabelaTipos.h"
#include "Excecoes.h"
#include "Entrada.h"
#include <iostream>
#include <cstdlib>

Batalha::Batalha(Jogador& j, TreinadorNPC& o, bool ehSelvagem) : jogador(j), oponente(o) {
    selvagem = ehSelvagem;
}

int Batalha::calcularDano(Pokemon& atacante, Pokemon& defensor, Golpe golpe) {
    // Golpe fisico usa ataque/defesa, especial usa ataque/defesa especial
    double ataque = atacante.getAtaque();
    double defesa = defensor.getDefesa();
    if (golpe.getCategoria() == CategoriaGolpe::ESPECIAL) {
        ataque = atacante.getAtaqueEspecial();
        defesa = defensor.getDefesaEspecial();
    }

    //formula simplificada do jogo original
    double dano = (2.0 * atacante.getNivel() / 5 + 2) * golpe.getPoder() * ataque / defesa / 50 + 2;

    //bonus de 50% se o golpe for do mesmo tipo do Pokemon
    if (golpe.getTipo() == atacante.getTipo()) {
        dano = dano * 1.5;
    }

    //vantagem ou desvantagem de tipo
    dano = dano * TabelaTipos::calcularMultiplicador(golpe.getTipo(), defensor.getTipo());

    // Variacao aleatoria entre 85% e 100%
    dano = dano * (85 + rand() % 16) / 100;

    if (dano < 1) {
        dano = 1;
    }
    return (int)dano;
}

void Batalha::atacar(Pokemon& atacante, Pokemon& defensor, Golpe golpe) {
    std::cout << atacante.getNome() << " usou " << golpe.getNome() << "!" << std::endl;

    //chance de errar
    if (rand() % 100 >= golpe.getPrecisao()) {
        std::cout << "Mas errou!" << std::endl;
        return;
    }

    double multiplicador = TabelaTipos::calcularMultiplicador(golpe.getTipo(), defensor.getTipo());
    if (multiplicador > 1) {
        std::cout << "E super efetivo!" << std::endl;
    } else if (multiplicador < 1) {
        std::cout << "Nao e muito efetivo..." << std::endl;
    }

    int dano = calcularDano(atacante, defensor, golpe);
    defensor.receberDano(dano);
    std::cout << defensor.getNome() << " perdeu " << dano << " de HP." << std::endl;
}

void Batalha::oponenteAtaca() {
    Pokemon& dele = oponente.getPokemonAtual();
    Pokemon& meu = jogador.getPokemonAtual();
    int g = oponente.escolherGolpe(meu);
    atacar(dele, meu, dele.getGolpe(g));
}

void Batalha::mostrarStatus() {
    Pokemon& meu = jogador.getPokemonAtual();
    Pokemon& dele = oponente.getPokemonAtual();

    std::cout << std::endl << "----------------------------------------" << std::endl;
    std::cout << dele.getNome() << " Nv." << dele.getNivel()
              << "  HP: " << dele.getHpAtual() << "/" << dele.getHpMax() << std::endl;
    std::cout << meu.getNome() << " Nv." << meu.getNivel()
              << "  HP: " << meu.getHpAtual() << "/" << meu.getHpMax() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

ResultadoBatalha Batalha::executar() {
    if (selvagem) {
        std::cout << "Um " << oponente.getPokemonAtual().getNome() << " selvagem apareceu!" << std::endl;
    } else {
        std::cout << oponente.getNome() << " quer batalhar!" << std::endl;
        std::cout << oponente.getNome() << " enviou " << oponente.getPokemonAtual().getNome() << "!" << std::endl;
    }
    std::cout << "Vai, " << jogador.getPokemonAtual().getNome() << "!" << std::endl;

    while (true) {
        mostrarStatus();
        Pokemon& meu = jogador.getPokemonAtual();
        Pokemon& dele = oponente.getPokemonAtual();

        std::cout << "1 - Atacar" << std::endl;
        std::cout << "2 - Usar Pocao (" << jogador.getMochila().getQuantidadePocoes() << ")" << std::endl;
        std::cout << "3 - Jogar Pokebola" << std::endl;
        std::cout << "4 - Fugir" << std::endl;

        try {
            int opcao = lerOpcao(1, 4);

            if (opcao == 1) {
                int g = jogador.escolherGolpe(dele);
                //quem for mais rapido ataca primeiro
                if (meu.getVelocidade() >= dele.getVelocidade()) {
                    atacar(meu, dele, meu.getGolpe(g));
                    if (!dele.estaDesmaiado()) {
                        oponenteAtaca();
                    }
                } else {
                    oponenteAtaca();
                    if (!meu.estaDesmaiado()) {
                        atacar(meu, dele, meu.getGolpe(g));
                    }
                }
            } else if (opcao == 2) {
                jogador.getMochila().usarPocao(meu);
                std::cout << meu.getNome() << " recuperou HP!" << std::endl;
                oponenteAtaca();
            } else if (opcao == 3) {
                if (!selvagem) {
                    throw ItemIndisponivelException("Nao pode capturar o Pokemon de outro treinador!");
                }
                std::cout << "Voce jogou uma Pokebola..." << std::endl;
                if (jogador.getMochila().usarPokebola(dele)) {
                    std::cout << "Pegou! " << dele.getNome() << " foi capturado!" << std::endl;
                    try {
                        jogador.adicionarPokemon(dele);
                    } catch (EquipeCheiaException& e) {
                        std::cout << e.what() << " " << dele.getNome() << " foi solto." << std::endl;
                    }
                    return ResultadoBatalha::CAPTURA;
                }
                std::cout << "Ah nao! O Pokemon escapou!" << std::endl;
                oponenteAtaca();
            } else {
                if (!selvagem) {
                    throw PokemonException("Nao da pra fugir de uma batalha contra treinador!");
                }
                std::cout << "Voce fugiu!" << std::endl;
                return ResultadoBatalha::FUGA;
            }
        } catch (PokemonException& e) {
            std::cout << e.what() << std::endl;
            continue;   //volta para o menu sem perder o turno
        }

        //verifica se o Pokemon do oponente desmaiou
        if (dele.estaDesmaiado()) {
            std::cout << dele.getNome() << " desmaiou!" << std::endl;
            if (!oponente.temPokemonVivo()) {
                return ResultadoBatalha::VITORIA;
            }
            oponente.trocarParaProximo();
            std::cout << oponente.getNome() << " enviou " << oponente.getPokemonAtual().getNome() << "!" << std::endl;
        }

        //verifica se o Pokemon do jogador desmaiou
        if (meu.estaDesmaiado()) {
            std::cout << meu.getNome() << " desmaiou!" << std::endl;
            if (!jogador.temPokemonVivo()) {
                return ResultadoBatalha::DERROTA;
            }
            jogador.trocarParaProximo();
            std::cout << "Vai, " << jogador.getPokemonAtual().getNome() << "!" << std::endl;
        }
    }
}