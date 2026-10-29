#include "Golpe.h"

Golpe::Golpe(std::string nome, Tipo tipo, int poder, int precisao, CategoriaGolpe categoria) {
    this->nome = nome;
    this->tipo = tipo;
    this->poder = poder;
    this->precisao = precisao;
    this->categoria = categoria;
}

std::string Golpe::getNome() {
    return nome;
}

Tipo Golpe::getTipo() {
    return tipo;
}

int Golpe::getPoder() {
    return poder;
}

int Golpe::getPrecisao() {
    return precisao;
}

CategoriaGolpe Golpe::getCategoria() {
    return categoria;
}