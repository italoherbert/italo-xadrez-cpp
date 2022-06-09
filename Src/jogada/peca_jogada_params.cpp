
#include "peca_jogada_params.h"

PecaJogadaParams::PecaJogadaParams( JogadaUtil* jUtil, Jogo* jogo, JogadaLista* lista, Pecas* pecas, int posX, int posY, bool isComp, bool isCaptura ) {
	this->jUtil = jUtil;
	this->jogo = jogo;
	this->lista = lista;
	this->posX = posX;
	this->posY = posY;
	this->isComp = isComp;
	this->isCaptura = isCaptura;
	this->pecas = pecas;
}

JogadaUtil* PecaJogadaParams::getJogadaUtil() {
	return jUtil;
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

