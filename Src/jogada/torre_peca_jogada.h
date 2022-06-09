
#ifndef TORRE_PECA_JOGADA_H
#define TORRE_PECA_JOGADA_H

#include "peca_jogada.h"

class TorrePecaJogada : public PecaJogada {
	
	private:
		bool addJogada( Jogo* jogo, JogadaLista* lista, int posX, int posY, bool isComp );
	
	public:
		void calculaJogadasPossiveis( PecaJogadaParams* params );
	
};

#endif
