
#include "consts.h"
#include "driver_adapter.h"

#include "grafico/abertura_grafico.h"

void DriverAdapter::setJogoEGUI( GUI* gui, Jogo* jogo, JogoGrafico* jogoGrafico ) {
	this->gui = gui;
	this->jogo = jogo;
	this->jogoGrafico = jogoGrafico;
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

bool DriverAdapter::isFim() {
	return jogo->isFim();
}

void DriverAdapter::setFim( bool fim ) {
	jogo->setFim( fim );
}
