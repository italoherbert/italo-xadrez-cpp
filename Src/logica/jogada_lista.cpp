#include "jogada_lista.h"

#include <cstdlib>

#include "jogada.h"
#include "jogada_roque.h"
#include "jogada_en_passant.h"

JogadaLista::JogadaLista() {
	jogadas_tam = 0;
}

JogadaLista::~JogadaLista() {
	for( int i = 0; i < jogadas_tam; i++ )
		if ( jogadas[ i ] != NULL )
			delete jogadas[ i ];
}

void JogadaLista::addJogada( int posX, int posY, Peca* captura, int tipo ) {
	jogadas[ jogadas_tam++ ] = new Jogada( posX, posY, captura, tipo );
}

void JogadaLista::addJogada( int posX, int posY, Peca* captura ) {
	jogadas[ jogadas_tam++ ] = new Jogada( posX, posY, captura, Jogada::NORMAL );	 
}

void JogadaLista::addJogada( Jogada* jogada ) {
	jogadas[ jogadas_tam++ ] = jogada;
}

void JogadaLista::limpaJogadas() {
	for( int i = 0; i < jogadas_tam; i++ )
		jogadas[ i ] = NULL;
	jogadas_tam = 0;
}

void JogadaLista::copia( JogadaLista* lista ) {
	lista->limpaJogadas();
	for( int i = 0; i < jogadas_tam; i++ ) {	
		int posX = jogadas[i]->getPosX();
		int posY = jogadas[i]->getPosY();
		Peca* captura = jogadas[i]->getCaptura();
		int tipo = jogadas[i]->getTipo();
		
		if ( tipo == Jogada::ROQUE ) {
			Peca* rei = ((JogadaRoque*)jogadas[i])->getRei();
			Peca* torre = ((JogadaRoque*)jogadas[i])->getTorre();
			int reiPosX = ((JogadaRoque*)jogadas[i])->getReiPosX();
			int reiPosY = ((JogadaRoque*)jogadas[i])->getReiPosY();
			int torrePosX = ((JogadaRoque*)jogadas[i])->getTorrePosX();
			int torrePosY = ((JogadaRoque*)jogadas[i])->getTorrePosY();
			lista->addJogada( new JogadaRoque( reiPosX, reiPosY, torrePosX, torrePosY, captura, rei, torre ) );
		} else if ( tipo == Jogada::EN_PASSANT ) {
			lista->addJogada( new JogadaEnPassant( posX, posY, captura ) );
		} else {
			lista->addJogada( new Jogada( posX, posY, captura, tipo ) );		
		}
	}
}

int JogadaLista::getTam() {
	return jogadas_tam;
}

Jogada* JogadaLista::getJogada( int i ) {
	return jogadas[ i ];
}

