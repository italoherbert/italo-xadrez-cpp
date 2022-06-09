
#ifndef JOGADA_UTIL_H
#define JOGADA_UTIL_H

#include "../logica/jogada_lista.h"
#include "../logica/peca.h"
#include "../logica/pecas.h"

class JogadaUtil {	
	
	public:
		virtual void calculaJogadasPossiveis( JogadaLista* lista, Pecas* pecas, int posX, int posY, int tipo, bool isComp, bool isCaptura ) = 0;	
		
		virtual void filtraJogadas( JogadaLista* lista, int posX, int posY, bool isComp ) = 0;

};

#endif
