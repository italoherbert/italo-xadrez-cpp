
#ifndef PECA_H
#define PECA_H

class Peca {
	private:
		int posX;
		int posY;
		
		int animPosX;
		int animPosY;
		int tipo;
		bool deComp;
		bool removida;
		int moveuContador;
		
	public:
		Peca( bool deComp, int tipo, int posX, int posY );
		
		Peca* nova();
		
		bool isIgual( Peca* peca );
		
		int getPosX();
		int getPosY();
		int getAnimPosX();
		int getAnimPosY();
		int getTipo();
		bool isRemovida();
		bool isDeComp();
		int getMoveuContador();
		
		void setPosX( int posX );
		void setPosY( int posY );
		void setAnimPosX( int posX );
		void setAnimPosY( int posY );
		void setTipo( int tipo );
		void setRemovida( bool removida );
		void setMoveuContador( int cont );
};

#endif
