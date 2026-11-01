#include "grafico/JogoGrafico.h"
#include "Jogo.h"
#include "Batalha.h"
#include "TabelaTipos.h"
#include "Excecoes.h"
#include <cstdlib>

JogoGrafico::JogoGrafico() : jogador("Jogador"), oponente("Ninguem") {
    tela = Tela::ESCOLHA_INICIAL;
    opcao = 0;
    selvagem = true;
    escolhendoGolpe = false;
    batalhaAcabou = false;
    fimDeJogo = false;
    venceuJogo = false;
    sair = false;
}

// ---------------------------------------------------------------
// Loop principal: le o teclado e desenha a tela 60 vezes por segundo
// ---------------------------------------------------------------
void JogoGrafico::executar() {
    InitWindow(800, 600, "Pokemon - T1 POO");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);   // ESC nao fecha a janela
    carregarImagens();      // so pode carregar depois de abrir a janela

    while (!WindowShouldClose() && !sair) {
        // 1) Le o teclado
        if (tela == Tela::ESCOLHA_INICIAL) {
            atualizarEscolha();
        } else if (tela == Tela::MENU) {
            atualizarMenu();
        } else if (tela == Tela::BATALHA) {
            atualizarBatalha();
        } else if (IsKeyPressed(KEY_ENTER)) {
            sair = true;
        }

        // 2) Desenha
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (tela == Tela::ESCOLHA_INICIAL) {
            desenharEscolha();
        } else if (tela == Tela::MENU) {
            desenharMenu();
        } else if (tela == Tela::BATALHA) {
            desenharBatalha();
        } else {
            desenharFim();
        }
        EndDrawing();
    }

    descarregarImagens();
    CloseWindow();
}

// ---------------------------------------------------------------
// Imagens: procura "imagens/Nome.png" para cada Pokemon do jogo.
// Se o arquivo nao existir, o Pokemon e desenhado como um circulo.
// ---------------------------------------------------------------
void JogoGrafico::carregarImagens() {
    std::string nomes[9] = {"Bulbasaur", "Charmander", "Squirtle", "Pikachu", "Rattata",
                            "Oddish", "Vulpix", "Poliwag", "Voltorb"};
    for (int i = 0; i < 9; i++) {
        std::string caminho = "imagens/" + nomes[i] + ".png";
        if (FileExists(caminho.c_str())) {
            nomesImagens.push_back(nomes[i]);
            imagens.push_back(LoadTexture(caminho.c_str()));
        }
    }
}

void JogoGrafico::descarregarImagens() {
    for (int i = 0; i < imagens.size(); i++) {
        UnloadTexture(imagens[i]);
    }
}

void JogoGrafico::desenharFigura(std::string nome, Tipo tipo, int x, int y, int raio) {
    // Sombra embaixo do Pokemon
    DrawEllipse(x, y + raio, raio * 1.2, raio * 0.3, Fade(DARKGREEN, 0.5f));

    for (int i = 0; i < nomesImagens.size(); i++) {
        if (nomesImagens[i] == nome) {
            // Ajusta o tamanho da imagem para caber num quadrado de lado 2*raio
            Texture2D img = imagens[i];
            float escala = 2.0f * raio / img.width;
            if (img.height > img.width) {
                escala = 2.0f * raio / img.height;
            }
            float largura = img.width * escala;
            float altura = img.height * escala;
            Rectangle origem = {0, 0, (float)img.width, (float)img.height};
            Rectangle destino = {x - largura / 2, y - altura / 2, largura, altura};
            DrawTexturePro(img, origem, destino, {0, 0}, 0, WHITE);
            return;
        }
    }

    // Sem imagem: circulo com a cor do tipo
    DrawCircle(x, y, raio, corDoTipo(tipo));
    DrawCircleLines(x, y, raio, BLACK);
}

// ---------------------------------------------------------------
// Teclado
// ---------------------------------------------------------------
void JogoGrafico::moverSelecao(int total) {
    if (IsKeyPressed(KEY_DOWN)) {
        opcao = (opcao + 1) % total;
    }
    if (IsKeyPressed(KEY_UP)) {
        opcao = (opcao + total - 1) % total;
    }
}

void JogoGrafico::atualizarEscolha() {
    moverSelecao(3);
    if (IsKeyPressed(KEY_ENTER)) {
        std::string iniciais[3] = {"Bulbasaur", "Charmander", "Squirtle"};
        jogador.adicionarPokemon(Jogo::criarPokemon(iniciais[opcao], 6));
        mensagens.clear();
        mensagem("Voce escolheu " + iniciais[opcao] + "!");
        tela = Tela::MENU;
        opcao = 0;
    }
}

void JogoGrafico::atualizarMenu() {
    moverSelecao(4);
    if (IsKeyPressed(KEY_ENTER)) {
        if (opcao == 0) {
            iniciarBatalha(true);
        } else if (opcao == 1) {
            iniciarBatalha(false);
        } else if (opcao == 2) {
            jogador.curarEquipe();
            jogador.trocarParaProximo();
            mensagens.clear();
            mensagem("Seus Pokemon foram curados!");
        } else {
            sair = true;
        }
    }
}

void JogoGrafico::atualizarBatalha() {
    // Batalha terminou: espera o Enter para sair da tela
    if (batalhaAcabou) {
        if (IsKeyPressed(KEY_ENTER)) {
            if (fimDeJogo) {
                tela = Tela::FIM;
            } else {
                tela = Tela::MENU;
            }
            opcao = 0;
        }
        return;
    }

    // Menu de golpes
    if (escolhendoGolpe) {
        moverSelecao(jogador.getPokemonAtual().getQuantidadeGolpes());
        if (IsKeyPressed(KEY_BACKSPACE)) {
            escolhendoGolpe = false;
            opcao = 0;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            int golpe = opcao;
            escolhendoGolpe = false;
            opcao = 0;
            mensagens.clear();
            jogadorAtaca(golpe);
        }
        return;
    }

    // Menu de acoes
    moverSelecao(4);
    if (IsKeyPressed(KEY_ENTER)) {
        Pokemon& meu = jogador.getPokemonAtual();
        Pokemon& dele = oponente.getPokemonAtual();
        mensagens.clear();

        try {
            if (opcao == 0) {
                escolhendoGolpe = true;
            } else if (opcao == 1) {
                jogador.getMochila().usarPocao(meu);
                mensagem(meu.getNome() + " recuperou HP!");
                oponenteAtaca();
                verificarDesmaios();
            } else if (opcao == 2) {
                if (!selvagem) {
                    throw ItemIndisponivelException("Nao pode capturar Pokemon de treinador!");
                }
                if (jogador.getMochila().usarPokebola(dele)) {
                    mensagem("Pegou! " + dele.getNome() + " foi capturado!");
                    try {
                        jogador.adicionarPokemon(dele);
                    } catch (EquipeCheiaException& e) {
                        mensagem(e.what());
                    }
                    batalhaAcabou = true;
                } else {
                    mensagem("O Pokemon escapou da Pokebola!");
                    oponenteAtaca();
                    verificarDesmaios();
                }
            } else {
                if (!selvagem) {
                    throw PokemonException("Nao da pra fugir de batalha de treinador!");
                }
                mensagem("Voce fugiu!");
                batalhaAcabou = true;
            }
        } catch (PokemonException& e) {
            mensagem(e.what());
        }
        opcao = 0;
    }
}

// ---------------------------------------------------------------
// Regras da batalha (mesmas da versao de terminal)
// ---------------------------------------------------------------
void JogoGrafico::iniciarBatalha(bool ehSelvagem) {
    selvagem = ehSelvagem;
    batalhaAcabou = false;
    escolhendoGolpe = false;
    mensagens.clear();

    if (selvagem) {
        std::string especies[6] = {"Pikachu", "Rattata", "Oddish", "Vulpix", "Poliwag", "Voltorb"};
        oponente = TreinadorNPC("Selvagem");
        oponente.adicionarPokemon(Jogo::criarPokemon(especies[rand() % 6], 3 + rand() % 3));
        mensagem("Um " + oponente.getPokemonAtual().getNome() + " selvagem apareceu!");
    } else {
        oponente = TreinadorNPC("Lider Surge");
        oponente.adicionarPokemon(Jogo::criarPokemon("Voltorb", 6));
        oponente.adicionarPokemon(Jogo::criarPokemon("Pikachu", 7));
        mensagem("Lider Surge quer batalhar!");
    }
    mensagem("Vai, " + jogador.getPokemonAtual().getNome() + "!");
    tela = Tela::BATALHA;
    opcao = 0;
}

void JogoGrafico::jogadorAtaca(int golpe) {
    Pokemon& meu = jogador.getPokemonAtual();
    Pokemon& dele = oponente.getPokemonAtual();

    // Quem for mais rapido ataca primeiro
    if (meu.getVelocidade() >= dele.getVelocidade()) {
        atacar(meu, dele, meu.getGolpe(golpe));
        if (!dele.estaDesmaiado()) {
            oponenteAtaca();
        }
    } else {
        oponenteAtaca();
        if (!meu.estaDesmaiado()) {
            atacar(meu, dele, meu.getGolpe(golpe));
        }
    }
    verificarDesmaios();
}

void JogoGrafico::atacar(Pokemon& atacante, Pokemon& defensor, Golpe golpe) {
    mensagem(atacante.getNome() + " usou " + golpe.getNome() + "!");

    if (rand() % 100 >= golpe.getPrecisao()) {
        mensagem("Mas errou!");
        return;
    }

    double multiplicador = TabelaTipos::calcularMultiplicador(golpe.getTipo(), defensor.getTipo());
    if (multiplicador > 1) {
        mensagem("E super efetivo!");
    } else if (multiplicador < 1) {
        mensagem("Nao e muito efetivo...");
    }

    int dano = Batalha::calcularDano(atacante, defensor, golpe);
    defensor.receberDano(dano);
}

void JogoGrafico::oponenteAtaca() {
    Pokemon& dele = oponente.getPokemonAtual();
    Pokemon& meu = jogador.getPokemonAtual();
    int g = oponente.escolherGolpe(meu);
    atacar(dele, meu, dele.getGolpe(g));
}

void JogoGrafico::verificarDesmaios() {
    Pokemon& meu = jogador.getPokemonAtual();
    Pokemon& dele = oponente.getPokemonAtual();

    if (dele.estaDesmaiado()) {
        mensagem(dele.getNome() + " desmaiou!");
        if (!oponente.temPokemonVivo()) {
            terminarBatalha(true);
            return;
        }
        oponente.trocarParaProximo();
        mensagem(oponente.getNome() + " enviou " + oponente.getPokemonAtual().getNome() + "!");
    }

    if (meu.estaDesmaiado()) {
        mensagem(meu.getNome() + " desmaiou!");
        if (!jogador.temPokemonVivo()) {
            terminarBatalha(false);
            return;
        }
        jogador.trocarParaProximo();
        mensagem("Vai, " + jogador.getPokemonAtual().getNome() + "!");
    }
}

void JogoGrafico::terminarBatalha(bool venceu) {
    batalhaAcabou = true;
    if (venceu) {
        mensagem("Voce venceu a batalha!");
        if (!selvagem) {
            fimDeJogo = true;
            venceuJogo = true;
        }
    } else if (selvagem) {
        // Como no original: perdeu para selvagem, volta ao Centro Pokemon
        mensagem("Voce correu para o Centro Pokemon...");
        jogador.curarEquipe();
        jogador.trocarParaProximo();
    } else {
        fimDeJogo = true;
    }
}

void JogoGrafico::mensagem(std::string texto) {
    mensagens.push_back(texto);
}

// ---------------------------------------------------------------
// Desenho
// ---------------------------------------------------------------
Color JogoGrafico::corDoTipo(Tipo tipo) {
    if (tipo == Tipo::FOGO) {
        return RED;
    } else if (tipo == Tipo::AGUA) {
        return BLUE;
    } else if (tipo == Tipo::PLANTA) {
        return GREEN;
    } else if (tipo == Tipo::ELETRICO) {
        return GOLD;
    } else {
        return GRAY;
    }
}

void JogoGrafico::desenharOpcoes(std::vector<std::string> itens, int x, int y) {
    for (int i = 0; i < itens.size(); i++) {
        Color cor = DARKGRAY;
        std::string texto = "  " + itens[i];
        if (i == opcao) {
            cor = BLACK;
            texto = "> " + itens[i];   // seta no item selecionado
        }
        DrawText(texto.c_str(), x, y + i * 32, 24, cor);
    }
}

void JogoGrafico::desenharMensagens(int x, int y) {
    // Mostra so as 4 ultimas mensagens
    int inicio = mensagens.size() - 4;
    if (inicio < 0) {
        inicio = 0;
    }
    int linha = 0;
    for (int i = inicio; i < mensagens.size(); i++) {
        DrawText(mensagens[i].c_str(), x, y + linha * 30, 20, BLACK);
        linha++;
    }
}

void JogoGrafico::desenharInfo(Pokemon& p, int x, int y) {
    DrawRectangle(x, y, 320, 80, LIGHTGRAY);
    DrawRectangleLines(x, y, 320, 80, BLACK);

    std::string titulo = p.getNome() + "  Nv." + std::to_string(p.getNivel());
    DrawText(titulo.c_str(), x + 12, y + 10, 24, BLACK);

    // Barra de HP: verde, amarela ou vermelha
    int largura = 200 * p.getHpAtual() / p.getHpMax();
    Color cor = GREEN;
    if (p.getHpAtual() * 100 / p.getHpMax() < 50) {
        cor = ORANGE;
    }
    if (p.getHpAtual() * 100 / p.getHpMax() < 20) {
        cor = RED;
    }
    DrawText("HP", x + 12, y + 48, 20, BLACK);
    DrawRectangle(x + 50, y + 50, 200, 16, DARKGRAY);
    DrawRectangle(x + 50, y + 50, largura, 16, cor);

    std::string hp = std::to_string(p.getHpAtual()) + "/" + std::to_string(p.getHpMax());
    DrawText(hp.c_str(), x + 258, y + 48, 20, BLACK);
}

void JogoGrafico::desenharEscolha() {
    DrawText("POKEMON", 290, 40, 50, RED);
    DrawText("Escolha seu Pokemon inicial", 230, 110, 24, DARKGRAY);

    std::string nomes[3] = {"Bulbasaur", "Charmander", "Squirtle"};
    Tipo tipos[3] = {Tipo::PLANTA, Tipo::FOGO, Tipo::AGUA};
    for (int i = 0; i < 3; i++) {
        int x = 150 + i * 250;
        if (i == opcao) {
            DrawRectangleLines(x - 90, 190, 180, 230, BLACK);
        }
        desenharFigura(nomes[i], tipos[i], x, 280, 60);
        DrawText(nomes[i].c_str(), x - MeasureText(nomes[i].c_str(), 24) / 2, 370, 24, BLACK);
    }
    DrawText("Setas: escolher    Enter: confirmar", 190, 520, 22, GRAY);

    // Na tela de escolha as setas laterais tambem funcionam
    if (IsKeyPressed(KEY_RIGHT)) {
        opcao = (opcao + 1) % 3;
    }
    if (IsKeyPressed(KEY_LEFT)) {
        opcao = (opcao + 2) % 3;
    }
}

void JogoGrafico::desenharMenu() {
    DrawText("O que voce quer fazer?", 40, 40, 32, BLACK);

    std::vector<std::string> itens;
    itens.push_back("Andar na grama");
    itens.push_back("Desafiar o Lider do Ginasio");
    itens.push_back("Centro Pokemon");
    itens.push_back("Sair");
    desenharOpcoes(itens, 60, 110);

    // Equipe do jogador
    DrawText("Sua equipe:", 480, 110, 24, BLACK);
    Pokemon& atual = jogador.getPokemonAtual();
    desenharFigura(atual.getNome(), atual.getTipo(), 520, 180, 30);
    std::string info = atual.getNome() + " HP " + std::to_string(atual.getHpAtual()) + "/" + std::to_string(atual.getHpMax());
    DrawText(info.c_str(), 560, 170, 20, BLACK);
    std::string pocoes = "Pocoes: " + std::to_string(jogador.getMochila().getQuantidadePocoes());
    DrawText(pocoes.c_str(), 480, 230, 20, DARKGRAY);

    DrawRectangleLines(20, 430, 760, 150, BLACK);
    desenharMensagens(40, 450);
}

void JogoGrafico::desenharBatalha() {
    Pokemon& meu = jogador.getPokemonAtual();
    Pokemon& dele = oponente.getPokemonAtual();

    // Cenario: ceu e grama
    DrawRectangleGradientV(0, 0, 800, 200, SKYBLUE, RAYWHITE);
    DrawRectangleGradientV(0, 200, 800, 220, (Color){170, 220, 140, 255}, (Color){110, 180, 90, 255});

    // Oponente em cima, jogador embaixo
    desenharInfo(dele, 40, 30);
    desenharFigura(dele.getNome(), dele.getTipo(), 600, 140, 60);
    desenharFigura(meu.getNome(), meu.getTipo(), 200, 320, 75);
    desenharInfo(meu, 440, 280);

    // Caixa de mensagens
    DrawRectangleLines(20, 430, 470, 150, BLACK);
    desenharMensagens(35, 445);

    // Caixa do menu
    DrawRectangleLines(500, 430, 280, 150, BLACK);
    if (batalhaAcabou) {
        DrawText("Enter: continuar", 520, 490, 22, BLACK);
    } else if (escolhendoGolpe) {
        std::vector<std::string> golpes;
        for (int i = 0; i < meu.getQuantidadeGolpes(); i++) {
            golpes.push_back(meu.getGolpe(i).getNome());
        }
        desenharOpcoes(golpes, 515, 445);
        DrawText("Backspace: voltar", 520, 550, 18, GRAY);
    } else {
        std::vector<std::string> acoes;
        acoes.push_back("Atacar");
        acoes.push_back("Pocao (" + std::to_string(jogador.getMochila().getQuantidadePocoes()) + ")");
        acoes.push_back("Pokebola");
        acoes.push_back("Fugir");
        desenharOpcoes(acoes, 515, 445);
    }
}

void JogoGrafico::desenharFim() {
    if (venceuJogo) {
        DrawText("PARABENS!", 260, 200, 50, GOLD);
        DrawText("Voce derrotou o Lider e venceu o jogo!", 150, 290, 24, BLACK);
    } else {
        DrawText("FIM DE JOGO", 240, 200, 50, RED);
        DrawText("Todos os seus Pokemon desmaiaram...", 170, 290, 24, BLACK);
    }
    DrawText("Enter: sair", 330, 450, 22, GRAY);
}
