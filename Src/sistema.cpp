
#include "sistema.h"

Sistema::Sistema() {
	this->drv = new DriverAdapter();

	this->gui = new GUI( drv );
	this->jogo = new Jogo( drv );

	this->drv->setJogoEGUI( gui, jogo );

	this->aberturaGrafico = new AberturaGrafico( gui );
	this->jogoGrafico = new JogoGrafico( jogo, gui );

	this->audio = new JogoAudio();

	this->algoritmoGerenciador = new AlgoritmoGerenciador( jogo );
	this->animacao = new Animacao( jogo );

	this->guiControlador = new GUI_Controlador( this );
	this->aberturaGraficoControlador = new AberturaGraficoControlador( this );
	this->jogoGraficoControlador = new JogoGraficoControlador( this );

	gui->setGUIListener( guiControlador );
	gui->setAberturaGraficoListener( aberturaGraficoControlador );
	gui->setJogoGraficoListener( jogoGraficoControlador );

	gui->setAberturaGrafico( aberturaGrafico );
	gui->setJogoGrafico( jogoGrafico );
}

Sistema::~Sistema() {
	delete jogo;
	delete drv;
	delete aberturaGrafico;
	delete jogoGrafico;
	delete audio;
	delete algoritmoGerenciador;
	delete animacao;

	delete guiControlador;
	delete aberturaGraficoControlador;
	delete jogoGraficoControlador;
}

void Sistema::inicia() {
	aberturaGrafico->inicializa();
	jogoGrafico->inicializa();
	audio->inicializa();

	jogo->reinicia();
	audio->reinicia();
	gui->reinicia();

	int graficoJogadorNivel = drv->getAberturaNivel( jogo->getNivel( false ) );
	int graficoComputadorNivel = drv->getAberturaNivel( jogo->getNivel( true ) );

	aberturaGrafico->setJogadorUmTipo( graficoJogadorNivel );
	aberturaGrafico->setJogadorDoisTipo( graficoComputadorNivel );
}

void Sistema::finaliza() {
	aberturaGrafico->finaliza();
	jogoGrafico->finaliza();
	audio->finaliza();
}

void Sistema::exec() {
	gui->executa( "Jogo de Xadrez", Consts::JANELA_LARGURA, Consts::JANELA_ALTURA );
}

Jogo* Sistema::getJogo() {
	return jogo;
}

DriverAdapter* Sistema::getJogoDriver() {
	return drv;
}

GUI* Sistema::getGUI() {
	return gui;
}

AberturaGrafico* Sistema::getAberturaGrafico() {
	return aberturaGrafico;
}

JogoGrafico* Sistema::getJogoGrafico() {
	return jogoGrafico;
}

Animacao* Sistema::getAnimacao() {
	return animacao;
}

JogoAudio* Sistema::getJogoAudio() {
	return audio;
}

AlgoritmoGerenciador* Sistema::getAlgoritmoGerenciador() {
	return algoritmoGerenciador;
}


