
#ifndef JOGO_GRAFICO_CONTROLADOR_H
#define JOGO_GRAFICO_CONTROLADOR_H

#include "../sistema.h"

class Sistema;

class JogoGraficoControlador : public JogoGraficoListener {
	
	private:
		Peca* pecaSelecionada;
		bool isMensagemDelay;
		
		Sistema* sistema;
		
		bool selecionaPeca( int posX, int posY, bool isComp );
		bool processaJogada( int posX, int posY );		
		void processaMensagem();
		
		void verificaXequeEXequeMate( bool moveu );

	public:
		JogoGraficoControlador( Sistema* sistema );
		
		void executando();
		
		void mousePressionado( int x, int y );
		void teclaPressionada( int tecla );
};

#endif
