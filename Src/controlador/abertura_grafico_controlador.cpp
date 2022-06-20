
#include "abertura_grafico_controlador.h"

AberturaGraficoControlador::AberturaGraficoControlador( Sistema* sistema ) {
	this->sistema = sistema;
}

void AberturaGraficoControlador::mousePressionado( int x, int y ) {
	GUI* gui = sistema->getGUI();
	Jogo* jogo = sistema->getJogo();
	JogoDriverAdapter* jdrv = sistema->getJogoDriver();
	AberturaGrafico* aberturaGrafico = sistema->getAberturaGrafico();

	JogoAudio* audio = sistema->getJogoAudio();

	if ( aberturaGrafico->isMouseJogadorUmOpBT( x, y ) ) {
		jogo->incNivel( false );
		int nivel = jogo->getNivel( false );

		aberturaGrafico->setJogadorUmTipo( jdrv->getAberturaNivel( nivel ) );
	} else if ( aberturaGrafico->isMouseJogador2OpBT( x, y ) ) {
		jogo->incNivel( true );
		int nivel = jogo->getNivel( true );

		aberturaGrafico->setJogadorDoisTipo( jdrv->getAberturaNivel( nivel ) );
	} else if ( aberturaGrafico->isMouseJogarBT( x, y ) ) {
		aberturaGrafico->sobreOpcao( AberturaGrafico::OPCAO_JOGAR );
		
		audio->setMusica( JogoAudio::AUDIO_FUNDO_JOGO );
		gui->setCursorTipo( GUI::CURSOR_SETA );
		gui->setGraficoTipo( GUI::JOGO_GRAFICO );
	}
}

void AberturaGraficoControlador::mouseSobre( int x, int y ) {
	GUI* gui = sistema->getGUI();
	AberturaGrafico* aberturaGrafico = sistema->getAberturaGrafico();

	bool mouseEm = true;
	if ( aberturaGrafico->isMouseJogadorUmOpBT( x, y ) ) {
		aberturaGrafico->sobreOpcao( AberturaGrafico::OPCAO_SET_TIPO_JOGADOR );
	} else if ( aberturaGrafico->isMouseJogador2OpBT( x, y ) ) {
		aberturaGrafico->sobreOpcao( AberturaGrafico::OPCAO_SET_TIPO_COMPUTADOR );
	} else if ( aberturaGrafico->isMouseJogarBT( x, y ) ) {
		aberturaGrafico->sobreOpcao( AberturaGrafico::OPCAO_JOGAR );
	} else {
		aberturaGrafico->sobreOpcao( AberturaGrafico::NAO_OPCAO );
		mouseEm = false;
	}			
		
	if ( mouseEm )		
		gui->setCursorTipo( GUI::CURSOR_MAOZINHA );
	else gui->setCursorTipo( GUI::CURSOR_SETA );
}

void AberturaGraficoControlador::teclaPressionada( int tecla ) {
	
}
