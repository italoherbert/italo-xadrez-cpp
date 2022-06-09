
#include "abertura_grafico_controlador.h"

AberturaGraficoControlador::AberturaGraficoControlador( Jogo* jogo, GUI* gui, AberturaGrafico* aG, JogoAudio* audio ) {
	this->jogo = jogo;
	this->gui = gui;
	this->aberturaGrafico = aG;	
	this->audio = audio;
}

void AberturaGraficoControlador::mousePressionado( int x, int y ) {	
	bool opSelecionada = true;
	if ( aberturaGrafico->isMouseEmFacilBT( x, y ) ) {
		jogo->setNivel( Jogo::NIVEL_FACIL );
	} else if ( aberturaGrafico->isMouseEmNormalBT( x, y ) ) {
		jogo->setNivel( Jogo::NIVEL_NORMAL );
	} else if ( aberturaGrafico->isMouseEmDificilBT( x, y ) ) {
		jogo->setNivel( Jogo::NIVEL_DIFICIL );
	} else {
		opSelecionada = false;
	}	
	
	if ( opSelecionada ) {			
		aberturaGrafico->sobreNivel( Jogo::NIVEL_NENHUM );
		
		audio->setMusica( JogoAudio::AUDIO_FUNDO_JOGO );
		gui->setCursorTipo( GUI::CURSOR_SETA );
		gui->setGraficoTipo( GUI::JOGO_GRAFICO );		
	}
}

void AberturaGraficoControlador::mouseSobre( int x, int y ) {	
	bool mouseEm = true;
	if ( aberturaGrafico->isMouseEmFacilBT( x, y ) ) {
		aberturaGrafico->sobreNivel( Jogo::NIVEL_FACIL );
	} else if ( aberturaGrafico->isMouseEmNormalBT( x, y ) ) {
		aberturaGrafico->sobreNivel( Jogo::NIVEL_NORMAL );
	} else if ( aberturaGrafico->isMouseEmDificilBT( x, y ) ) {
		aberturaGrafico->sobreNivel( Jogo::NIVEL_DIFICIL );
	} else {
		aberturaGrafico->sobreNivel( Jogo::NIVEL_NENHUM );
		mouseEm = false;
	}			
		
	if ( mouseEm )		
		gui->setCursorTipo( GUI::CURSOR_MAOZINHA );
	else gui->setCursorTipo( GUI::CURSOR_SETA );
}

void AberturaGraficoControlador::teclaPressionada( int tecla ) {
	
}
