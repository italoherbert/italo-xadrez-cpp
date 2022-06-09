
#include "tela_driver_adapter.h"

#include "consts.h"

TelaDriverAdapter::TelaDriverAdapter( GUI* gui ) {
	this->gui = gui;
}

double TelaDriverAdapter::getFatorCelulaDIM() {
	return Consts::FATOR_CELULA_DIM;
}

int TelaDriverAdapter::getTelaLargura() {
	int l, a;
	
	gui->carregaTelaDIM( &l, &a );
	
	return l;
}

int TelaDriverAdapter::getTelaAltura() {
	int l, a;
	
	gui->carregaTelaDIM( &l, &a );
	
	return a;
}
