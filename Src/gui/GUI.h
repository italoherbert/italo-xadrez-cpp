
#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "../consts.h"
#include "abertura_grafico_listener.h"
#include "grafico.h"
#include "GUI_Listener.h"
#include "jogo_grafico_listener.h"

class GUI {
	private:
		SDL_Window* janela = nullptr;
		SDL_Surface* tela = nullptr;
		SDL_Renderer* pintor = nullptr;
		
		TTF_Font* mensagemFonte = nullptr;
		
		SDL_Cursor* cursorSeta = nullptr;
		SDL_Cursor* cursorMaozinha = nullptr;
		
		GUI_Listener* listener = nullptr;
		AberturaGraficoListener* aberturaGraficoListener = nullptr;
		JogoGraficoListener* jogoGraficoListener = nullptr;
		
		Grafico* aberturaGrafico = nullptr;
		Grafico* jogoGrafico = nullptr;
		
		int graficoTipo = ABERTURA_GRAFICO;
	
	public:
		const static int ABERTURA_GRAFICO = 1;
		const static int JOGO_GRAFICO = 2;
		
		const static int CURSOR_MAOZINHA = 2;
		const static int CURSOR_SETA = 1;
		
		GUI();
		
		void reinicia();
		
		void executa( std::string titulo, int largura, int altura );

		void carregaTelaDIM( int* largura, int* altura );

		void setAberturaGrafico( Grafico* grafico );		
		void setJogoGrafico( Grafico* grafico );
		
		void setGraficoTipo( int tipo );
		void setCursorTipo( int tipo );
		
		void setGUIListener( GUI_Listener* listener );
		void setAberturaGraficoListener( AberturaGraficoListener* listener );
		void setJogoGraficoListener( JogoGraficoListener* listener );
		
		SDL_Surface* getTela();
		TTF_Font* getMensagemFonte();		
};

#endif

