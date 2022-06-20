
#ifndef ABERTURA_GRAFICO_H
#define ABERTURA_GRAFICO_H

#include <SDL2/SDL.h>

#include "../gui/grafico.h"
#include "../gui/GUI.h"
#include "../logica/jogo.h"

class AberturaGrafico : public Grafico {

	private:
		GUI* gui;	
		
		SDL_Surface* aberturaIMG;

		SDL_Color* corTexto = new SDL_Color;
		SDL_Color* corFundo = new SDL_Color;
		
		SDL_Color* corTextoBTSobre = new SDL_Color;
		SDL_Color* corFundoBTSobre = new SDL_Color;
			
		SDL_Rect* menuRet = nullptr;
		SDL_Rect* opcoesTituloRet = nullptr;
		SDL_Rect* jogadorOpcaoRet = nullptr;
		SDL_Rect* computadorOpcaoRet = nullptr;
		SDL_Rect* jogarBTOpcaoRet = nullptr;

		SDL_Rect* jogadorTextoOpcaoRet = nullptr;
		SDL_Rect* computadorTextoOpcaoRet = nullptr;
		SDL_Rect* jogarBTTextoOpcaoRet = nullptr;

		SDL_Color* jogadorTextoOpcaoCor = new SDL_Color;
		SDL_Color* computadorTextoOpcaoCor = new SDL_Color;
		SDL_Color* jogarBTTextoOpcaoCor = new SDL_Color;

		SDL_Color* jogadorFundoOpcaoCor = new SDL_Color;
		SDL_Color* computadorFundoOpcaoCor = new SDL_Color;
		SDL_Color* jogarBTFundoOpcaoCor = new SDL_Color;

		int jogador1Tipo = DIFICIL;
		int jogador2Tipo = DIFICIL;

		char maxOpcaoTextDefaultStr[ 127 ];
		char opcoesStr[ 127 ];
		char jogarStr[ 127 ];
		char humanoStr[ 127 ];
		char facilStr[ 127 ];
		char normalStr[ 127 ];
		char dificilStr[ 127 ];

		char fontePath[ 127 ];

		void desenhaMenu( SDL_Renderer* pintor );	
		void desenhaTexto( SDL_Renderer* pintor, SDL_Rect* ret, char* rotulo, SDL_Color* cor );
		void desenhaBTFundo( SDL_Renderer* pintor, SDL_Rect* ret, SDL_Color* cor );
		
		bool isMouseEmBT( SDL_Rect* btFundoRet, int mouseX, int mouseY );

	public:
		const static int NAO_OPCAO = 0;
		const static int OPCAO_SET_TIPO_JOGADOR = 1;
		const static int OPCAO_SET_TIPO_COMPUTADOR = 2;
		const static int OPCAO_JOGAR = 3;

		const static int HUMANO = 0;
		const static int FACIL = 1;
		const static int NORMAL = 2;
		const static int DIFICIL = 3;

		const int MENSAGEM_FONTE_TAM = 24;

		const int MENU_ABERTURA_ESP = 10;

		const int MENU_ABERTURA_ESP_BT_H = 50;
		const int MENU_ABERTURA_ESP_BT_V = 10;

		const int MENU_ABERTURA_LARGURA_FUNDO_TEXTO = 300;

		AberturaGrafico( GUI* gui );
		
		void inicializa();
		void finaliza();
		
		void desenha( SDL_Renderer* pintor ); 	
	
		void sobreOpcao( int opcao );
		char* getJogadorStringTipo( int tipo );
	
		bool isMouseJogadorUmOpBT( int mouseX, int mouseY );		
		bool isMouseJogador2OpBT( int mouseX, int mouseY );		
		bool isMouseJogarBT( int mouseX, int mouseY );					

		void setJogadorUmTipo( int tipo );
		void setJogadorDoisTipo( int tipo );
};

#endif
