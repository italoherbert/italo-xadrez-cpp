
#ifndef TELA_DRIVER_ADAPTER_H
#define TELA_DRIVER_ADAPTER_H

#include "gui/GUI.h"
#include "logica/jogo_driver.h"

class JogoDriverAdapter : public JogoDriver {
	
	private:
		GUI* gui;
		
	public:
		JogoDriverAdapter( GUI* gui );
		
		int getTelaLargura();
		int getTelaAltura();
		
		double getFatorCelulaDIM();

		int getAberturaNivel( int nivel );
	
};

#endif
