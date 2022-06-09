
#ifndef DESENHO_H
#define DESENHO_H

#include <SDL2/SDL.h>

#include "../gui/GUI.h"
#include "../logica/jogo.h"

class Desenho {
	
	public:
		virtual void desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor ) = 0;
	
};

#endif
