
#ifndef ABERTURA_GRAFICO_H
#define ABERTURA_GRAFICO_H

#include <SDL2/SDL.h>

#include "../gui/grafico.h"
#include "../gui/GUI.h"
#include "../logica/jogo.h"

struct AberturaRet {
	int x;
	int y;
	int largura;
	int altura;	
};

struct AberturaTexto {
	AberturaRet textoRet;
	char rotulo[127];	
	SDL_Color cor;
};

struct AberturaBT {
	AberturaRet fundoRet;	
	AberturaTexto texto;	
	
	SDL_Color corFundo;
};

class AberturaGrafico : public Grafico {		
		
	private:
		GUI* gui;	
		
		SDL_Surface* aberturaIMG;				 	
		SDL_Color corTexto;
		SDL_Color corFundo;
		
		SDL_Color corTextoBTSobre;
		SDL_Color corFundoBTSobre;
			
		AberturaRet menuRet;
		AberturaTexto opcoesTextoRet;
		AberturaBT facilBT;
		AberturaBT normalBT;
		AberturaBT dificilBT;				
					
		void desenhaMenu( SDL_Renderer* pintor );	
		void desenhaTexto( SDL_Renderer* pintor, AberturaTexto at );	
		void desenhaBTFundo( SDL_Renderer* pintor, AberturaBT bt );
		
		bool isMouseEmBT( AberturaRet btFundoRet, int mouseX, int mouseY );
		
	public:				
		AberturaGrafico( GUI* gui );
		
		void inicializa();
		void finaliza();
		
		void desenha( SDL_Renderer* pintor ); 	
	
		void sobreNivel( int nivel );
	
		bool isMouseEmFacilBT( int mouseX, int mouseY );		
		bool isMouseEmNormalBT( int mouseX, int mouseY );		
		bool isMouseEmDificilBT( int mouseX, int mouseY );					
	
};

#endif
