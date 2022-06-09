
#ifndef TELA_DRIVER_ADAPTER_H
#define TELA_DRIVER_ADAPTER_H

#include "gui/GUI.h"
#include "logica/tela_driver.h"

class TelaDriverAdapter : public TelaDriver {
	
	private:
		GUI* gui;
		
	public:
		TelaDriverAdapter( GUI* gui );
		
		int getTelaLargura();
		int getTelaAltura();
		
		double getFatorCelulaDIM();
	
};

#endif
