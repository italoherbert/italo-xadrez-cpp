
#ifndef RAINHA_PECA_JOGADA_H
#define RAINHA_PECA_JOGADA_H

#include "bispo_peca_jogada.h"
#include "peca_jogada.h"
#include "torre_peca_jogada.h"

class RainhaPecaJogada : public PecaJogada {
	
	private:
		BispoPecaJogada* bispoPJ;
		TorrePecaJogada* torrePJ;
		
	public:
		RainhaPecaJogada( TorrePecaJogada* torrePJ, BispoPecaJogada* bispoPJ );
		
		void calculaJogadasPossiveis( PecaJogadaParams* params );
			
};

#endif
