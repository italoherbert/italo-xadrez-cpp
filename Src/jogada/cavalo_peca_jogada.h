
#ifndef CAVALO_PECA_JOGADA_H
#define CAVALO_PECA_JOGADA_H

#include "../logica/jogada_lista.h"
#include "../logica/jogo.h"
#include "../logica/pecas.h"
#include "peca_jogada.h"

class CavaloPecaJogada : public PecaJogada {
	
	private:
		void addJogada( Jogo* jogo, JogadaLista* lista, Pecas* pecas, int x, int y, bool isComp );

	public:
		void calculaJogadasPossiveis( PecaJogadaParams* params );
		
};

#endif
