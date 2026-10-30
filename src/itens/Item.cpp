#include "itens/Item.h"
#include "Excecoes.h"

Item::Item(std::string nome, int quantidade) {
    this->nome = nome;
    this->quantidade = quantidade;
}

Item::~Item() {
}

void Item::adicionar(int qtd) {
    quantidade = quantidade + qtd;
}

void Item::consumir() {
    if (quantidade == 0) {
        throw ItemIndisponivelException("Voce nao tem mais " + nome + "!");}
    quantidade = quantidade - 1;
}

std::string Item::getNome() {
    return nome;
}

int Item::getQuantidade() {
    return quantidade;
}