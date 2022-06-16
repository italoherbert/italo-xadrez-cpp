
#ifndef PECA_JOGADA_PARAMS_H
#define PECA_JOGADA_PARAMS_H

#include "jogo.h"
#include "jogada_lista.h"
#include "pecas.h"

class Jogo;

class PecaJogadaParams {
	
	private:
		Jogo* jogo;
		JogadaLista* lista;
		int posX;
		int posY;
		bool isComp;
		bool isCaptura;				
		
		Pecas* pecas;
					
	public:
		PecaJogadaParams(
				Jogo* jogo,
				JogadaLista* lista,
				Pecas* pecas,
				int posX, int posY, bool isComp, bool isCaptura );

		Jogo* getJogo();
		JogadaLista* getJogadas();
		int getPosX();
		int getPosY();
		bool getIsComp();
		bool getIsCaptura();
	
		Pecas* getPecas();
	
};

#endif
