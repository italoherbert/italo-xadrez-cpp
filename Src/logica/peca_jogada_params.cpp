
#include "peca_jogada_params.h"

PecaJogadaParams::PecaJogadaParams( Jogo* jogo, JogadaLista* lista, Pecas* pecas, int posX, int posY, bool isComp, bool isCaptura ) {
	this->jogo = jogo;
	this->lista = lista;
	this->pecas = pecas;
	this->posX = posX;
	this->posY = posY;
	this->isComp = isComp;
	this->isCaptura = isCaptura;
}

Jogo* PecaJogadaParams::getJogo() {
	return jogo;
}

JogadaLista* PecaJogadaParams::getJogadas() {
	return lista;
}

int PecaJogadaParams::getPosX() {
	return posX;
}

int PecaJogadaParams::getPosY() {
	return posY;
}

bool PecaJogadaParams::getIsComp() {
	return isComp;
}

bool PecaJogadaParams::getIsCaptura() {
	return isCaptura;
}

Pecas* PecaJogadaParams::getPecas() {
	return pecas;
}

