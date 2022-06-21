
#ifndef JOGO_GRAFICO_CONTROLADOR_H
#define JOGO_GRAFICO_CONTROLADOR_H

#include "../sistema.h"

class Sistema;

class JogoGraficoControlador : public JogoGraficoListener {
	
	private:
		const long NO_START = -1;

		const long NO_DELAY = -1;
		const long MENSAGEM_DELAY = 2;
		const long FIM_JOGO_MENSAGEM_DELAY = 4;

		Peca* pecaSelecionada = nullptr;
		long mensagemTempoStart = -1;
		
		bool reiniciarJogo = false;

		Sistema* sistema;
		
		bool selecionaPeca( int posX, int posY, bool isComp );
		bool processaJogada( int posX, int posY );		

		void setMensagem( std::string mensagem, long delay );
		void removeMensagem();
		
		void verificaSeXeque();
		int verificaEProcessaXequeMate();

	public:
		JogoGraficoControlador( Sistema* sistema );
		
		void executando();
		
		void mousePressionado( int x, int y );
		void teclaPressionada( int tecla );
};

#endif
