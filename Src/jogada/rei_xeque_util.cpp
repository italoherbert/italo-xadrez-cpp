/*
#include "rei_xeque_util.h"

bool ReiXequeUtil::isReiEmCheque( JogoGerenciador* jGer, 
			Peca* pecas[Jogo::N_PECAS], Peca* outras[Jogo::N_PECAS], bool isComp ) {
		
	for( int i = 0; i < Jogo::N_PECAS; i++ ) {
		Peca* peca = outras[ i ];
		JogadaLista* lista = new JogadaLista();
				
		jGer->calculaJogadasPossiveis( lista, peca->getPosX(), peca->getPosY(), isComp );
		
		int tam = lista->getTam();
		for( int j = 0; j < tam; j++ ) {
			Jogada* jogada = lista->getJogada( j );
			if( jogada->getCaptura() != NULL )
				if ( jogada->getCaptura()->getTipo() == Jogo::REI )
					return true;
		}		
	}
	
	return false;
}
*/
