
#include "algoritmo.h"

#include <cstdlib>
#include <cmath>
#include <ctime>

#include "../logica/jogo_pecas.h"

using namespace std;

Algoritmo::Algoritmo( Jogo* jogo ) {
	this->jogo = jogo;
}

void Algoritmo::calculaMelhorJogada( int* posX, int* posY, Jogada** jogada ) {
	MiniMaxNoLista* nosLista = NULL;
	MiniMaxNo* no = this->minimax( &nosLista, NULL, true, 2, INT32_MIN, INT32_MAX );

	if ( no->peso == 0 ) {
		jogo->copia_pecas( jogPecas, compPecas );
		this->sorteiaJogada( posX, posY, jogada, jogPecas, compPecas, true );
	} else {
		*posX = no->posX;
		*posY = no->posY;
		*jogada = no->jogada;
	}

	this->limpaMiniMaxArvoreELs( nosLista );

	Peca* escolhida = jogo->getPeca( *posX, *posY );
	if ( escolhida->isIgual( jogo->getUltimaPecaComputador() ) ) {
		if ( ( jogo->getCompJogadaRepetidaCont()+1) % 4 == 0 ) {
			jogo->copia_pecas( jogPecas, compPecas );
			this->sorteiaJogada( posX, posY, jogada, jogPecas, compPecas, true );

			jogo->zeraCompJogadaRepetidaCont();
		} else {
			jogo->incCompJogadaRepetidaCont();
		}
	} else {
		jogo->zeraCompJogadaRepetidaCont();
	}

	escolhida->incJogadaCont();

	jogo->incCompJogadasCont();
}

void Algoritmo::limpaMiniMaxArvoreELs( MiniMaxNoLista* no ) {
	while( no != NULL ) {
		free( no->no );
		MiniMaxNoLista* aux = no;
		no = no->prox;
		delete aux;
	}
}


MiniMaxNo* Algoritmo::minimax( MiniMaxNoLista** nosLista, MiniMaxNo* no, bool isComp, int nivel, float alpha, float beta ) {
	jogo->copia_pecas( jogPecas, compPecas );
	if ( no != NULL )
		this->efetuaJogadas( no, jogPecas, compPecas );

	int status = jogo->isXequeMateOuEmpate( jogPecas, compPecas, !isComp );

	jogo->deleta_pecas( jogPecas );
	jogo->deleta_pecas( compPecas );

	if ( nivel <= 0 || status != Jogo::NAO_FIM )
		return no;

	MiniMaxNo* minimaxNo = new MiniMaxNo;
	minimaxNo->peso = ( isComp ? INT32_MIN : INT32_MAX );

	bool fim = false;
	for( int i = 0; !fim && i < Jogo::N_PECAS; i++ ) {
		jogo->copia_pecas( jogPecas, compPecas );

		if ( no != NULL )
			this->efetuaJogadas( no, jogPecas, compPecas );

		Peca* p = jogo->getPeca( isComp ? compPecas : jogPecas, i );
		if ( p == NULL )
			continue;

		p = p->nova();

		JogadaLista* lista = new JogadaLista();
		JogoPecas* jogoPecas = new JogoPecas( jogo );
		jogoPecas->setPecas( jogPecas, compPecas );

		jogo->calculaJogadasPossiveis( lista, jogoPecas, p->getPosX(), p->getPosY(), p->getTipo(), isComp, false );
		jogo->filtraJogadas( lista, jogPecas, compPecas, p->getPosX(), p->getPosY(), isComp );

		jogo->deleta_pecas( jogPecas );
		jogo->deleta_pecas( compPecas );
		jogo->deleta_pecas( jogoPecas );

		int tam = lista->getTam();
		for( int j = 0; !fim && j < tam; j++ ) {
			Jogada* jog = lista->getJogada( j );

			jogo->copia_pecas( jogPecas, compPecas );
			if ( no != NULL )
				this->efetuaJogadas( no, jogPecas, compPecas );

			bool isXeque = false;
			float peso = this->move( jogPecas, compPecas, p, jog, isComp, &isXeque );

			jogo->deleta_pecas( jogPecas );
			jogo->deleta_pecas( compPecas );

			MiniMaxNo* filho = new MiniMaxNo;
			filho->jogada = jog->nova();
			filho->posX = p->getPosX();
			filho->posY = p->getPosY();
			filho->peso = isComp ? peso : -peso;
			filho->ant = no;
			filho->prox = NULL;
			if ( no != NULL ) {
				no->prox = filho;
				filho->peso += no->peso;
			}

			MiniMaxNoLista* lno = new MiniMaxNoLista;
			lno->no = filho;
			lno->prox = *nosLista;
			*nosLista = lno;

			MiniMaxNo* no2 = this->minimax( nosLista, filho, !isComp, nivel-1, alpha, beta );
			if ( no2 == NULL ) {
				cout << "XXXXXXXXXXX" << endl;
				continue;
			}

			filho->peso = no2->peso;

			if ( isComp ) {
				if ( filho->peso > minimaxNo->peso )
					minimaxNo = filho;

				if ( minimaxNo->peso > alpha )
					alpha = minimaxNo->peso;
				if ( beta <= alpha )
					fim = true;
			} else {
				if ( filho->peso < minimaxNo->peso )
					minimaxNo = filho;

				if ( minimaxNo->peso < beta )
					beta = minimaxNo->peso;
				if ( beta <= alpha )
					fim = true;
			}
		}


		jogo->deleta_jogadas( lista );
	}

	return minimaxNo;
}

float Algoritmo::move(
		Peca* jps[ Jogo::N_PECAS ], Peca* cps[ Jogo::N_PECAS ],
		Peca* p, Jogada* jog, bool isComp, bool* isXeque ) {

	Peca* pOrig = jogo->getPeca( p->getPosX(), p->getPosY() );

	float jogCapPecaPeso = 0;
	float xequePeso = 0;

	jogo->move( jps, cps, p->getPosX(), p->getPosY(), jog->getPosX(), jog->getPosY() );

	Peca* capturada = jog->getCaptura();
	if ( capturada != NULL )
		if ( capturada->getTipo() != Jogo::REI )
			jogCapPecaPeso = this->calculaPeso( capturada );

	*isXeque = jogo->isReiEmXeque( jps, cps, isComp );
	if ( *isXeque )
		if ( pOrig->getJogadaCont() % 3 != 0 || pOrig->getJogadaCont() == 0 )
			xequePeso = 0.1 - ( pOrig->getJogadaCont() * 0.01 );

	return jogCapPecaPeso + xequePeso;
}

void Algoritmo::efetuaJogadas( MiniMaxNo* no, Peca* jps[Jogo::N_PECAS], Peca* cps[Jogo::N_PECAS] ) {
	MiniMaxNo* perc = no;
	while( perc->ant != NULL )
		perc = perc->ant;

	while( perc != NULL ) {
		int posX = no->posX;
		int posY = no->posY;
		int novaPosX = no->jogada->getPosX();
		int novaPosY = no->jogada->getPosY();
		jogo->move( jps, cps, posX, posY, novaPosX, novaPosY );

		perc = perc->prox;
	}
}

float Algoritmo::calculaPeso( Peca* peca ) {
	float peso = 0;
	switch( peca->getTipo() ) {
		case Jogo::REI:     peso = 0.5;  break;
		case Jogo::RAINHA:  peso = 9;   break;
		case Jogo::TORRE:   peso = 5;   break;
		case Jogo::BISPO:   peso = 3;   break;
		case Jogo::CAVALO:  peso = 3;   break;
		case Jogo::PEAO:    peso = 1;  break;
	}
	return peso;
}

void Algoritmo::sorteiaJogada(
		int* posX, int* posY, Jogada** jogada,
		Peca* jps[ Jogo::N_PECAS ],
		Peca* cps[ Jogo::N_PECAS ],
		bool isComp ) {

	Peca* pecasParaSortear[ Jogo::N_PECAS ];

	int minCont = INT32_MAX;
	for( int i = 0; i < Jogo::N_PECAS; i++ ) {
		Peca* p = jogo->getPeca( isComp ? cps : jps, i );
		if ( p == NULL )
			continue;

		JogadaLista* lista = new JogadaLista();

		JogoPecas* pecas = new JogoPecas( jogo );
		pecas->setPecas( jps, cps );

		jogo->calculaJogadasPossiveis( lista, pecas, p->getPosX(), p->getPosY(), p->getTipo(), isComp, false );
		jogo->filtraJogadas( lista, jps, cps, p->getPosX(), p->getPosY(), isComp );

		if ( lista->getTam() > 0 && p->getJogadaCont() < minCont )
			minCont = p->getJogadaCont();

		jogo->deleta_pecas( pecas );
	}

	int pecasParaSortearCont = 0;
	for( int i = 0; i < Jogo::N_PECAS; i++ ) {
		Peca* p = jogo->getPeca( isComp ? cps : jps, i );
		if ( p == NULL )
			continue;
		if ( p->isRemovida() )
			continue;

		bool isCap = jogo->isCaptura( (isComp ? jps : cps), jps, cps, p->getPosX(), p->getPosY(), !isComp );
		if ( isCap )
			continue;

		JogadaLista* lista = new JogadaLista();

		JogoPecas* pecas = new JogoPecas( jogo );
		pecas->setPecas( jps, cps );

		jogo->calculaJogadasPossiveis( lista, pecas, p->getPosX(), p->getPosY(), p->getTipo(), isComp, false );
		jogo->filtraJogadas( lista, jps, cps, p->getPosX(), p->getPosY(), isComp );

		if ( lista->getTam() > 0 && p->getJogadaCont() == minCont ) {
			Jogada* jog = this->sorteiaPecaJogada( p, jps, cps, isComp );
			if ( jog != NULL )
				pecasParaSortear[ pecasParaSortearCont++ ] = p;
		}

		jogo->deleta_pecas( pecas );
	}

	if ( pecasParaSortearCont > 0 ) {
		srand( time( NULL ) );
		int indice = (int)round( rand() % pecasParaSortearCont );

		Peca* p = pecasParaSortear[ indice ];
		*jogada = this->sorteiaPecaJogada( p, jps, cps, isComp );
		*posX = p->getPosX();
		*posY = p->getPosY();
	} else {
		Peca* p = this->sorteiaPeca( ( isComp ? cps : jps ), jps, cps, isComp );
		*jogada = this->sorteiaPecaJogada( p, jps, cps, isComp );

		*posX = p->getPosX();
		*posY = p->getPosY();
	}

}

Peca* Algoritmo::sorteiaPeca(
		Peca* vetor[ Jogo::N_PECAS ],
		Peca* jps[ Jogo::N_PECAS],
		Peca* cps[ Jogo::N_PECAS ],
		bool isComp ) {

	Peca* vet[ Jogo::N_PECAS ];
	int vet_tam = 0;
	for( int i = 0; i < Jogo::N_PECAS; i++ )  {
		if ( vetor[i]->isRemovida() )
			continue;

		Peca* p = vetor[i];

		JogadaLista* lista = new JogadaLista();

		JogoPecas* pecas = new JogoPecas( jogo );
		pecas->setPecas( jps, cps );

		jogo->calculaJogadasPossiveis( lista, pecas, p->getPosX(), p->getPosY(), p->getTipo(), isComp, false );
		jogo->filtraJogadas( lista, jps, cps, p->getPosX(), p->getPosY(), isComp );

		if ( lista->getTam() > 0 ) {
			Jogada* jog = this->sorteiaPecaJogada( p, jps, cps, isComp );
			if ( jog != NULL )
				vet[ vet_tam++ ] = p;
		}

		pecas->deleta_pecas();
	}

	srand( time( NULL ) );
	return vet[ (int)round( rand() % vet_tam ) ]->nova();
}

Jogada* Algoritmo::sorteiaPecaJogada( Peca* peca, Peca* jps[ Jogo::N_PECAS ], Peca* cps[ Jogo::N_PECAS ], bool isComp ) {
	JogadaLista* lista = new JogadaLista();

	JogoPecas* pecas = new JogoPecas( jogo );
	pecas->setPecas( jps, cps );

	jogo->calculaJogadasPossiveis( lista, pecas, peca->getPosX(), peca->getPosY(), peca->getTipo(), isComp, false );
	jogo->filtraJogadas( lista, jps, cps, peca->getPosX(), peca->getPosY(), isComp );

	JogadaLista* lista2 = new JogadaLista();

	for( int i = 0; i < lista->getTam(); i++ ) {
		Jogada* jog = lista->getJogada( i );
		bool isCap = jogo->isCaptura( ( isComp ? jps : cps ), jogPecas, compPecas, jog->getPosX(), jog->getPosY(), !isComp );
		if ( !isCap )
			lista2->addJogada( jog );
	}

	srand( time( NULL ) );

	Jogada* jog = NULL;
	if ( lista2->getTam() > 0 ) {
		jog = lista2->getJogada( (int)round( rand() % lista2->getTam() ) )->nova();
	} else if ( lista->getTam() > 0 ){
		jog = lista->getJogada( (int)round( rand() % lista->getTam() ) )->nova();
	}

	jogo->deleta_jogadas( lista );
	jogo->deleta_jogadas( lista2 );

	return jog;
}
