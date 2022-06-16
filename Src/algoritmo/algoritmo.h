
#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "../logica/jogada.h"
#include "../logica/jogada_roque.h"
#include "../logica/jogo.h"
#include "../logica/peca.h"

#include <vector>
#include <iostream>

using namespace std;

typedef struct MiniMaxNo {
	Jogada* jogada;
	int posX;
	int posY;
	float peso;
	struct MiniMaxNo* ant;
	struct MiniMaxNo* prox;
}MinMaxNo;

typedef struct MiniMaxNoLista {
	MiniMaxNo* no;
	struct MiniMaxNoLista* prox;
} MiniMaxLista;

class Algoritmo {
	
	private:
		Peca* jogPecas[ Jogo::N_PECAS ];
		Peca* compPecas[ Jogo::N_PECAS ];

	protected:
		Jogo* jogo;

		Peca* sorteiaPeca( Peca* vetor[ Jogo::N_PECAS ], Peca* jps[ Jogo::N_PECAS], Peca* cps[ Jogo::N_PECAS ], bool isComp );
		Jogada* sorteiaPecaJogada( Peca* peca, Peca* jps[ Jogo::N_PECAS], Peca* cps[ Jogo::N_PECAS ], bool isComp );
		void sorteiaJogada( int* posX, int* posY, Jogada** jogada, Peca* jps[ Jogo::N_PECAS ], Peca* cps[ Jogo::N_PECAS ], bool isComp );

		float calculaPeso( Peca* peca );

		MiniMaxNo* minimax( MiniMaxNoLista** nosLista, MiniMaxNo* no, bool isComp, int nivel, float alpha, float beta );
		void limpaMiniMaxArvoreELs( MiniMaxNoLista* no );

		void efetuaJogadas( MiniMaxNo* no, Peca* jps[Jogo::N_PECAS], Peca* cps[Jogo::N_PECAS] );

		float move(
				Peca* jps[ Jogo::N_PECAS ],
				Peca* cps[ Jogo::N_PECAS ],
				Peca* p,
				Jogada* jogada,
				bool isComp,
				bool* isXeque );

	public:
		Algoritmo( Jogo* jogo );

		virtual ~Algoritmo() {}

		void calculaMelhorJogada( int* posX, int* posY, Jogada** jogada );
	
};

#endif
