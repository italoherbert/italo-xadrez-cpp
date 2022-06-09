
#ifndef GUI_CONTROLADOR_H
#define GUI_CONTROLADOR_H

#include "../audio/jogo_audio.h"
#include "../grafico/abertura_grafico.h"
#include "../grafico/jogo_grafico.h"
#include "../gui/GUI_Listener.h"
#include "../logica/jogo.h"

class GUI_Controlador : public GUI_Listener {
	
	private:
		Jogo* jogo;
		GUI* gui;
		
		JogoGrafico* jogoGrafico;
		AberturaGrafico* aberturaGrafico;
		JogoAudio* audio;
								
	public:
		GUI_Controlador( Jogo* jogo, GUI* gui, AberturaGrafico* aG, JogoGrafico* jG, JogoAudio* audio );

		void inicializou();
		void finalizando();
		
		void janelaFechada();
};

#endif
