
#ifndef ABERTURA_GRAFICO_CONTROLADOR_H
#define ABERTURA_GRAFICO_CONTROLADOR_H

#include "../audio/jogo_audio.h"
#include "../grafico/abertura_grafico.h"
#include "../gui/abertura_grafico_listener.h"
#include "../gui/GUI.h"
#include "../logica/jogo.h"

class AberturaGraficoControlador : public AberturaGraficoListener {
	
	private:
		Jogo* jogo;
		GUI* gui;
		
		AberturaGrafico* aberturaGrafico;
		JogoAudio* audio;	
	public:		
		AberturaGraficoControlador( Jogo* jogo, GUI* gui, AberturaGrafico* aG, JogoAudio* audio );
		virtual ~AberturaGraficoControlador() {}

		void mouseSobre( int x, int y );
		void mousePressionado( int x, int y );
		void teclaPressionada( int tecla );
	
};

#endif
