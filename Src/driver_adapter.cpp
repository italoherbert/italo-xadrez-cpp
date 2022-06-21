
#include "consts.h"
#include "driver_adapter.h"

#include "grafico/abertura_grafico.h"

void DriverAdapter::setJogoEGUI( GUI* gui, Jogo* jogo, JogoGrafico* jogoGrafico ) {
	this->gui = gui;
	this->jogo = jogo;
	this->jogoGrafico = jogoGrafico;
}


int DriverAdapter::getAberturaNivel( int nivel ) {
	switch( nivel ) {
		case Jogo::NIVEL_HUMANO: return AberturaGrafico::HUMANO;
		case Jogo::NIVEL_FACIL: return AberturaGrafico::FACIL;
		case Jogo::NIVEL_NORMAL: return AberturaGrafico::NORMAL;
		case Jogo::NIVEL_DIFICIL: return AberturaGrafico::DIFICIL;
		default: return 0;
	}
}

int DriverAdapter::getInfoPainelAltura() {
	return jogoGrafico->getInfoDesenho()->getPainelAltura();
}

double DriverAdapter::getFatorCelulaDIM() {
	return Consts::FATOR_CELULA_DIM;
}

int DriverAdapter::getTelaLargura() {
	int l, a;
	
	gui->carregaTelaDIM( &l, &a );
	
	return l;
}

int DriverAdapter::getTelaAltura() {
	int l, a;
	
	gui->carregaTelaDIM( &l, &a );
	
	return a;
}

bool DriverAdapter::isPausa() {
	return jogo->isPausa();
}