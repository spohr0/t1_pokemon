# T1 - Pokémon em C++

Trabalho T1 de Programação Orientada a Objetos

Versão simplificada de Pokémon no terminal: batalhas por turno, tipos, captura e Líder de Ginásio.

Integrante: Bernardo Spohr

## Como rodar

Versão de terminal:

    make
    ./pokemon

Versão gráfica (biblioteca raylib, já incluída na pasta `raylib/`, para macOS):

    make grafico
    ./pokemon_grafico

Controles da versão gráfica: setas para escolher, Enter para confirmar, Backspace para voltar do menu de golpes.


## Como jogar

Escolha um inicial (Bulbasaur, Charmander ou Squirtle), ande na grama para batalhar e capturar Pokémon, e vença o Líder do Ginásio para ganhar o jogo.


## Requisitos

- Herança: `Treinador` → `Jogador` / `TreinadorNPC`; `Item` → `Pocao` / `Pokebola`; `PokemonException` → exceções do jogo
- Lambda: `Treinador::trocarParaProximo()`
- Exceções: `include/Excecoes.h`
- Enums: `include/Enums.h`
