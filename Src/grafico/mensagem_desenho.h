
#ifndef MENSAGEM_DESENHO_H
#define MENSAGEM_DESENHO_H

#include <iostream>
#include <SDL2/SDL.h>

#include "../gui/GUI.h"
#include "../logica/jogo.h"

class MensagemDesenho {
	
	private:
		std::string mensagem;
	
	public:
		MensagemDesenho();
		
		void desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor );
		
		void setMensagem( std::string msg );
		void removeMensagem();
		
		bool isMensagemVazia();

};

#endif
