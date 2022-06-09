
#ifndef PEAO_PECA_JOGADA_H
#define PEAO_PECA_JOGADA_H

#include "peca_jogada.h"
#include "peca_jogada_params.h"

class PeaoPecaJogada : public PecaJogada {
	
	public:
		void calculaJogadasPossiveis( PecaJogadaParams* params );
							
};

#endif
