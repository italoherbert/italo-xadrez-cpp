
#ifndef JOGO_GRAFICO_CONTROLADOR_H
#define JOGO_GRAFICO_CONTROLADOR_H

#include "../algoritmo/algoritmo.h"
#include "../animacao/animacao.h"
#include "../audio/jogo_audio.h"
#include "../grafico/jogo_grafico.h"
#include "../gui/GUI.h"
#include "../gui/GUI_Listener.h"
#include "../jogada/jogada_gerenciador.h"
#include "../logica/jogo.h"

class JogoGraficoControlador : public JogoGraficoListener {
	
	private:
		Jogo* jogo;
		GUI* gui;
		
		JogoGrafico* jogoGrafico;
		JogoAudio* audio;
		
		JogadaGerenciador* jGer;
		Algoritmo* algoritmo;
		Animacao* animacao;		
		
		Peca* pecaSelecionada;
		
		bool selecionaPeca( int posX, int posY, bool isComp );
		bool processaJogada( int posX, int posY );		
		void processaMensagem();
		
		void verificaXequeEXequeMate( bool moveu );
		
		bool isMensagemDelay;
		
	public:
		JogoGraficoControlador( Jogo* jogo, JogadaGerenciador* jGer, 
			Algoritmo* alg, Animacao* anim, 
			GUI* gui, JogoGrafico* jG, JogoAudio* audio );
		
		void executando();
		
		void mousePressionado( int x, int y );
		void teclaPressionada( int tecla );
};

#endif
