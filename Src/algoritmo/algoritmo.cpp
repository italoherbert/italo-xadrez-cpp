
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
	MiniMaxNo* raiz = new MiniMaxNo;
	raiz->peso = 0;
	raiz->pai = NULL;
	raiz->filhos = NULL;

	MiniMaxNo* no = this->minimax( raiz, true, jogo->getNivel(), INT32_MIN, INT32_MAX );

	if ( no->peso == 0 ) {
		jogo->copia_pecas( jogPecas, compPecas );

		bool tentativaDominioCentro = this->tentaDominioDoCentro( jogPecas, compPecas, posX, posY, jogada );
		if ( !tentativaDominioCentro )
			this->sorteiaJogada( posX, posY, jogada, jogPecas, compPecas, true );

		jogo->deleta_pecas( jogPecas );
		jogo->deleta_pecas( compPecas );
	} else {
		while( no->pai->pai != NULL  )
			no = no->pai;
		*posX = no->posX;
		*posY = no->posY;
		*jogada = no->jogada;
	}

	this->limpaMiniMaxArvore( raiz );

	Peca* escolhida = jogo->getPeca( *posX, *posY );
	if ( escolhida->isIgual( jogo->getUltimaPecaComputador() ) ) {
		if ( ( jogo->getCompJogadaRepetidaCont()+1 ) % 3 == 0 ) {
			bool isCap = jogo->isCaptura(
					jogPecas, jogPecas, compPecas,
					escolhida->getPosX(), escolhida->getPosY(), false );

			if ( !isCap ) {
				jogo->copia_pecas( jogPecas, compPecas );
				this->sorteiaJogada( posX, posY, jogada, jogPecas, compPecas, true );

				jogo->deleta_pecas( jogPecas );
				jogo->deleta_pecas( compPecas );

				jogo->zeraCompJogadaRepetidaCont();
			}
		} else {
			jogo->incCompJogadaRepetidaCont();
		}
	} else {
		jogo->zeraCompJogadaRepetidaCont();
	}

	escolhida->incJogadaCont();

	jogo->incCompJogadasCont();
}

MiniMaxNo* Algoritmo::minimax( MiniMaxNo* no, bool isComp, int nivel, float alpha, float beta ) {
	jogo->copia_pecas( jogPecas, compPecas );
	this->efetuaJogadas( no, jogPecas, compPecas );

	int status = jogo->isXequeMateOuEmpate( jogPecas, compPecas, isComp );

	jogo->deleta_pecas( jogPecas );
	jogo->deleta_pecas( compPecas );

	if ( nivel <= 0 || status != Jogo::NAO_FIM ) {
		if ( isComp ) {
			if ( status == Jogo::COMPUTADOR_VENCEU )
				no->peso = nivel * 1000;
		} else {
			if ( status == Jogo::JOGADOR_VENCEU )
				no->peso = -nivel * 1000;
		}
		return no;
	}

	MiniMaxNo* minimaxNo = new MiniMaxNo;
	minimaxNo->peso = isComp ? INT32_MIN : INT32_MAX;
	minimaxNo->pai = no;

	bool fim = false;
	for( int i = 0; !fim && i < Jogo::N_PECAS; i++ ) {
		jogo->copia_pecas( jogPecas, compPecas );
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
			Jogada* jog = lista->getJogada( j )->nova();

			jogo->copia_pecas( jogPecas, compPecas );
			this->efetuaJogadas( no, jogPecas, compPecas );

			float peso = this->move( jogPecas, compPecas, p, jog, isComp );

			jogo->deleta_pecas( jogPecas );
			jogo->deleta_pecas( compPecas );

			MiniMaxNo* filho = new MiniMaxNo;
			filho->jogada = jog;
			filho->posX = p->getPosX();
			filho->posY = p->getPosY();
			filho->peso = no->peso + ( isComp ? peso : -peso );
			filho->pai = no;
			filho->filhos = NULL;

			MiniMaxNoLista* novo = new MiniMaxNoLista;
			novo->no = filho;
			novo->prox = NULL;
			if ( no->filhos == NULL ) {
				no->filhos = novo;
			} else {
				novo->prox = no->filhos;
				no->filhos = novo;
			}

			MiniMaxNo* no2 = this->minimax( filho, !isComp, nivel-1, alpha, beta );

			if ( isComp ){
				if ( no2->peso > minimaxNo->peso )
					minimaxNo = no2;

				if ( minimaxNo->peso > alpha )
					alpha = minimaxNo->peso;
				if ( beta <= alpha )
					fim = true;
			} else {
				if ( no2->peso < minimaxNo->peso )
					minimaxNo = no2;

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

float Algoritmo::move( Peca** jps, Peca** cps, Peca* p, Jogada* jog, bool isComp ) {
	float capturadaPeso = 0;
	float xequePeso = 0;

	bool antesMovePodeSerCapturada = jogo->isCaptura(
				isComp ? jps : cps,
				jps, cps, p->getPosX(), p->getPosY(), !isComp );

	jogo->move( jps, cps, p->getPosX(), p->getPosY(), jog->getPosX(), jog->getPosY() );
	if ( jog->getTipo() == Jogada::EN_PASSANT ) {
		Peca* capP = jogo->getPeca( jogPecas, compPecas, jog->getCaptura()->getPosX(), jog->getCaptura()->getPosY() );
		capP->setRemovida( true );
	}

	bool aposMovePodeSerCapturada = jogo->isCaptura(
				isComp ? jps : cps,
				jps, cps, jog->getPosX(), jog->getPosY(), !isComp );

	Peca* capturada = jog->getCaptura();
	if ( capturada != NULL )
		if ( capturada->getTipo() != Jogo::REI )
			capturadaPeso = this->calculaPeso( capturada );

	bool isXeque = jogo->isReiEmXeque( jps, cps, isComp );
	if ( isXeque )
		xequePeso = 1.0;

	float capPecaPeso = 0;
	if ( antesMovePodeSerCapturada ) {
		if ( !aposMovePodeSerCapturada )
			capPecaPeso = this->calculaPeso( p );
	} else {
		if ( aposMovePodeSerCapturada )
			capPecaPeso = -this->calculaPeso( p );
	}

	return capturadaPeso + capPecaPeso + xequePeso;
}

void Algoritmo::limpaMiniMaxArvore( MiniMaxNo* no ) {
	if ( no == NULL )
		return;

	MiniMaxNoLista* perc = no->filhos;
	while( perc != NULL ) {
		MiniMaxNoLista* aux = perc;
		perc = perc->prox;
		this->limpaMiniMaxArvore( aux->no );
		delete aux;
	}

	delete no;
}

float Algoritmo::calculaGanhoOuPerda( Peca** jps, Peca** cps, bool isComp ) {
	float max = 0;
	float min = 0;

	for( int i = 0; i < Jogo::N_PECAS; i++ ) {
		Peca* p = jogo->getPeca( isComp ? cps : jps, i );
		if ( p == NULL )
			continue;

		max += this->calculaPeso( p );
	}

	for( int i = 0; i < Jogo::N_PECAS; i++ ) {
		Peca* p = jogo->getPeca( isComp ? jps : cps, i );
		if ( p == NULL )
			continue;

		min += this->calculaPeso( p );
	}

	return max - min;
}

void Algoritmo::efetuaJogadas( MiniMaxNo* no, Peca* jps[Jogo::N_PECAS], Peca* cps[Jogo::N_PECAS] ) {
	MiniMaxNo* perc = no;
	MiniMaxNoLista* raiz = NULL;

	while( perc != NULL ) {
		MiniMaxNoLista* novo = new MiniMaxNoLista;
		novo->no = perc;
		novo->prox = NULL;

		if ( raiz == NULL ) {
			raiz = novo;
		} else {
			novo->prox = raiz;
			raiz = novo;
		}

		perc = perc->pai;
	}

	while( raiz != NULL ) {
		if ( raiz->no->pai != NULL ) {
			int posX = raiz->no->posX;
			int posY = raiz->no->posY;
			int novaPosX = raiz->no->jogada->getPosX();
			int novaPosY = raiz->no->jogada->getPosY();
			jogo->move( jps, cps, posX, posY, novaPosX, novaPosY );
		}

		MiniMaxNoLista* aux = raiz;
		raiz = raiz->prox;
		delete aux;
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

bool Algoritmo::tentaDominioDoCentro( Peca** jps, Peca** cps, int* posX, int* posY, Jogada** jogada ) {
	bool jogou = false;
	for( int i = 0; !jogou && i < Jogo::N_JOGADAS_DOMINIO_CENTRO; i++ ) {
		int* jog = jogo->getCompJogadaDominioCentro( i );
		int px1 = jog[ 0 ];
		int py1 = jog[ 1 ];
		int px2 = jog[ 2 ];
		int py2 = jog[ 3 ];
		Peca* p = jogo->getPeca( cps, px1, py1 );
		if ( p != NULL ) {
			if ( p->getMoveuContador() == 0 ) {
				Peca* p2 = jogo->getPeca( jps, cps, px2, py2 );
				if ( p2 != NULL )
					if ( p2->getTipo() == Jogo::REI )
						p2 = NULL;

				if ( p2 == NULL ){
					*posX = px1;
					*posY = py1;
					*jogada = new Jogada( px2, py2, p2, Jogada::NORMAL );
					jogou = true;
				}
			}
		}
	}
	return jogou;
}
