
#include "jogo_driver_adapter.h"
#include "consts.h"

#include "grafico/abertura_grafico.h"

JogoDriverAdapter::JogoDriverAdapter( GUI* gui ) {
	this->gui = gui;
}

int JogoDriverAdapter::getAberturaNivel( int nivel ) {
	switch( nivel ) {
		case Jogo::NIVEL_JORADOR: return AberturaGrafico::HUMANO;
		case Jogo::NIVEL_FACIL: return AberturaGrafico::FACIL;
		case Jogo::NIVEL_NORMAL: return AberturaGrafico::NORMAL;
		case Jogo::NIVEL_DIFICIL: return AberturaGrafico::DIFICIL;
		default: return 0;
	}
}

double JogoDriverAdapter::getFatorCelulaDIM() {
	return Consts::FATOR_CELULA_DIM;
}

int JogoDriverAdapter::getTelaLargura() {
	int l, a;
	
	gui->carregaTelaDIM( &l, &a );
	
	return l;
}

int JogoDriverAdapter::getTelaAltura() {
	int l, a;
	
	gui->carregaTelaDIM( &l, &a );
	
	return a;
}
