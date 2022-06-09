
#ifndef BISPO_PECA_JOGADA_H
#define BISPO_PECA_JOGADA_H

#include "peca_jogada.h"

class BispoPecaJogada : public PecaJogada {
	
	private:
		bool addJogada( Jogo* jogo, JogadaLista* lista, int posX, int posY, bool isComp );
	
	public:
		void calculaJogadasPossiveis( PecaJogadaParams* params );
	
};

#endif
