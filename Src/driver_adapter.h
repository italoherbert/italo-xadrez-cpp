
#ifndef TELA_DRIVER_ADAPTER_H
#define TELA_DRIVER_ADAPTER_H

#include "gui/GUI.h"
#include "gui/GUI_Driver.h"

#include "logica/jogo.h"
#include "logica/jogo_driver.h"

class DriverAdapter : public JogoDriver, public GUI_Driver {
	
	private:
		GUI* gui;
		Jogo* jogo;
		
	public:
		void setJogoEGUI( GUI* gui, Jogo* jogo );
		
		int getTelaLargura();
		int getTelaAltura();
		
		double getFatorCelulaDIM();

		int getAberturaNivel( int nivel );

		bool isPausa();
	
};

#endif
