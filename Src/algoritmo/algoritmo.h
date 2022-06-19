
#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "../logica/jogada.h"
#include "../logica/jogada_roque.h"
#include "../logica/jogo.h"
#include "../logica/peca.h"

#include <vector>
#include <iostream>

using namespace std;

typedef struct MiniMaxNoLista MiniMaxNoLista;

typedef struct MiniMaxNo {
	Jogada* jogada;
	int posX;
	int posY;
	float peso;
	struct MiniMaxNo* pai;
	struct MiniMaxNoLista* filhos;
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

		MiniMaxNo* minimax( MiniMaxNo* no, bool isMaximizador, int nivel, float alpha, float beta, bool isComp );

		float calculaPeso( Peca* peca );

		void limpaMiniMaxArvore( MiniMaxNo* no );
		void efetuaJogadas( MiniMaxNo* no, Peca* jps[Jogo::N_PECAS], Peca* cps[Jogo::N_PECAS] );

		float move( Peca**, Peca**, Peca* p, Jogada* jogada, bool isComp );

		bool tentaDominioDoCentro( int* posX, int* posY, Jogada** jogada, Peca** jps, Peca** cps, bool isComp );
		bool sorteiaJogada( int* posX, int* posY, Jogada** jogada, Peca** jps, Peca** cps, bool isComp );

		Peca* sorteiaPeca( Peca** jps, Peca** cps, bool isComp );
		Jogada* sorteiaPecaJogada( Peca* peca, Peca** jps, Peca** cps, bool isComp );


	public:
		Algoritmo( Jogo* jogo );

		virtual ~Algoritmo() {}

		void calculaMelhorJogada( int* posX, int* posY, Jogada** jogada, bool isComp );
	
};

#endif
