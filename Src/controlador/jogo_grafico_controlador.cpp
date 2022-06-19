
#include "jogo_grafico_controlador.h"

#include <cmath>

#include "../grafico/audio_ligado_desenho.h"
#include "../logica/jogada_roque.h"

JogoGraficoControlador::JogoGraficoControlador( Jogo* jogo,
		AlgoritmoGerenciador* algGer, Animacao* anim,
		GUI* gui, JogoGrafico* jG, JogoAudio* audio ) {
	this->jogo = jogo;
	this->gui = gui;
	this->jogoGrafico = jG;
	this->audio = audio;
	this->algGer = algGer;
	this->animacao = anim;
	this->pecaSelecionada = NULL;
		
	this->isMensagemDelay = false;	
}

void JogoGraficoControlador::mousePressionado( int x, int y ) {
	if ( jogo->getFIM() != Jogo::NAO_FIM ) {
		jogo->reinicia();

		audio->reinicia();
		gui->reinicia();
	}

	if ( jogo->getMovimento() != NULL )		
		return;
			
	jogoGrafico->getMensagemDesenho()->removeMensagem();
	
	AudioLigadoDesenho* ald = jogoGrafico->getAudioLigadoDesenho();
	if ( ald->isMouseEmAudioBT( x, y ) ) {
		jogo->setAudioLigado( !jogo->isAudioLigado() );
		if ( jogo->isAudioLigado() ) {
			audio->resumeMusica();
		} else {
			audio->pauseMusica();
		}		 
	} else {
		int tx = jogo->getTela()->getTabuleiroX();
		int ty = jogo->getTela()->getTabuleiroY();
		int td = jogo->getTela()->getTabuleiroDIM();
		int cd = jogo->getTela()->getCelulaDIM();			
	
		bool moveu = false;
	
		if( x >= tx && x < tx+td && y >= ty && y < ty+td ) {
			int posX = ( x - tx ) / cd;
			int posY = ( y - ty ) / cd;			
			
			if ( pecaSelecionada != NULL ) {			
				Peca* p = jogo->getPeca( posX, posY );
				if ( p != NULL ) {
					if ( !p->isIgual( pecaSelecionada ) && p->isDeComp() == jogo->isVezComputador() ) {
						jogo->getJogadasPossiveis()->limpaJogadas();
						jogo->setJogadorJogadaPeca( NULL );
						pecaSelecionada = NULL;
					}
				}
			}

			if ( !jogo->isVezComputador() ) {
				if ( pecaSelecionada == NULL ) {
					Peca* peca = jogo->getJogadorPeca( posX, posY );
					if ( peca != NULL ) {
						bool selecionada = this->selecionaPeca( posX, posY, false );				
						if ( selecionada ) {
							jogo->setJogadorJogadaPeca( peca );
							pecaSelecionada = peca;
						}
					}
				} else {							
					Jogada* jogada = jogo->getJogada( posX, posY );
					if ( jogada != NULL ) {				
						jogo->setMovimento( animacao->criaMovimentos( jogada, pecaSelecionada ) );	
					} else {
						jogo->getJogadasPossiveis()->limpaJogadas();
						jogo->setJogadorJogadaPeca( NULL );
						pecaSelecionada = NULL;	
					}
				} 			
			}
							
			this->verificaXequeEXequeMate( moveu );
		}
	}
}

void JogoGraficoControlador::teclaPressionada( int tecla ) {		
	if ( jogo->getFIM() == Jogo::NAO_FIM ) {
		if ( tecla == TECLA_ESQ ) {
			jogo->reinicia();
			audio->reinicia();
		
			gui->reinicia();
		}
	} else {
		jogo->reinicia();
		audio->reinicia();

		gui->reinicia();
	}		
	jogoGrafico->getMensagemDesenho()->removeMensagem();
}

void JogoGraficoControlador::executando() {
	audio->tocaAudio();

	if ( jogo->getMovimento() == NULL ) {
		this->processaMensagem();						

		//if ( jogo->isVezComputador() && jogo->getFIM() == Jogo::NAO_FIM ) {
		bool isComp = jogo->isVezComputador();
		if ( jogo->getFIM() == Jogo::NAO_FIM ) {
			Jogada* jogada;
			int posX, posY;
			
			algGer->calculaMelhorJogada( &posX, &posY, &jogada, isComp );

			Peca* peca = jogo->getPeca( posX, posY );			
			jogo->setMovimento( animacao->criaMovimentos( jogada, peca ) );
		}
	} else {		
		Movimento* movimento = jogo->getMovimento();					
		
		bool animou = animacao->move( movimento, Consts::ANIM_RAIO_INC );
		if ( animou ) {		
			int posX = movimento->getMovimento1()->getPeca()->getPosX();
			int posY = movimento->getMovimento1()->getPeca()->getPosY();

			Jogada* jogada = movimento->getJogada();

			Peca* peca = jogo->getPeca( posX, posY );
			peca->setAnimPosX( 0 );
			peca->setAnimPosY( 0 );

			bool moveu;	
						
			if( jogada->getTipo() == Jogada::ROQUE ) {						
				JogadaRoque* jr = (JogadaRoque*)jogada;

				Peca* rei = jr->getRei();
				Peca* torre = jr->getTorre();						
				int reiPosX = jr->getReiPosX();
				int reiPosY = jr->getReiPosY();
				int torrePosX = jr->getTorrePosX();
				int torrePosY = jr->getTorrePosY();
				
				Peca* pTorre = jogo->getPeca( torre->getPosX(), torre->getPosY() );
				pTorre->setAnimPosX( 0 );
				pTorre->setAnimPosY( 0 );																		
																										
				jogo->move( rei->getPosX(), rei->getPosY(), reiPosX, reiPosY );																												
				jogo->move( torre->getPosX(), torre->getPosY(), torrePosX, torrePosY );																				
				
				jogo->registraRoque( peca->isDeComp() );				
				
				moveu = true;
			} else if ( jogada->getTipo() == Jogada::EN_PASSANT ){
				int capPosX = jogada->getCaptura()->getPosX();
				int capPosY = jogada->getCaptura()->getPosY();

				Peca* capturada = jogo->getPeca( capPosX, capPosY );
				capturada->setRemovida( true );

				jogo->move( posX, posY, jogada->getPosX(), jogada->getPosY() );

				moveu = true;
			} else {
				moveu = jogo->move( posX, posY, jogada->getPosX(), jogada->getPosY() );
			}
																				
			if ( moveu ) {
				if ( jogada->getCaptura() != NULL ) {
					audio->setNumAudio( JogoAudio::AUDIO_CAPTURA );
				} else {										
					if ( jogo->isVezComputador() )			
						audio->setNumAudio( JogoAudio::AUDIO_COMP_JOGOU );				
					else audio->setNumAudio( JogoAudio::AUDIO_JOG_JOGOU );				
				}
			
				jogo->setVezComputador( !jogo->isVezComputador() );
								
				peca->setMoveuContador( peca->getMoveuContador() + 1 );							
						
				if( peca->getTipo() == Jogo::PEAO )
					if( jogada->getPosY() == 0 || jogada->getPosY() == 7 )
						peca->setTipo( Jogo::RAINHA );						
					
				jogo->setUltimaPeca( peca );
							
				jogo->getJogadasPossiveis()->limpaJogadas();
				jogo->setJogadorJogadaPeca( NULL );
				pecaSelecionada = NULL;	
												
				jogo->setMovimento( NULL );								
			}																					 
									
			this->verificaXequeEXequeMate( moveu );						
		}						
	}
}

bool JogoGraficoControlador::selecionaPeca( int posX, int posY, bool isComp ) {
	Peca* peca = jogo->getPeca( posX, posY );
	if ( peca != NULL ) {
		JogadaLista* lista = jogo->getJogadasPossiveis();
		lista->limpaJogadas();
			
		Peca* jogPecas[ Jogo::N_PECAS ];
		Peca* compPecas[ Jogo::N_PECAS ];
		jogo->copia_pecas( jogPecas, compPecas );

		jogo->calculaJogadasPossiveis( lista, jogo, posX, posY, peca->getTipo(), isComp, false );
		jogo->filtraJogadas( lista, jogPecas, compPecas, posX, posY, isComp );
		
		jogo->deleta_pecas( jogPecas );
		jogo->deleta_pecas( compPecas );

		if ( lista->getTam() == 0 ) {
			bool reiEmXeque = false;
			if ( isComp )
				reiEmXeque = jogo->isCompReiEmXeque();
			else reiEmXeque = jogo->isJogadorReiEmXeque();
			
			if ( reiEmXeque ) {			
				std::string msg = "Seu rei está em xeque!";
				
				jogoGrafico->getMensagemDesenho()->setMensagem( msg );
			} else {
				std::string msg = "Movimento inválido!";
				
				jogoGrafico->getMensagemDesenho()->setMensagem( msg );
			}
			
			audio->setNumAudio( JogoAudio::AUDIO_JOGADA_INVALIDA );
		}
		return true;
	}
	return false;
}

void JogoGraficoControlador::verificaXequeEXequeMate( bool moveu ) {
	int status = jogo->isXequeMateOuEmpate( true );
	if ( status == Jogo::NAO_FIM )
		status = jogo->isXequeMateOuEmpate( false );
	jogo->setFim( status );		
	
	if ( moveu && status == Jogo::NAO_FIM ) {			
		bool reiEmXeque = false;
		
		if ( jogo->isVezComputador() )
			reiEmXeque = jogo->isCompReiEmXeque();
		else reiEmXeque = jogo->isJogadorReiEmXeque();
				
		if ( reiEmXeque ) {									
			jogo->getJogadasPossiveis()->limpaJogadas();
			jogo->setJogadorJogadaPeca( NULL );
			pecaSelecionada = NULL;				
			
			audio->setNumAudio( JogoAudio::AUDIO_XEQUE );

			std::string msg = "Xeque!";

			jogoGrafico->getMensagemDesenho()->setMensagem( msg );
			isMensagemDelay = true;											
		}
	}

	if ( status == Jogo::JOGADOR_VENCEU ) {
		audio->setNumAudio( JogoAudio::AUDIO_VENCEU );
	} else if ( status == Jogo::COMPUTADOR_VENCEU ) {
		audio->setNumAudio( JogoAudio::AUDIO_PERDEU );
	} else if ( status == Jogo::EMPATE ) {
		audio->setNumAudio( JogoAudio::AUDIO_EMPATOU );
	}
}

void JogoGraficoControlador::processaMensagem() {
	if ( isMensagemDelay ) {
		SDL_Delay( Consts::DELAY_MENSAGEM );

		jogoGrafico->getMensagemDesenho()->removeMensagem();
		isMensagemDelay = false;		
	}

	int status = jogo->getFIM();
	if ( status != Jogo::NAO_FIM ) {
		std::string mensagem = "";

		switch( status ) {
			case Jogo::JOGADOR_VENCEU:
				mensagem = "Xeque mate, você ganhou!";
				break;
			case Jogo::COMPUTADOR_VENCEU:
				mensagem = "Xeque mate, você perdeu!";
				break;
			case Jogo::EMPATE:
				mensagem = "O jogo empatou!";
				break;
		}

		if ( !mensagem.empty() )
			jogoGrafico->getMensagemDesenho()->setMensagem( mensagem );
	}
}


