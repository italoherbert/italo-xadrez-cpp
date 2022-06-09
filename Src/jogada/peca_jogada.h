
#ifndef PECA_JOGADA_H
#define PECA_JOGADA_H

#include "peca_jogada_params.h"

class PecaJogada {	
	
	public:	
		virtual ~PecaJogada() {}

		virtual void calculaJogadasPossiveis( PecaJogadaParams* params ) = 0;		
	
};

#endif
