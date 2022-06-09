
#include "cavalo_peca_jogada.h"

#include <cstdlib>


void CavaloPecaJogada::calculaJogadasPossiveis( PecaJogadaParams* params ) {		
	Jogo* jogo = params->getJogo();
	JogadaLista* lista = params->getJogadas();
	int posX = params->getPosX();
	int posY = params->getPosY();
	bool isComp = params->getIsComp();
	Pecas* pecas = params->getPecas();	
		
	int x = posX - 2;
	int y = posY - 1;	
	this->addJogada( jogo, lista, pecas, x, y, isComp );	
		
	x = posX - 2;
	y = posY + 1;	
	this->addJogada( jogo, lista, pecas, x, y, isComp );	
	
	x = posX + 2;
	y = posY - 1;	
	this->addJogada( jogo, lista, pecas, x, y, isComp );	
	
	x = posX + 2;
	y = posY + 1;	
	this->addJogada( jogo, lista, pecas, x, y, isComp );		
	
	x = posX - 1;
	y = posY - 2;
	this->addJogada( jogo, lista, pecas, x, y, isComp );		

	x = posX + 1;
	y = posY - 2;
	this->addJogada( jogo, lista, pecas, x, y, isComp );		

	x = posX - 1;
	y = posY + 2;
	this->addJogada( jogo, lista, pecas, x, y, isComp );		

	x = posX + 1;
	y = posY + 2;
	this->addJogada( jogo, lista, pecas, x, y, isComp );		

}

void CavaloPecaJogada::addJogada( Jogo* jogo, JogadaLista* lista, Pecas* pecas, int x, int y, bool isComp ) {
	if ( jogo->isPosicaoValida( x, y ) )	
		jogo->addJogada( lista, pecas, x, y, isComp );					
}
