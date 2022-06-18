
#ifndef JOGADA_LISTA_H
#define JOGADA_LISTA_H

#include "jogada.h"
#include "peca.h"

class JogadaLista {
			
	private:
		Jogada* jogadas[ 36 ];		
		int jogadas_tam;
			
	public:
		const static int MAX_CELULAS = 36;
		
		JogadaLista();
		~JogadaLista();
	
		void addJogada( int posX, int posY, Peca* captura, int tipo );
		void addJogada( int posX, int posY, Peca* captura );
		void addJogada( Jogada* jogada );	
		
		void limpaJogadas();
		
		void copia( JogadaLista* lista );
		
		int getTam();
		
		Jogada* getJogada( int i );		
		
};

#endif
