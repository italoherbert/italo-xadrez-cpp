#include "algoritmo_gerenciador.h"

#include <iostream>

#include "algoritmo.h"

AlgoritmoGerenciador::AlgoritmoGerenciador( Jogo* jogo ) {
	this->minimaxAlgoritmo = new Algoritmo( jogo );
	this->jogo = jogo;
}

AlgoritmoGerenciador::~AlgoritmoGerenciador() {
	delete this->minimaxAlgoritmo;
}

void AlgoritmoGerenciador::calculaMelhorJogada( int* posX, int* posY, Jogada** jogada ) {
	switch( jogo->getNivel() ) {
		case Jogo::NIVEL_FACIL:
		case Jogo::NIVEL_NORMAL:
		case Jogo::NIVEL_DIFICIL:
			minimaxAlgoritmo->calculaMelhorJogada( posX, posY, jogada );
			break;
	}
}

