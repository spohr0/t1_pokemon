#ifndef JOGOGRAFICO_H
#define JOGOGRAFICO_H

#include <string>
#include <vector>
#include "raylib.h"
#include "treinadores/Jogador.h"
#include "treinadores/TreinadorNPC.h"

// Telas da versao grafica
enum class Tela {
    ESCOLHA_INICIAL,
    MENU,
    BATALHA,
    FIM
};

class JogoGrafico {
private:
    Jogador jogador;
    TreinadorNPC oponente;
    Tela tela;
    int opcao;                          // item selecionado no menu
    bool selvagem;                      // batalha contra Pokemon selvagem?
    bool escolhendoGolpe;               // esta no menu de golpes?
    bool batalhaAcabou;
    bool fimDeJogo;
    bool venceuJogo;
    bool sair;
    std::vector<std::string> mensagens;

    // Imagens da pasta "imagens/" (nomeDoPokemon.png)
    std::vector<std::string> nomesImagens;
    std::vector<Texture2D> imagens;
    void carregarImagens();
    void descarregarImagens();

    // Teclado
    void moverSelecao(int total);
    void atualizarEscolha();
    void atualizarMenu();
    void atualizarBatalha();

    // Regras da batalha
    void iniciarBatalha(bool ehSelvagem);
    void jogadorAtaca(int golpe);
    void atacar(Pokemon& atacante, Pokemon& defensor, Golpe golpe);
    void oponenteAtaca();
    void verificarDesmaios();
    void terminarBatalha(bool venceu);
    void mensagem(std::string texto);

    // Desenho
    Color corDoTipo(Tipo tipo);
    void desenharFigura(std::string nome, Tipo tipo, int x, int y, int raio);
    void desenharEscolha();
    void desenharMenu();
    void desenharBatalha();
    void desenharFim();
    void desenharInfo(Pokemon& p, int x, int y);
    void desenharOpcoes(std::vector<std::string> itens, int x, int y);
    void desenharMensagens(int x, int y);

public:
    JogoGrafico();
    void executar();
};

#endif
