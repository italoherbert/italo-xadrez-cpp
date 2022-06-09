
#ifndef TELA_DRIVER_H
#define TELA_DRIVER_H

class TelaDriver {
	
	public:
		virtual int getTelaLargura() = 0;
		virtual int getTelaAltura() = 0;
		
		virtual double getFatorCelulaDIM() = 0;
	
};

#endif
