
#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "../jogada/jogada_gerenciador.h"
#include "../logica/jogada.h"
#include "../logica/jogada_roque.h"
#include "../logica/jogo.h"
#include "../logica/peca.h"

class Algoritmo {
	
	private:
		Jogo* jogo;
		JogadaGerenciador* jGer;
		
		int xequeCont;
		int naoXequeCont;
				
		Jogada* jogadasSorteio[ Jogo::N_PECAS * JogadaLista::MAX_CELULAS ];
		Peca* pecasSorteio[ Jogo::N_PECAS * JogadaLista::MAX_CELULAS ];
							
		Peca* sorteiaPeca( Peca* vetor[ Jogo::N_PECAS ], Peca* jogPecas[ Jogo::N_PECAS], Peca* compPecas[ Jogo::N_PECAS ]);
		Jogada* sorteiaJogada( Peca* peca, Peca* jogPecas[ Jogo::N_PECAS], Peca* compPecas[ Jogo::N_PECAS ] );
								
		void sorteiaJogada( int* posX, int* posY, Jogada** jogada, Peca* jogPecas[ Jogo::N_PECAS ], Peca* compPecas[ Jogo::N_PECAS ] );
		
		bool tentaDominioDoCentro( int* posX, int* posY, Jogada** jogada, Peca* jogPecas[ Jogo::N_PECAS ], Peca* compPecas[ Jogo::N_PECAS ] );
		bool tentaDominioDoCentro( Peca* peca, int* posX, int* posY, Jogada** jogada, Peca* jogPecas[ Jogo::N_PECAS ], Peca* compPecas[ Jogo::N_PECAS ] );
		bool isTentarDominioDoCentro( Peca* peca, JogadaLista* lista, Peca* jogPecas[Jogo::N_PECAS], Peca* compPecas[Jogo::N_PECAS] );


		float calculaPeso( Peca* peca );																	
	
	public:
		const static int MAX_XEQUE_CONT = 5;
		
		Algoritmo( Jogo* jogo, JogadaGerenciador* jogadaGerenciador );
		
		void calculaMelhorJogada( int* posX, int* posY, Jogada** jogada );
	
};

#endif
