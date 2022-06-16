#include "peao_peca_jogada.h"

#include <cstdlib>

#include "../jogada_en_passant.h"
#include "../jogada_lista.h"
#include "../jogo.h"

void PeaoPecaJogada::calculaJogadasPossiveis( PecaJogadaParams* params ) {		
	Jogo* jogo = params->getJogo();
	JogadaLista* lista = params->getJogadas();
	int posX = params->getPosX();
	int posY = params->getPosY();
	bool isComp = params->getIsComp();
	Pecas* pecas = params->getPecas();
	
	Peca* peca = pecas->getPeca( posX, posY );	
	if ( isComp != peca->isDeComp() ) 
		return;

	int x = posX;
	int y = posY + ( isComp ? 1 : -1 );
		
	if ( jogo->isPosicaoValida( x, y ) ) {	
		peca = pecas->getPeca( x, y );				
		if ( peca == NULL )	{		
			lista->addJogada( x, y, NULL );						
		
			bool eh_primeira_jogada = ( isComp ? posY == 1 : posY == 6 );
			if ( eh_primeira_jogada ) {
				y += ( isComp ? 1 : -1 );
				
				if ( jogo->isPosicaoValida( x, y ) ) {			
					peca = pecas->getPeca( x, y );
					if ( peca == NULL )
						lista->addJogada( x, y, NULL );
				}
			}
		}
	}
	
	y = posY + ( isComp ? 1 : -1 );
	x = posX - 1;
				
	if ( jogo->isPosicaoValida( x, y ) ) {			
		if ( isComp ) {			
			peca = pecas->getJogadorPeca( x, y );		
			if ( peca != NULL )
				lista->addJogada( x, y, peca );
		} else {
			peca = pecas->getComputadorPeca( x, y );
			if ( peca != NULL)
				lista->addJogada( x, y, peca );
		}
	}
		
	x = posX + 1;
			
	if ( jogo->isPosicaoValida( x, y ) ) {			
		if ( isComp ) {			
			peca = pecas->getJogadorPeca( x, y );		
			if ( peca != NULL )
				lista->addJogada( x, y, peca );
		} else {
			peca = pecas->getComputadorPeca( x, y );
			if ( peca != NULL )
				lista->addJogada( x, y, peca );
		}
	}

	if ( jogo->getUltimaPeca() != NULL ) {
		if ( jogo->getUltimaPeca()->getTipo() == Jogo::PEAO && jogo->getUltimaPeca()->getMoveuContador() == 1 )	 {		
			peca = pecas->getPeca( posX, posY );
			
			int ultPecaX = jogo->getUltimaPeca()->getPosX();
			int ultPecaY = jogo->getUltimaPeca()->getPosY();
			Peca* ultPeca = pecas->getPeca( ultPecaX, ultPecaY );
			if ( ultPeca != NULL ) {	
				if ( isComp ) {	
					Peca* peca = pecas->getComputadorPeca( posX, posY );
					if ( peca->getPosY() == 4 && ultPeca->getPosY() == 4 )
						if ( ultPeca->getPosX() == peca->getPosX() - 1 || ultPeca->getPosX() == peca->getPosX() + 1 )
							lista->addJogada( new JogadaEnPassant( ultPeca->getPosX(), ultPeca->getPosY() + 1, ultPeca ) );
				} else {	
					Peca* peca = pecas->getJogadorPeca( posX, posY );		
					if ( peca->getPosY() == 3 && ultPeca->getPosY() == 3 )
						if ( ultPeca->getPosX() == peca->getPosX() - 1 || ultPeca->getPosX() == peca->getPosX() + 1 ) 
							lista->addJogada( new JogadaEnPassant( ultPeca->getPosX(), ultPeca->getPosY() - 1, ultPeca ) );
				}
			
			}
			
		}
	}
}

