
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

		SDL_Color* opcaoTextoCor = new SDL_Color;
		SDL_Color* opcaoFundoCor = new SDL_Color;
		SDL_Color* opcaoTextoSobreCor = new SDL_Color;
		SDL_Color* opcaoFundoSobreCor = new SDL_Color;
		SDL_Color* opcaoBordaCor = new SDL_Color;
		
		SDL_Color* btnFundoCor = new SDL_Color;
		SDL_Color* btnTextoCor = new SDL_Color;
		SDL_Color* btnTextoSobreCor = new SDL_Color;
		SDL_Color* btnFundoSobreCor = new SDL_Color;
		SDL_Color* btnBordaCor = new SDL_Color;
			
		SDL_Rect* jogador1TextoRet = nullptr;
		SDL_Rect* jogador2TextoRet = nullptr;

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

		SDL_Color* textoCor = new SDL_Color;

		int jogador1Tipo = DIFICIL;
		int jogador2Tipo = DIFICIL;

		char opcoesStr[ 127 ];
		char jogarStr[ 127 ];
		char humanoStr[ 127 ];
		char facilStr[ 127 ];
		char normalStr[ 127 ];
		char dificilStr[ 127 ];
		char jogadorStr[ 127 ];
		char computadorStr[ 127 ];

		void desenhaMenu( SDL_Renderer* pintor );	
		void desenhaTexto( SDL_Renderer* pintor, SDL_Rect* ret, char* rotulo, SDL_Color* cor );
		void desenhaBTFundo( SDL_Renderer* pintor, SDL_Rect* ret, SDL_Color* cor, SDL_Color* bordaCor );
		
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

		const int MENU_ABERTURA_ESP_OP_H = 20;
		const int MENU_ABERTURA_ESP_OP_ROTULO_W = 20;

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
