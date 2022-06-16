
#ifndef JOGO_H
#define JOGO_H


#include "jogada/bispo_peca_jogada.h"
#include "jogada/cavalo_peca_jogada.h"
#include "jogada/peao_peca_jogada.h"
#include "jogada/rainha_peca_jogada.h"
#include "jogada/rei_peca_jogada.h"
#include "jogada/torre_peca_jogada.h"

#include "jogada_lista.h"
#include "movimento.h"
#include "peca.h"
#include "pecas.h"
#include "tela.h"
#include "tela_driver.h"
#include "jogo_constantes.h"
#include "peca_jogada_params.h"

#include <string>

class BispoPecaJogada;
class CavaloPecaJogada;
class PeaoPecaJogada;
class ReiPecaJogada;
class RainhaPecaJogada;
class TorrePecaJogada;

class Jogo : public Pecas, public JogoConstantes {

	private:		
		Tela* tela;
		
		Peca* jogadorPecas[ 16 ];
		Peca* computadorPecas[ 16 ];
				
		JogadaLista* jogadas;
		Peca* jogadaPeca = nullptr;
		
		Peca* ultPeca = nullptr;
		Peca* ultPecaComp = nullptr;
		Peca* ultPecaJog = nullptr;

		int compJogadasCont = 0;
		int compJogadaRepetidaCont = 0;
				
		bool vezComputador = false;
		bool compRoque = false;
		bool jogRoque = false;
		bool audioLigado = true;
		
		int nivel = NIVEL_DIFICIL;
		int fim = 0;
		
		Movimento* movimento = nullptr;

		PeaoPecaJogada* peaoPecaJogada;
		ReiPecaJogada* reiPecaJogada;
		CavaloPecaJogada* cavaloPecaJogada;
		TorrePecaJogada* torrePecaJogada;
		BispoPecaJogada* bispoPecaJogada;
		RainhaPecaJogada* rainhaPecaJogada;
							
	public:
		Jogo( TelaDriver* drv );
		~Jogo();
		
		void reinicia();

		void calculaJogadas( JogadaLista* lista, Pecas* pecas, bool isComp, bool isCaptura );

		void filtraJogadas(
					JogadaLista* lista,
					Peca* jogPecas[ N_PECAS ],
					Peca* compPecas[ N_PECAS],
					int posX, int posY, bool isComp );

		void calculaJogadasPossiveis(
				JogadaLista* lista,
				Pecas* pecas,
				int posX, int posY, int tipo, bool isComp, bool isCaptura );

		bool move( int posX, int posY, int novaPosX, int novaPosY );
		bool move( Peca* pecas1[N_PECAS], Peca* pecas2[N_PECAS], int posX, int posY, int novaPosX, int novaPosY );		
			
		bool isJogadorReiEmXeque();
		bool isCompReiEmXeque();
	
		bool isCaptura( Peca* outras[N_PECAS],
					Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY, bool isComp );
		
		Peca* pecaCaptura( Peca* outras[N_PECAS],
					Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY, bool isComp );
					
		bool isCaptura( Peca* outras[N_PECAS],
					Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY, bool isComp, bool incluirRei );
	
		Peca* pecaCaptura( Peca* outras[N_PECAS],
					Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY, bool isComp, bool incluirRei );
	
	
		bool isReiEmXeque( Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], bool isComp );

		int isXequeMateOuEmpate( bool isComp );
		int isXequeMateOuEmpate( Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], bool isComp );

		int isPosicaoValida( int posX, int posY );			
		bool addJogada( JogadaLista* lista, Pecas* pecas, int posX, int posY, bool isComp );					
				
		Tela* getTela();
		
		Peca* getPecaRei( bool isComp );
		
		Peca* getPecaRei( Peca* vetor[N_PECAS] );		
		Peca* getPecaPeaoMeioEsq( Peca* vetor[N_PECAS] );
		Peca* getPecaPeaoMeioDir( Peca* vetor[N_PECAS] );
		Peca* getPecaCavaloEsq( Peca* vetor[N_PECAS] );
		Peca* getPecaCavaloDir( Peca* vetor[N_PECAS] );
		Peca* getPecaBispoEsq( Peca* vetor[N_PECAS] );
		Peca* getPecaBispoDir( Peca* vetor[N_PECAS] );

		Peca* getJogadorPeca( int indice );
		Peca* getComputadorPeca( int indice );
		
		Peca* getJogadorPeca( int posX, int posY );
		Peca* getComputadorPeca( int posX, int posY );

		Peca* getPeca( int posX, int posY );
	
		Peca* getPeca( Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY );	
		Peca* getPeca( Peca* vetor[N_PECAS], int posX, int posY );						
		Peca* getPeca( Peca* vetor[N_PECAS], int indice );								
		
		Peca** getJogadorPecas();
		Peca** getComputadorPecas();
										
		Jogada* getJogada( int posX, int posY );
		
		JogadaLista* getJogadasPossiveis();									
		
		void registraRoque( bool isComp );
		
		void copia_pecas( Peca* novoJPs[N_PECAS], Peca* novoCPs[N_PECAS] );		
		void copia_pecas( Pecas* pecas, Peca* novoJPs[N_PECAS], Peca* novoCPs[N_PECAS] );		
		void copia_pecas( Peca* novoJPs[N_PECAS], Peca* novoCPs[N_PECAS], Peca* jps[N_PECAS], Peca* cps[N_PECAS] );
		
		void deleta_pecas();
		void deleta_pecas( Pecas* pecas );
		
		void deleta_pecas( Peca* vetor[N_PECAS] );
		void deleta_jogadas( JogadaLista* lista );

		bool isVezComputador();		
		void setVezComputador( bool b );
				
		Peca* getUltimaPecaComputador();
		Peca* getUltimaPecaJogador();

		Peca* getUltimaPeca();		
		void setUltimaPeca( Peca* peca );

		int getCompJogadaRepetidaCont();
		void incCompJogadaRepetidaCont();
		void zeraCompJogadaRepetidaCont();

		Peca* getJogadorJogadaPeca();
		void setJogadorJogadaPeca( Peca* peca );

		bool isCompRoqueFeito();
		bool isJogRoqueFeito();

		void incCompJogadasCont();
		int getCompJogadasCont();
						
		int getFIM();
		void setFim( int fim );								
								
		Movimento* getMovimento();
		void setMovimento( Movimento* movimento );
		
		bool isAudioLigado();
		void setAudioLigado( bool b );
				
		int getNivel();
		void setNivel( int nivel );		
				
		std::string get_peca_str( int tipo );
};

#endif
