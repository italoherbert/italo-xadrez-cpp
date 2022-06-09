
#include "algoritmo.h"

#include <cstdlib>
#include <cmath>
#include <ctime>

#include <iostream>

#include "../logica/jogo_pecas.h"
using namespace std;

Algoritmo::Algoritmo( Jogo* jogo, JogadaGerenciador* jGer ) {
	this->jogo = jogo;
	this->jGer = jGer;
	
	srand( time( NULL ) );
	
	xequeCont = 0;
	naoXequeCont = 0;
}

float Algoritmo::calculaPeso( Peca* peca ) {
	float peso = 0;
	switch( peca->getTipo() ) {
		case Jogo::REI: peso = 20; break;
		case Jogo::RAINHA: peso = 9; break;
		case Jogo::TORRE: peso = 5; break;
		case Jogo::BISPO:  peso = 3; break;
		case Jogo::CAVALO: peso = 3; break;
		case Jogo::PEAO:
			if ( peca->getPosX() == 3 || peca->getPosX() == 4 )
				peso = 1.2;
			else peso = 1.0;
			break;
	}
	return peso;
}

void Algoritmo::calculaMelhorJogada( int* posX, int* posY, Jogada** jogada ) {
	if ( jogo->getFIM() != Jogo::NAO_FIM )
		return;				
	
	Peca* jogPecas[ Jogo::N_PECAS ];
	Peca* compPecas[ Jogo::N_PECAS ];
	
	jogo->copia_pecas( jogPecas, compPecas );			
	
	Jogada* jogadaXeque = NULL;			
	
	*jogada = NULL;
		
	float peso = INT32_MIN;
	for( int i = 0; i < Jogo::N_PECAS; i++ ) {
		Peca* p = jogo->getPeca( compPecas, i );
		if ( p == NULL )	
			continue;
		
		JogadaLista* lista = new JogadaLista();
		JogoPecas* pecas = new JogoPecas( jogo );
		pecas->setPecas( jogPecas, compPecas );			
			
		jGer->calculaJogadasPossiveis( lista, pecas, p->getPosX(), p->getPosY(), p->getTipo(), true, false );
		jGer->filtraJogadas( lista, p->getPosX(), p->getPosY(), true );
		
		bool capPeca = jogo->isCaptura( jGer, jogPecas, jogPecas, compPecas, p->getPosX(), p->getPosY(), false );											
		float pecaPeso = this->calculaPeso( p );																					
										
		int tam = lista->getTam();
		for( int j = 0; j < tam; j++ ) {
			Jogada* jog = lista->getJogada( j );
												
			Peca* jps[ Jogo::N_PECAS ];
			Peca* cps[ Jogo::N_PECAS ];
		
			jogo->copia_pecas( jps, cps, jogPecas, compPecas );				
			jogo->move( jps, cps, p->getPosX(), p->getPosY(), jog->getPosX(), jog->getPosY() );										
			
			bool capJogada = jogo->isCaptura( jGer, jps, jps, cps, jog->getPosX(), jog->getPosY(), false );				
			
			int fim = jogo->isXequeMate( jGer, jps, cps, true );
			if ( fim == Jogo::JOGADOR_VENCEU )
				continue;					
										
			fim = jogo->isXequeMate( jGer, jps, cps, false );
			if ( fim == Jogo::COMPUTADOR_VENCEU ) {
				*jogada = jog->nova();
				*posX = p->getPosX();
				*posY = p->getPosY();
				peso = 100;
			}
									
			if ( jog->getCaptura() != NULL ) {												
				float pecaCapPeso = this->calculaPeso( jog->getCaptura() );				
				if ( jogo->getNivel() == Jogo::NIVEL_FACIL ) {
					if ( pecaCapPeso >= peso ) {				
						*jogada = jog->nova();
						*posX = p->getPosX();
						*posY = p->getPosY();
														
						peso = pecaCapPeso;																																
					}
				} else {					
					if ( capJogada ) {
						if ( pecaCapPeso - pecaPeso >= peso ) {							
							*jogada = jog->nova();
							*posX = p->getPosX();
							*posY = p->getPosY();
							
							peso = pecaCapPeso - pecaPeso;																														
						}
					} else {								
						if ( pecaCapPeso >= peso ) {				
							*jogada = jog->nova();
							*posX = p->getPosX();
							*posY = p->getPosY();
															
							peso = pecaCapPeso;																																
						}						
					}
				}
			} 									
																																									
			if ( capPeca ) {																	
				if ( jogo->getNivel()  == Jogo::NIVEL_FACIL ) {				
					if ( !capJogada ) {
						if ( pecaPeso >= peso ) {					
							*jogada = jog->nova();
							*posX = p->getPosX();
							*posY = p->getPosY();
													
							peso = pecaPeso;									
						}												
					}										
				} else {			
					bool naoAchou = true;
					if ( jogo->getNivel() == Jogo::NIVEL_DIFICIL ) {
						naoAchou = false;
						
						bool cap_cap = jogo->isCaptura( jGer, cps, jps, cps, p->getPosX(), p->getPosY(), false );
						if ( cap_cap ) {
							Peca* pecaQueCaptura = jogo->pecaCaptura( jGer, jps, jps, cps, p->getPosX(), p->getPosY(), false );
							if ( pecaQueCaptura != NULL ) {
								float pecaQueCapturaPeso = this->calculaPeso( pecaQueCaptura );						
								if ( ( pecaQueCapturaPeso - pecaPeso ) > peso && ( pecaQueCapturaPeso - pecaPeso ) > 0 ) {
									*jogada = jog->nova();
									*posX = p->getPosX();
									*posY = p->getPosY();
																		
									peso = pecaQueCapturaPeso - pecaPeso;															
								} if ( pecaPeso > pecaQueCapturaPeso ) {
									naoAchou = true;
								}
							}					
						} 										
					}
					
					if ( naoAchou ) {																															
						Peca* capturada = NULL;
						float max = INT32_MIN;
						for( int k = 0; k < Jogo::N_PECAS; k++ ) {
							Peca* p2 = jogo->getPeca( cps, k );
							if ( p2 == NULL )
								continue;
							
							bool cpt = jogo->isCaptura( jGer, jps, jps, cps, p2->getPosX(), p2->getPosY(), false );
							if ( cpt ) {
								int cp = this->calculaPeso( p2 );													
								if ( cp > max ) {							
									capturada = p2;		
									max = cp;
								}
							}
						}																			
		
						if ( capturada == NULL ) {
							if ( !capJogada ) {
								if ( pecaPeso >= peso ) {					
									*jogada = jog->nova();
									*posX = p->getPosX();
									*posY = p->getPosY();
															
									peso = pecaPeso;									
								}												
							}
						} else {					
							if ( pecaPeso - max >= peso ) {
								*jogada = jog->nova();
								*posX = p->getPosX();
								*posY = p->getPosY();
								
								peso = pecaPeso - max;							
							}																
						}														
					}
				}
			}																						
																
			Peca* rei = jogo->getPecaRei( jps );								
			
			bool isCap = jogo->isCaptura( jGer, cps, jps, cps, jog->getPosX(), jog->getPosY(), false );										
			if ( isCap ) {
				Peca* pecaCpt = jogo->pecaCaptura( jGer, jps, jps, cps, jog->getPosX(), jog->getPosY(), false, false );
				if ( pecaCpt != NULL )					
					if ( !pecaCpt->isIgual( rei ) )
						isCap = false;				
			}			
					
			if ( ( !capJogada || isCap ) && naoXequeCont == 0 ){						
				bool xeque = jogo->isReiEmXeque( jGer, cps, jps, cps, true );
				if ( xeque ) {
					float d = sqrt( pow( jog->getPosX() - rei->getPosX(), 2 ) + pow( jog->getPosY() - rei->getPosY(), 2 ) );
					float xequePeso = 3 + ( 0.01f * pecaPeso ) - ( 0.01f * d );															
											
					if ( isCap )						
						xequePeso *= 1.2f;												
																													
					if( jogo->getUltimaPecaComputador() != NULL )
						if( p->isIgual( jogo->getUltimaPecaComputador() ) )
							xequePeso -= 2;											
					
					if ( xequePeso > peso ) {						
						*jogada = jog->nova();
						*posX = p->getPosX();
						*posY = p->getPosY();
					
						peso = xequePeso;						

						jogadaXeque = *jogada;
					}
				}
			}
			
			if ( p->getTipo() == Jogo::PEAO ) {
				if ( jog->getPosX() == p->getPosX() && jog->getPosY() == ( p->getPosY() + 1 ) ) {				
					if ( p->getPosY() > 1 ) {
						bool capPeao = jogo->isCaptura( jGer, jps, jps, cps, jog->getPosX(), jog->getPosY(), false );
						if ( !capPeao ) {						
							Peca* p1 = jogo->getPeca( jps, cps, p->getPosX() - 1, p->getPosY() + 2 );
							Peca* p2 = jogo->getPeca( jps, cps, p->getPosX() + 1, p->getPosY() + 2 );
							
							if ( p1 == NULL && p2 == NULL ) {
								bool capVizinha = false;
								
								if ( jogo->getNivel() == Jogo::NIVEL_DIFICIL ) {										
									for( int k = -1; !capVizinha && k <= 1; k++ ) {
										for( int l = -1; !capVizinha && l <= 1; l++ ) {
											if ( k != 0 && l != 0 ) {
												int x = p->getPosX() + k;
												int y = p->getPosY() + l;
												Peca* pc = jogo->getPeca( cps, x, y );
												if ( pc != NULL )
													capVizinha = jogo->isCaptura( jGer, jps, jps, cps, x, y, false );
											}
										}					
									}
								}
								
								if ( !capVizinha ) {								
									if ( 0.01f > peso ) {						
										*jogada = jog->nova();
										*posX = p->getPosX();
										*posY = p->getPosY();
										
										peso = 0.01f;	
									}
								}
							}	
						}											
					}
				}
			}
		
			jogo->deleta_pecas( jps );
			jogo->deleta_pecas( cps );											
		}		
			
	}		
	
	if ( peso < 0 ) {		
		if ( jogo->getNivel() == Jogo::NIVEL_FACIL ) {
			this->sorteiaJogada( posX, posY, jogada, jogPecas, compPecas );			
		} else {		
			bool jogou = this->tentaDominioDoCentro( posX, posY, jogada, jogPecas, compPecas );
			if ( !jogou )
				this->sorteiaJogada( posX, posY, jogada, jogPecas, compPecas );																						
		}
	}
			
	if ( *jogada == jogadaXeque ) {
		if ( xequeCont <  MAX_XEQUE_CONT ) {		
			xequeCont++;		
			if ( xequeCont == MAX_XEQUE_CONT ) {
				naoXequeCont = MAX_XEQUE_CONT;									
				xequeCont = 0;
			}
		}
	} else {
		if ( naoXequeCont > 0 )
			naoXequeCont--;		
	}	
		
	jogo->deleta_pecas( jogPecas );
	jogo->deleta_pecas( compPecas );	
}

bool Algoritmo::tentaDominioDoCentro( int* posX, int* posY, Jogada** jogada, Peca* jogPecas[ Jogo::N_PECAS ], Peca* compPecas[ Jogo::N_PECAS ] ) {
	bool achou = false;
			
	Peca* peaoEsq = jogo->getPecaPeaoMeioEsq( compPecas );
	if ( peaoEsq != NULL )
		if ( peaoEsq->getMoveuContador() == 0 )
			achou = this->tentaDominioDoCentro( peaoEsq, posX, posY, jogada, jogPecas, compPecas );					
			
	if ( !achou ) {
		Peca* peaoDir = jogo->getPecaPeaoMeioDir( compPecas );
		if ( peaoDir != NULL )
			if ( peaoDir->getMoveuContador() == 0 )
				achou = this->tentaDominioDoCentro( peaoDir, posX, posY, jogada, jogPecas, compPecas );		
	}		
	
	if ( !achou ) {
		Peca* cavaloEsq = jogo->getPecaCavaloEsq( compPecas );
		if ( cavaloEsq != NULL )
			if( cavaloEsq->getMoveuContador() == 0 )			
				achou = this->tentaDominioDoCentro( cavaloEsq, posX, posY, jogada, jogPecas, compPecas );			
	}

	if ( !achou ) {
		Peca* cavaloDir = jogo->getPecaCavaloDir( compPecas );
		if ( cavaloDir != NULL )
			if( cavaloDir->getMoveuContador() == 0 )
				achou = this->tentaDominioDoCentro( cavaloDir, posX, posY, jogada, jogPecas, compPecas );				
	}		
	
	if ( !achou ) {
		Peca* rei = jogo->getPecaRei( compPecas );
		if ( rei != NULL )
			if ( rei->getMoveuContador() == 0 )			
				achou = this->tentaDominioDoCentro( rei, posX, posY, jogada, jogPecas, compPecas );			
	}
		
	if ( !achou ) {
		Peca* bispoDir = jogo->getPecaBispoDir( compPecas );
		if ( bispoDir != NULL )
			if ( bispoDir->getMoveuContador() == 0 )
				achou = this->tentaDominioDoCentro( bispoDir, posX, posY, jogada, jogPecas, compPecas );
	}				
	
	return achou;
} 

bool Algoritmo::tentaDominioDoCentro( Peca* peca, int* posX, int* posY, Jogada** jogada, Peca* jogPecas[ Jogo::N_PECAS ], Peca* compPecas[ Jogo::N_PECAS ] ) {		
	JogadaLista* lista = new JogadaLista();
		
	JogoPecas* pecas = new JogoPecas( jogo );
	pecas->setPecas( jogPecas, compPecas );
	
	jGer->calculaJogadasPossiveis( lista, pecas, peca->getPosX(), peca->getPosY(), peca->getTipo(), true, false );
	jGer->filtraJogadas( lista, peca->getPosX(), peca->getPosY(), true );
	
	bool tentar = this->isTentarDominioDoCentro( peca, lista, jogPecas, compPecas );
	
	bool achou = false;	
	int peaoPeso = 0;
	int bispoPeso = 0;
		
	int tam = lista->getTam();	
	for( int i = 0; !achou && tentar && i < tam; i++ ) {
		Jogada* jog = lista->getJogada( i );
		
		Peca* jps[ Jogo::N_PECAS ];
		Peca* cps[ Jogo::N_PECAS ];
	
		jogo->copia_pecas( jps, cps, jogPecas, compPecas );				
		jogo->move( jps, cps, peca->getPosX(), peca->getPosY(), jog->getPosX(), jog->getPosY() );										
		
		bool cap = jogo->isCaptura( jGer, jps, jps, cps, jog->getPosX(), jog->getPosY(), false );							
		if ( !cap ) {		
			if ( peca->getTipo() == Jogo::PEAO ) {
				if ( jog->getPosX() == 3 || jog->getPosX() == 4 ) {					
					bool processa = true;
					if ( jog->getPosY() == 2 ) {
						Peca* cav_esq = jogo->getPecaCavaloEsq( cps );
						Peca* cav_dir = jogo->getPecaCavaloDir( cps );
						
						if ( cav_esq != NULL )
							processa = cav_esq->getMoveuContador() > 0;
						if ( processa && cav_dir != NULL ) 
							processa = cav_dir->getMoveuContador() > 0;												
					}
					
					if ( processa ) {						
						int pso = ( jog->getPosY() == 3  ? 2 : 1 );
						if ( pso > peaoPeso ) {																	
							*jogada = jog->nova();					
							*posX = peca->getPosX();
							*posY = peca->getPosY();
							
							peaoPeso = pso;
						}
					}
				}
			} else if ( peca->getTipo() == Jogo::CAVALO ){								
				if ( (jog->getPosX() == 2 && jog->getPosY() == 2) || (jog->getPosX() == 5 && jog->getPosY() == 2) ) {
					*jogada = jog->nova();					
					*posX = peca->getPosX();
					*posY = peca->getPosY();
					
					achou = true;
				}	
			} else if ( peca->getTipo() == Jogo::BISPO ) {
				bool processar = true;	
					
				Peca* peao_esq = jogo->getPecaPeaoMeioEsq( cps );
				Peca* peao_dir = jogo->getPecaPeaoMeioDir( cps );
				if ( peao_esq != NULL )	
					processar = peao_esq->getMoveuContador() > 0;
				if ( processar && peao_dir != NULL )
					processar = peao_dir->getMoveuContador() > 0;
									
				if ( processar ) {									
					if ( jog->getPosX() == 1  && jog->getPosY() == 4 ) {					
						if ( 2 > bispoPeso ) {							
							*jogada = jog->nova();					
							*posX = peca->getPosX();
							*posY = peca->getPosY();
							
							bispoPeso = 2;
						}
					} else if ( jog->getPosX() == 4 && jog->getPosY() == 1 ) {
						if ( 1 > bispoPeso ) {							
							*jogada = jog->nova();					
							*posX = peca->getPosX();
							*posY = peca->getPosY();
							
							bispoPeso = 1;
						}
					}			
				}
			} else if ( peca->getTipo() == Jogo::REI ) {				
				if ( jog->getTipo() == Jogada::ROQUE ) {
					*jogada = ((JogadaRoque*)jog)->nova();
					*posX = peca->getPosX();
					*posY = peca->getPosY();
						
					achou = true;
				}
			}
		} 
		
		jogo->deleta_pecas( jps );
		jogo->deleta_pecas( cps );			
	}	
	
	jogo->deleta_jogadas( lista );
	delete pecas;	
	
	if ( peaoPeso > 0 ) 
		return true;
		
	if ( bispoPeso > 0 )
		return true;
	
	return achou;
}

bool Algoritmo::isTentarDominioDoCentro( Peca* peca, JogadaLista* lista, Peca* jogPecas[Jogo::N_PECAS], Peca* compPecas[Jogo::N_PECAS] ) {
	if ( peca->getTipo() == Jogo::PEAO ) {		
		if ( ( peca->getPosX() == 3 || peca->getPosX() == 4 ) && ( peca->getPosY() == 3 ) )
			return false;
	} else {				
		int tam = lista->getTam();
		for( int i = 0; i < tam; i++ ) {
			Jogada* jog = lista->getJogada( i );
			
			if ( ( jog->getPosX() == 3 || jog->getPosX() == 4 ) && ( jog->getPosY() == 3 ) )			
				return false;				
		}
		
		JogadaLista* lista2 = new JogadaLista();
	
		JogoPecas* pecas = new JogoPecas( jogo );
		pecas->setPecas( jogPecas, compPecas );
		
		jGer->calculaJogadasPossiveis( lista2, pecas, peca->getPosX(), peca->getPosY(), peca->getTipo(), false, false );
		jGer->filtraJogadas( lista2, peca->getPosX(), peca->getPosY(), false );
		
		bool tentar = true;
		
		tam = lista2->getTam();
		for( int i = 0; tentar && i < tam; i++ ) {
			Jogada* jog = lista2->getJogada( i );
			
			if ( ( jog->getPosX() == 3 || jog->getPosX() == 4 ) && ( jog->getPosY() == 3 ) )			
				tentar = false;				
		}
		
		return tentar;		
	}
	
	return true;
}

void Algoritmo::sorteiaJogada( int* posX, int* posY, Jogada** jogada, Peca* jogPecas[ Jogo::N_PECAS ], Peca* compPecas[ Jogo::N_PECAS ] ) {	
	int tam = 0;
	for( int i = 0; i < Jogo::N_PECAS; i++ ) {			
		Peca* p = jogo->getPeca( compPecas, i );
		if ( p == NULL )
			continue;
			
		JogadaLista* lista = new JogadaLista();
			
		JogoPecas* jp = new JogoPecas( jogo );
		jp->setPecas( jogPecas, compPecas );		
		
		jGer->calculaJogadasPossiveis( lista, jp, p->getPosX(), p->getPosY(), p->getTipo(), true, false );
		jGer->filtraJogadas( lista, p->getPosX(), p->getPosY(), true );
			
		int ltam = lista->getTam();
		for( int j = 0; j < ltam; j++ )	{
			Jogada* jog = lista->getJogada( j );
			
			Peca* jps[ Jogo::N_PECAS ];
			Peca* cps[ Jogo::N_PECAS ];
			
			jogo->copia_pecas( jps, cps, jogPecas, compPecas );			
			jogo->move( jps, cps, p->getPosX(), p->getPosY(), jog->getPosX(), jog->getPosY() );
			
			bool cap = jogo->isCaptura( jGer, jps, jps, cps, jog->getPosX(), jog->getPosY(), false );
			if ( jogo->getNivel() == Jogo::NIVEL_DIFICIL ) {				
				for( int k = -1; !cap && k <= 1; k++ ) {
					for( int l = -1; !cap && l <= 1; l++ ) {
						if ( k != 0 && l != 0 ) {
							int x = p->getPosX() + k;
							int y = p->getPosY() + l;
							Peca* pc = jogo->getPeca( cps, x, y );
							if ( pc != NULL )
								cap = jogo->isCaptura( jGer, jps, jps, cps, x, y, false );
						}
					}					
				}
			}
			
			if ( !cap ) {
				bool add = true;				
				if ( p->getTipo() == Jogo::REI || p->getTipo() == Jogo::TORRE ) {			
					if( jogo->getQuantCompJogadas() < 25 )
						if ( !jogo->isCompRoqueFeito() )
							add = false;
				} else if ( p->getTipo() == Jogo::CAVALO ) {
					if( jogo->getQuantCompJogadas() < 25 )
						add = false;
				} else if ( p->getTipo() == Jogo::PEAO ) {
					if ( jogo->getQuantCompJogadas() < 10 )
						if ( p->getPosX() != 3 && p->getPosX() != 4 )
							add = false;
				}			
									
				if ( add ) {						 
					jogadasSorteio[ tam ] = jog->nova();			
					pecasSorteio[ tam ] = p->nova();
					tam++;		
				}
			}			
			
			jogo->deleta_pecas( jps );
			jogo->deleta_pecas( cps );			
		}
		
		jogo->deleta_jogadas( lista );
		delete jp;
	}	

	if ( tam > 0 ) {	
		int indice = (int)round( rand() % tam );	
		
		*jogada = jogadasSorteio[ indice ];		
		*posX = pecasSorteio[ indice ]->getPosX();							
		*posY = pecasSorteio[ indice ]->getPosY();
	} else {		
		Peca* p = this->sorteiaPeca( compPecas, jogPecas, compPecas );
		*jogada = this->sorteiaJogada( p, jogPecas, compPecas );
		
		*posX = p->getPosX();
		*posY = p->getPosY();
	}
}

Peca* Algoritmo::sorteiaPeca( Peca* vetor[ Jogo::N_PECAS ], Peca* jogPecas[ Jogo::N_PECAS], Peca* compPecas[ Jogo::N_PECAS ]) {
	Peca* vet[ Jogo::N_PECAS ];
	int vet_tam = 0;
	for( int i = 0; i < Jogo::N_PECAS; i++ )  {	
		if ( vetor[i]->isRemovida() )
			continue;
		
		Peca* p = vetor[i];	
			
		JogadaLista* lista = new JogadaLista();
		
		JogoPecas* pecas = new JogoPecas( jogo );
		pecas->setPecas( jogPecas, compPecas );		
	
		jGer->calculaJogadasPossiveis( lista, pecas, p->getPosX(), p->getPosY(), p->getTipo(), true, false );
		jGer->filtraJogadas( lista, p->getPosX(), p->getPosY(), true );
		
		if ( lista->getTam() > 0 )	
			vet[ vet_tam++ ] = p;						
			
		pecas->deleta_pecas();
	}		
	
	return vet[ (int)round( rand() % vet_tam ) ]->nova();						
}

Jogada* Algoritmo::sorteiaJogada( Peca* peca, Peca* jogPecas[ Jogo::N_PECAS ], Peca* compPecas[ Jogo::N_PECAS ] ) {
	JogadaLista* lista = new JogadaLista();
		
	JogoPecas* pecas = new JogoPecas( jogo );
	pecas->setPecas( jogPecas, compPecas );		
	
	jGer->calculaJogadasPossiveis( lista, pecas, peca->getPosX(), peca->getPosY(), peca->getTipo(), true, false );
	jGer->filtraJogadas( lista, peca->getPosX(), peca->getPosY(), true );
		
	Jogada* jog = lista->getJogada( (int)round( rand() % lista->getTam() ) )->nova();	
	
	jogo->deleta_jogadas( lista );
			
	return jog;
}

