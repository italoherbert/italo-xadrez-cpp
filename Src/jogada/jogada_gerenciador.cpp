#include "jogada_gerenciador.h"

#include <cstdlib>

#include "peca_jogada_params.h"

JogadaGerenciador::JogadaGerenciador( Jogo* jogo ) {
	this->jogo = jogo;
	
	this->peaoPecaJogada = new PeaoPecaJogada();
	this->reiPecaJogada = new ReiPecaJogada();
	this->cavaloPecaJogada = new CavaloPecaJogada();
	this->torrePecaJogada = new TorrePecaJogada();
	this->bispoPecaJogada = new BispoPecaJogada();
	this->rainhaPecaJogada = new RainhaPecaJogada( torrePecaJogada, bispoPecaJogada );
}

JogadaGerenciador::~JogadaGerenciador() {
	delete this->peaoPecaJogada;
	delete this->reiPecaJogada;
	delete this->bispoPecaJogada;
	delete this->torrePecaJogada;
	delete this->bispoPecaJogada;
	delete this->rainhaPecaJogada;
}

void JogadaGerenciador::calculaJogadasPossiveis( JogadaLista* lista, Pecas* pecas, int posX, int posY, int tipo, bool isComp, bool isCaptura ) {						
	PecaJogadaParams* params = new PecaJogadaParams( this, jogo, lista, pecas, posX, posY, isComp, isCaptura );
	switch( tipo ) {		
		case Jogo::PEAO:
			peaoPecaJogada->calculaJogadasPossiveis( params );
			break;
		case Jogo::REI:
			reiPecaJogada->calculaJogadasPossiveis( params );
			break;
		case Jogo::CAVALO:
			cavaloPecaJogada->calculaJogadasPossiveis( params );
			break;
		case Jogo::TORRE:
			torrePecaJogada->calculaJogadasPossiveis( params );
			break;
		case Jogo::BISPO:
			bispoPecaJogada->calculaJogadasPossiveis( params );
			break;
		case Jogo::RAINHA:
			rainhaPecaJogada->calculaJogadasPossiveis( params );
			break;
	}
}

void JogadaGerenciador::filtraJogadas( JogadaLista* lista, int posX, int posY, bool isComp ) {						
	Peca* jogadorPecas[ Jogo::N_PECAS ];
	Peca* computadorPecas[ Jogo::N_PECAS ];				
												
	JogadaLista* jogadas = new JogadaLista();	

	int tam = lista->getTam();
	for( int i = 0; i < tam; i++ ) {					
		jogo->copia_pecas( jogadorPecas, computadorPecas );
		
		Jogada* jogada = lista->getJogada( i );		
		jogo->move( jogadorPecas, computadorPecas, posX, posY, jogada->getPosX(), jogada->getPosY() );																				 						 					
									
		if ( isComp ) {				 						
			if ( !jogo->isReiEmXeque( this, jogadorPecas, jogadorPecas, computadorPecas, false ) )				
				jogadas->addJogada( jogada );												
		} else {
			if ( !jogo->isReiEmXeque( this, computadorPecas, jogadorPecas, computadorPecas, true ) )
				jogadas->addJogada( jogada );																				
		}						
				
		jogo->deleta_pecas( jogadorPecas );
		jogo->deleta_pecas( computadorPecas );
	}				
					
	jogadas->copia( lista );	

	jogo->deleta_jogadas( jogadas );
}

	
