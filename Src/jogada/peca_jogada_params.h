
#ifndef PECA_JOGADA_PARAMS_H
#define PECA_JOGADA_PARAMS_H

#include "../logica/jogada_lista.h"
#include "../logica/jogo.h"
#include "../logica/pecas.h"
#include "jogada_util.h"

class PecaJogadaParams {
	
	private:
	 	Jogo* jogo;
	 	JogadaUtil* jUtil;
		JogadaLista* lista;
		int posX;
		int posY;
		bool isComp;
		bool isCaptura;				
		
		Pecas* pecas;
					
	public:
		PecaJogadaParams( JogadaUtil* jUtil, Jogo* jogo, JogadaLista* lista, Pecas* pecas, int posX, int posY, bool isComp, bool isCaptura );
						
		JogadaUtil* getJogadaUtil();				
		Jogo* getJogo();
		JogadaLista* getJogadas();
		int getPosX();
		int getPosY();
		bool getIsComp();
		bool getIsCaptura();
	
		Pecas* getPecas();
	
};

#endif
