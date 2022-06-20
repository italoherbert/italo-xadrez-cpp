
#ifndef TABULEIRO_DESENHO_H
#define TABULEIRO_DESENHO_H

#include "desenho.h"

class TabuleiroDesenho {
	
	private:
		const int TABULEIRO_BORDA = 20;

	public:		
		void desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor );
	
};

#endif
