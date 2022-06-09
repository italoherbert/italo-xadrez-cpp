
#ifndef JOGO_H
#define JOGO_H

#include "../jogada/jogada_util.h"
#include "jogada_lista.h"
#include "movimento.h"
#include "peca.h"
#include "pecas.h"
#include "tela.h"
#include "tela_driver.h"

class Jogo : public Pecas {	
	private:		
		Tela* tela;
		
		Peca* jogadorPecas[ 16 ];
		Peca* computadorPecas[ 16 ];
				
		JogadaLista* jogadas;
		Peca* jogadaPeca = nullptr;
		
		Peca* ultPeca = nullptr;
		Peca* ultPecaComp = nullptr;
		Peca* ultPecaJog = nullptr;
				
		bool vezComputador = false;
		int quantCompJogadas = 0;
		bool compRoque = false;
		bool jogRoque = false;
		bool audioLigado = true;
		
		int nivel = NIVEL_DIFICIL;
		int fim = 0;
		
		Movimento* movimento = nullptr;
							
	public:			
		const static int NIVEL_NENHUM = 0;
		const static int NIVEL_FACIL = 1;
		const static int NIVEL_NORMAL = 2;
		const static int NIVEL_DIFICIL = 3;
	
		const static int JOGADOR_VENCEU = 1;
		const static int COMPUTADOR_VENCEU = 2;
		const static int EMPATE = 3;
		const static int NAO_FIM = 0;
		
		const static int N_PECAS = 16;
		
		const static int TORRE = 1;
		const static int CAVALO = 2;
		const static int BISPO = 3;
		const static int RAINHA = 4;
		const static int REI = 5;
		const static int PEAO = 6;
		
		const static int PECA_REI_INDICE = 4;
		const static int PECA_PEAO_MEIO_ESQ_INDICE = 11;
		const static int PECA_PEAO_MEIO_DIR_INDICE = 12;
		const static int PECA_CAVALO_ESQ_INDICE = 1;
		const static int PECA_CAVALO_DIR_INDICE = 6;
		const static int PECA_BISPO_ESQ_INDICE = 2;
		const static int PECA_BISPO_DIR_INDICE = 5;		
		
		const static int TORRE_ESQ_INDICE = 0;
		const static int TORRE_DIR_INDICE = 7;
				
		Jogo( TelaDriver* drv );
		
		void reinicia();
		
		bool move( int posX, int posY, int novaPosX, int novaPosY );
		bool move( Peca* pecas1[N_PECAS], Peca* pecas2[N_PECAS], int posX, int posY, int novaPosX, int novaPosY );		
			
		bool isJogadorReiEmXeque( JogadaUtil* util );
		bool isCompReiEmXeque( JogadaUtil* util );
	
		bool isCaptura( JogadaUtil* util, Peca* outras[N_PECAS], 
					Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY, bool isComp );
		
		Peca* pecaCaptura( JogadaUtil* util, Peca* outras[N_PECAS], 
					Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY, bool isComp );
					
		bool isCaptura( JogadaUtil* util, Peca* outras[N_PECAS], 
					Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY, bool isComp, bool incluirRei );
	
		Peca* pecaCaptura( JogadaUtil* util, Peca* outras[N_PECAS], 
					Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], int posX, int posY, bool isComp, bool incluirRei );
	
	
		bool isReiEmXeque( JogadaUtil* util, Peca* outras[N_PECAS], 
					Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], bool isComp );
					
		int isXequeMate( JogadaUtil* util, bool isComp );
		int isXequeMate( JogadaUtil* util, Peca* jogPecas[N_PECAS], Peca* compPecas[N_PECAS], bool isComp );
	
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

		Peca* getJogadorJogadaPeca();
		void setJogadorJogadaPeca( Peca* peca );
		
		int getQuantCompJogadas();
		void incQuantCompJogadas();
		
		bool isCompRoqueFeito();
		bool isJogRoqueFeito();
						
		int getFIM();
		void setFim( int fim );								
								
		Movimento* getMovimento();
		void setMovimento( Movimento* movimento );
		
		bool isAudioLigado();
		void setAudioLigado( bool b );
				
		int getNivel();
		void setNivel( int nivel );		
				
		//std::string get_peca_str( int tipo );
};

#endif
