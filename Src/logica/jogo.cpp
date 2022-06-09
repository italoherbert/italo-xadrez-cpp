#include "jogo.h"

#include <cstdlib>
#include <cmath>

#include "jogada_roque.h"
#include "jogo_pecas.h"

Jogo::Jogo( TelaDriver* drv ) {	
	tela = new Tela( drv );				
	jogadas = new JogadaLista();					
}

void Jogo::reinicia() {
	jogadorPecas[0] = new Peca( false, TORRE, 0, 7 );
	jogadorPecas[1] = new Peca( false, CAVALO, 1, 7 );
	jogadorPecas[2] = new Peca( false, BISPO, 2, 7 );
	jogadorPecas[3] = new Peca( false, RAINHA, 3, 7 );
	jogadorPecas[4] = new Peca( false, REI, 4, 7 );
	jogadorPecas[5] = new Peca( false, BISPO, 5, 7 );
	jogadorPecas[6] = new Peca( false, CAVALO, 6, 7 );
	jogadorPecas[7] = new Peca( false, TORRE, 7, 7 );
	jogadorPecas[8] = new Peca( false, PEAO, 0, 6 );
	jogadorPecas[9] = new Peca( false, PEAO, 1, 6 );
	jogadorPecas[10] = new Peca( false, PEAO, 2, 6 );
	jogadorPecas[11] = new Peca( false, PEAO, 3, 6 );
	jogadorPecas[12] = new Peca( false, PEAO, 4, 6 );
	jogadorPecas[13] = new Peca( false, PEAO, 5, 6 );
	jogadorPecas[14] = new Peca( false, PEAO, 6, 6 );
	jogadorPecas[15] = new Peca( false, PEAO, 7, 6 );		
	
	computadorPecas[0] = new Peca( true, TORRE, 0, 0 );
	computadorPecas[1] = new Peca( true, CAVALO, 1, 0 );
	computadorPecas[2] = new Peca( true, BISPO, 2, 0 );
	computadorPecas[3] = new Peca( true, RAINHA, 3, 0 );
	computadorPecas[4] = new Peca( true, REI, 4, 0 );
	computadorPecas[5] = new Peca( true, BISPO, 5, 0 );
	computadorPecas[6] = new Peca( true, CAVALO, 6, 0 );
	computadorPecas[7] = new Peca( true, TORRE, 7, 0 );
	computadorPecas[8] = new Peca( true, PEAO, 0, 1 );
	computadorPecas[9] = new Peca( true, PEAO, 1, 1 );
	computadorPecas[10] = new Peca( true, PEAO, 2, 1 );
	computadorPecas[11] = new Peca( true, PEAO, 3, 1 );
	computadorPecas[12] = new Peca( true, PEAO, 4, 1 );
	computadorPecas[13] = new Peca( true, PEAO, 5, 1 );
	computadorPecas[14] = new Peca( true, PEAO, 6, 1 );
	computadorPecas[15] = new Peca( true, PEAO, 7, 1 );

	for( int i = 0; i < N_PECAS; i++ ) {
		jogadorPecas[i]->setRemovida( false );
		computadorPecas[i]->setRemovida( false );						
		//if ( i > 7 )
		//	computadorPecas[i]->setRemovida( true );
	}			
	//jogadorPecas[4]->setRemovida( false );
		
	jogadas->limpaJogadas();

	ultPeca = NULL;	
	movimento = NULL;
	
	vezComputador = false;	
	
	compRoque = false;
	jogRoque = false;
	audioLigado = true;
			
	quantCompJogadas = 0;	
	
	nivel = NIVEL_DIFICIL;
	fim = NAO_FIM;	
}


bool Jogo::move( int posX, int posY, int novaPosX, int novaPosY ) {
	return this->move( jogadorPecas, computadorPecas, posX, posY, novaPosX, novaPosY );
}

bool Jogo::move( Peca* pecas1[N_PECAS], Peca* pecas2[N_PECAS], int posX, int posY, int novaPosX, int novaPosY ) {
	Peca* novaPos = this->getPeca( pecas1, pecas2, novaPosX, novaPosY );	
	
	if ( novaPos != NULL )
		novaPos->setRemovida( true );	
	
	Peca* peca = this->getPeca( pecas1, pecas2, posX, posY );
								
	if ( peca != NULL ) {		
		peca->setPosX( novaPosX );
		peca->setPosY( novaPosY );
																		
		return true;
	}
	
	return false;
}

int Jogo::isXequeMate( JogadaUtil* util, bool isComp ) {
	return this->isXequeMate( util, jogadorPecas, computadorPecas, isComp );
}

int Jogo::isXequeMate( JogadaUtil* util, Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], bool isComp ) {					
	bool fim = true;		
	
	for( int i = 0; fim && i < N_PECAS; i++ ) {
		Peca* p = ( isComp ? compPecas[i] : jogPecas[i] );
		if ( p->isRemovida() )
			continue;
						
		JogadaLista* lista = new JogadaLista();	
		JogoPecas* pecas = new JogoPecas( this );
		pecas->setPecas( jogPecas, compPecas );
		
		util->calculaJogadasPossiveis( lista, pecas, p->getPosX(), p->getPosY(), p->getTipo(), isComp, true );
		util->filtraJogadas( lista, p->getPosX(), p->getPosY(), isComp );		
		
		if ( lista->getTam() != 0 )
			fim = false;
			
		this->deleta_jogadas( lista );
		delete pecas;			
	}	
	
	if ( fim ) {				
		bool isXeque;
		if( isComp )
			isXeque = this->isReiEmXeque( util, jogPecas, jogPecas, compPecas, false );
		else isXeque = this->isReiEmXeque( util, compPecas, jogPecas, compPecas, true );
		
		if ( isXeque ) {		
			if ( isComp )
				return JOGADOR_VENCEU;			
			else return COMPUTADOR_VENCEU;
		} else {
			if ( isComp == vezComputador )
				return EMPATE;
		}		
	}	
	return NAO_FIM;
}

bool Jogo::isJogadorReiEmXeque( JogadaUtil* util ) {
	return this->isReiEmXeque( util, computadorPecas, jogadorPecas, computadorPecas, true );
}

bool Jogo::isCompReiEmXeque( JogadaUtil* util ) {
	return this->isReiEmXeque( util, jogadorPecas, jogadorPecas, computadorPecas, false );
}

bool Jogo::isCaptura( JogadaUtil* util, Peca* outras[N_PECAS], 
			Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY, bool isComp ) {	
			
	Peca* p = this->pecaCaptura( util, outras, jogPecas, compPecas, posX, posY, isComp, true );
	return ( p != NULL );					
}

Peca* Jogo::pecaCaptura( JogadaUtil* util, Peca* outras[N_PECAS], 
			Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY, bool isComp ) {	
	return this->pecaCaptura( util, outras, jogPecas, compPecas, posX, posY, isComp, true );
}

bool Jogo::isCaptura( JogadaUtil* util, Peca* outras[N_PECAS], 
			Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY, bool isComp, bool incluirRei ) {	
			
	Peca* p = this->pecaCaptura( util, outras, jogPecas, compPecas, posX, posY, isComp, incluirRei );
	return ( p != NULL );					
}

Peca* Jogo::pecaCaptura( JogadaUtil* util, Peca* outras[N_PECAS], 
			Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY, bool isComp, bool incluirRei ) {	
	for( int i = 0; i < N_PECAS; i++ ) {
		Peca* peca = outras[ i ];				
		if ( peca->isRemovida() )
			continue;
			
		if ( !incluirRei )	
			if ( peca->getTipo() == Jogo::REI )
				continue;
			
		if ( peca->getPosX() == posX && peca->getPosY() == posY )																										
			continue;
			
		if ( peca->getTipo() == Jogo::PEAO ) {
			int y = peca->getPosY() + ( isComp ? 1 : -1 );
			int x = peca->getPosX() - 1;
						
			if ( this->isPosicaoValida( x, y ) )			
				if ( x == posX && y == posY )
					return peca;
					
			x = peca->getPosX() + 1;
			if ( this->isPosicaoValida( x, y ) )
				if ( x == posX && y == posY )
					return peca;					
		} else {								
			JogadaLista* lista = new JogadaLista();	
			
			JogoPecas* jps = new JogoPecas( this );
			jps->setPecas( jogPecas, compPecas );						
																	
			util->calculaJogadasPossiveis( lista, jps, peca->getPosX(), peca->getPosY(), peca->getTipo(), isComp, true );
			
			int tam = lista->getTam();
			for( int j = 0; j < tam; j++ ) {			
				Jogada* jogada = lista->getJogada( j );			
				
				if ( jogada->getPosX() == posX && jogada->getPosY() == posY ) {									
					this->deleta_jogadas( lista );
					delete jps;					
						
					return peca;
				}
			}			
			
			this->deleta_jogadas( lista );
			delete jps;
		}	
	
	}
		
	return NULL;				
}

bool Jogo::isReiEmXeque( JogadaUtil* util, Peca* outras[N_PECAS], 
			Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], bool isComp ) {
	for( int i = 0; i < N_PECAS; i++ ) {
		Peca* peca = outras[ i ];				
		if ( peca->isRemovida() )
			continue;																										
		
		JogadaLista* lista = new JogadaLista();	
		
		JogoPecas* jps = new JogoPecas( this );
		jps->setPecas( jogPecas, compPecas );						
																
		util->calculaJogadasPossiveis( lista, jps, peca->getPosX(), peca->getPosY(), peca->getTipo(), isComp, true );
		
		int tam = lista->getTam();				
		for( int j = 0; j < tam; j++ ) {			
			Jogada* jogada = lista->getJogada( j );				 
			if( jogada->getCaptura() != NULL )		
				if ( jogada->getCaptura()->getTipo() == REI )
					return true;					
		}		
		
		this->deleta_jogadas( lista );			
		delete jps;
	}	
		
	return false;
}

bool Jogo::addJogada( JogadaLista* lista, Pecas* pecas, int posX, int posY, bool isComp ) {					
	Peca* peca = pecas->getPeca( posX, posY );	
	if ( peca == NULL ) {
		lista->addJogada( posX, posY, NULL );
	} else {
		if ( isComp ) {
			if ( !peca->isDeComp() )				
				lista->addJogada( posX, posY, peca );				
		} else {
			if ( peca->isDeComp() )
				lista->addJogada( posX, posY, peca );
		}				
		return true;	
	}	
	return false;
}

Peca* Jogo::getPeca( Peca* jogPecas[ N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY ) {
	Peca* p = this->getPeca( jogPecas, posX, posY );
	if ( p == NULL )
		p = this->getPeca( compPecas, posX, posY );		
	return p;
}
		
Peca* Jogo::getPeca( Peca* pecas[ N_PECAS ], int posX, int posY ) {
	for( int i = 0; i < N_PECAS; i++ ) {
		Peca* p = pecas[ i ];
		if ( p->isRemovida() )
			continue;
			
		if ( p->getPosX() == posX && p->getPosY() == posY )
			return p;
	}
	return NULL;
}
		
Peca* Jogo::getPeca( Peca* vetor[ N_PECAS ], int indice ) {
	Peca* p = vetor[ indice ];
	if ( p->isRemovida() )
		return NULL;
	return p;
}

Peca** Jogo::getJogadorPecas() {
	return jogadorPecas;
}

Peca** Jogo::getComputadorPecas() {
	return computadorPecas;
}

int Jogo::getQuantCompJogadas() {
	return quantCompJogadas;
}

void Jogo::incQuantCompJogadas() {
	quantCompJogadas++;
}

int Jogo::isPosicaoValida( int posX, int posY ) {
	return ( posX >= 0 && posX < 8 && posY >= 0 && posY < 8 );
}
		
Peca* Jogo::getJogadorPeca( int posX, int posY ) {
	for( int i = 0; i < N_PECAS; i++ )	
		if ( !jogadorPecas[ i ]->isRemovida() )
			if ( jogadorPecas[ i ]->getPosX() == posX && jogadorPecas[ i ]->getPosY() == posY )
				return jogadorPecas[ i ];	
	return NULL;
}

Peca* Jogo::getComputadorPeca( int posX, int posY ) {
	for( int i = 0; i < N_PECAS; i++ )
		if ( !computadorPecas[ i ]->isRemovida() )
			if ( computadorPecas[ i ]->getPosX() == posX && computadorPecas[ i ]->getPosY() == posY )
				return computadorPecas[ i ];
			
	return NULL;
}

Peca* Jogo::getPeca( int posX, int posY ) {
	Peca* peca = this->getJogadorPeca( posX, posY );
	if ( peca == NULL )
		return this->getComputadorPeca( posX, posY );
	return peca;
}

Jogada* Jogo::getJogada( int posX, int posY ) {
	JogadaLista* lista = this->getJogadasPossiveis();
	int tam = lista->getTam();
	for( int i = 0; i < tam; i++ ) {	
		Jogada* jogada = lista->getJogada( i );
		if ( jogada->getPosX() == posX && jogada->getPosY() == posY )
			return jogada;
	}
	return NULL;
}

void Jogo::registraRoque( bool isComp ) {
	if ( isComp )
		compRoque = true;
	else jogRoque = true;
}

Peca* Jogo::getPecaPeaoMeioEsq( Peca* vetor[N_PECAS] ) {
	Peca* p = vetor[ PECA_PEAO_MEIO_ESQ_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaPeaoMeioDir( Peca* vetor[N_PECAS] ) {
	Peca* p = vetor[ PECA_PEAO_MEIO_DIR_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaCavaloEsq( Peca* vetor[N_PECAS] ) {
	Peca* p = vetor[ PECA_CAVALO_ESQ_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaCavaloDir( Peca* vetor[N_PECAS] ) {	
	Peca* p = vetor[ PECA_CAVALO_DIR_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaBispoEsq( Peca* vetor[N_PECAS] ) {
	Peca* p = vetor[ PECA_BISPO_ESQ_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaBispoDir( Peca* vetor[N_PECAS] ) {	
	Peca* p = vetor[ PECA_BISPO_DIR_INDICE ];
	return ( p->isRemovida() ? NULL : p );
}

Peca* Jogo::getPecaRei( bool isComp ) {
	if( isComp )
		return computadorPecas[ PECA_REI_INDICE ];
	return jogadorPecas[ PECA_REI_INDICE ];
}

Peca* Jogo::getPecaRei( Peca* vetor[N_PECAS] )  {
	return vetor[ PECA_REI_INDICE ];
}

Peca* Jogo::getJogadorPeca( int indice ) {
	return jogadorPecas[ indice ];
}

Peca* Jogo::getComputadorPeca( int indice ) {
	return computadorPecas[ indice ];
}

JogadaLista* Jogo::getJogadasPossiveis() {
	return jogadas;
}

bool Jogo::isCompRoqueFeito() {
	return compRoque;
}

bool Jogo::isJogRoqueFeito() {
	return jogRoque;
}

Tela* Jogo::getTela() {
	return tela;
}

bool Jogo::isVezComputador() {
	return vezComputador;
}	
	
void Jogo::setVezComputador( bool b ) {
	this->vezComputador = b;
}
		
Peca* Jogo::getJogadorJogadaPeca() {
	return jogadaPeca;
}

void Jogo::setJogadorJogadaPeca( Peca* peca ) {
	this->jogadaPeca = peca;
}

void Jogo::copia_pecas( Peca* novoJPs[N_PECAS], Peca* novoCPs[N_PECAS] ) {
	this->copia_pecas( novoJPs, novoCPs, jogadorPecas, computadorPecas );
}

void Jogo::copia_pecas( Pecas* pecas, Peca* novoJPs[N_PECAS], Peca* novoCPs[N_PECAS] ) {
	for( int i = 0; i < N_PECAS; i++ ) {
		novoJPs[ i ] = pecas->getJogadorPeca( i )->nova();
		novoCPs[ i ] = pecas->getComputadorPeca( i )->nova();
	}
}

void Jogo::copia_pecas( Peca* novoJPs[N_PECAS], Peca* novoCPs[N_PECAS], Peca* jps[N_PECAS], Peca* cps[N_PECAS] ) {
	for( int i = 0; i < N_PECAS; i++ ) {
		novoJPs[ i ] = jps[ i ]->nova();
		novoCPs[ i ] = cps[ i ]->nova();
	}
}

void Jogo::deleta_pecas() {
	this->deleta_pecas( jogadorPecas );
	this->deleta_pecas( computadorPecas );
}

void Jogo::deleta_pecas( Pecas* pecas ) {
	if ( pecas != NULL ) {
	
		pecas->deleta_pecas();
	
		delete pecas;
		pecas = NULL;
	}
}

void Jogo::deleta_pecas( Peca* vetor[N_PECAS] ) {
	if ( vetor != NULL ) {	
		for( int i = 0; i < N_PECAS; i++ )
			if ( vetor[i] != NULL )
				delete vetor[i];			
	}
}

void Jogo::deleta_jogadas( JogadaLista* lista ) {
	if ( lista != NULL ) {	
		int tam = lista->getTam();
		for( int i = 0; i < tam; i++ )	
			if ( lista->getJogada( i ) != NULL )			
				delete lista->getJogada( i );						
				
		delete lista;
		lista = NULL;
	}	
}

Peca* Jogo::getUltimaPecaComputador() {
	return ultPecaComp;
}

Peca* Jogo::getUltimaPecaJogador() {
	return ultPecaJog;
}

Peca* Jogo::getUltimaPeca() {
	return ultPeca;
}

void Jogo::setUltimaPeca( Peca* peca ) {
	if ( peca->isDeComp() )
		ultPecaComp = peca;
	else ultPecaJog = peca;
	
	this->ultPeca = peca;
}

int Jogo::getFIM() {
	return fim;
}

void Jogo::setFim( int fim ) {
	this->fim = fim;
}

bool Jogo::isAudioLigado() {
	return audioLigado;
}

void Jogo::setAudioLigado( bool ligado ) {
	this->audioLigado = ligado;
}

Movimento* Jogo::getMovimento() {
	return movimento;
}

void Jogo::setMovimento( Movimento* movimento ) {
	this->movimento = movimento;
}			

int Jogo::getNivel() {
	return nivel;
}

void Jogo::setNivel( int nivel ) {
	this->nivel = nivel;
}

/*
std::string Jogo::get_peca_str( int tipo ) {
	switch( tipo ) {
		case Jogo::REI: return "REI";
		case Jogo::RAINHA: return "RAINHA";
		case Jogo::TORRE: return "TORRE";
		case Jogo::BISPO: return "BISPO";
		case Jogo::CAVALO: return "CAVALO";
		case Jogo::PEAO: return "PEAO";
	}
	return "DESCONHECIDO";
}
*/
