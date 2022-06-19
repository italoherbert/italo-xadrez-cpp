
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
		
		Peca* jogadorPecas[ N_PECAS ];
		Peca* computadorPecas[ N_PECAS ];

		int jogadasDominioCentro[ N_JOGADAS_DOMINIO_CENTRO ][ 5 ] = {
			{ 3, 1, 3, 3, JOGADA_CENTRO_NORMAL },
			{ 6, 0, 5, 2, JOGADA_CENTRO_SE_NAO_CAPTURADA },
			{ 4, 1, 4, 2, JOGADA_CENTRO_SE_NAO_CAPTURADA },
			{ 1, 0, 2, 2, JOGADA_CENTRO_SE_NAO_CAPTURADA },
			{ 0, 5, 1, 4, JOGADA_CENTRO_SE_NAO_CAPTURADA }
		};
				
		JogadaLista* jogadas;
		Peca* jogadaPeca = nullptr;
		
		Peca* ultPeca = nullptr;
		Peca* ultPecaComp = nullptr;
		Peca* ultPecaJog = nullptr;

		int compJogadasCont = 0;
		int compJogadaRepetidaCont = 0;

		int jogadorJogadasCont = 0;
		int jogadorJogadaRepetidaCont = 0;
				
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
					Peca** jogPecas,
					Peca** compPecas,
					int posX, int posY, bool isComp );

		void calculaJogadasPossiveis(
				JogadaLista* lista,
				Pecas* pecas,
				int posX, int posY, int tipo, bool isComp, bool isCaptura );

		bool move( int posX, int posY, int novaPosX, int novaPosY );
		bool move( Peca** pecas1, Peca** pecas2, int posX, int posY, int novaPosX, int novaPosY );
			
		bool isJogadorReiEmXeque();
		bool isCompReiEmXeque();
	
		bool isCaptura( Peca** outras,
					Peca** jogPecas, Peca** compPecas, int posX, int posY, bool isComp );
		
		Peca* pecaCaptura( Peca** outras,
					Peca** jogPecas, Peca** compPecas, int posX, int posY, bool isComp );
					
		bool isCaptura( Peca** outras,
					Peca** jogPecas, Peca** compPecas, int posX, int posY, bool isComp, bool incluirRei );
	
		Peca* pecaCaptura( Peca** outras,
					Peca** jogPecas, Peca** compPecas, int posX, int posY, bool isComp, bool incluirRei );
	
	
		bool isReiEmXeque( Peca** jogPecas, Peca** compPecas, bool isComp );

		int isXequeMateOuEmpate( bool isComp );
		int isXequeMateOuEmpateOuXeque( Peca** jogPecas, Peca** compPecas, bool isComp );

		bool verificaSeJogadaValida( Peca** jps, Peca** cps, int posX1, int posY1, int posX2, int posY2 );
		int isPosicaoValida( int posX, int posY );			

		bool addJogada( JogadaLista* lista, Pecas* pecas, int posX, int posY, bool isComp );					
				
		Tela* getTela();
		
		Peca* getPecaRei( bool isComp );
		
		Peca* getPecaRei( Peca** vetor );
		Peca* getPecaPeaoMeioEsq( Peca** vetor );
		Peca* getPecaPeaoMeioDir( Peca** vetor );
		Peca* getPecaCavaloEsq( Peca** vetor );
		Peca* getPecaCavaloDir( Peca** vetor );
		Peca* getPecaBispoEsq( Peca** vetor );
		Peca* getPecaBispoDir( Peca** vetor );

		Peca* getJogadorPeca( int indice );
		Peca* getComputadorPeca( int indice );
		
		Peca* getJogadorPeca( int posX, int posY );
		Peca* getComputadorPeca( int posX, int posY );

		Peca* getPeca( int posX, int posY );
	
		Peca* getPeca( Peca** jogPecas, Peca** compPecas, int posX, int posY );
		Peca* getPeca( Peca** vetor, int posX, int posY );
		Peca* getPeca( Peca** vetor, int indice );
		
		Peca** getJogadorPecas();
		Peca** getComputadorPecas();
										
		Jogada* getJogada( int posX, int posY );
		
		JogadaLista* getJogadasPossiveis();									
		
		void registraRoque( bool isComp );
		
		void copia_pecas( Peca** novoJPs, Peca** novoCPs );
		void copia_pecas( Pecas* pecas, Peca** novoJPs, Peca** novoCPs );
		void copia_pecas( Peca** novoJPs, Peca** novoCPs, Peca** jps, Peca** cps );
		
		void deleta_pecas();
		void deleta_pecas( Pecas* pecas );
		
		void deleta_pecas( Peca** vetor );
		void deleta_pecas( Peca** vetor, int tam );

		void deleta_jogadas( JogadaLista* lista );

		bool isVezComputador();		
		void setVezComputador( bool b );

		Peca* getCompOuJogadorUltimaPeca( bool isComp );

		Peca* getUltimaPeca();
		void setUltimaPeca( Peca* peca );

		int getJogadaRepetidaCont( bool isComp );
		void incJogadaRepetidaCont( bool isComp );
		void zeraJogadaRepetidaCont( bool isComp );

		void incJogadasCont( bool isComp );
		int getJogadasCont( bool isComp );

		Peca* getJogadorJogadaPeca();
		void setJogadorJogadaPeca( Peca* peca );

		bool isCompRoqueFeito();
		bool isJogRoqueFeito();

		int* getJogadaDominioCentro( int i );
						
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
