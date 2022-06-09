
#ifndef TELA_H
#define TELA_H

#include "tela_driver.h"

class Tela {
	private:
		TelaDriver* driver;
		
	public:
		Tela( TelaDriver* driver );
		
		int getTabuleiroX();
		int getTabuleiroY();
		int getTabuleiroDIM();
		
		int getCelulaX( int x );
		int getCelulaY( int y );
		
		int getCelulaDIM();	
		
		int getX( int posX );
		int getY( int posY );	
			
};

#endif
