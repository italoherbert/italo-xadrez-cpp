
#ifndef JOGADA_GERENCIADOR_H
#define JOGADA_GERENCIADOR_H

#include "../logica/jogo.h"
#include "../logica/peca.h"
#include "../logica/pecas.h"
#include "bispo_peca_jogada.h"
#include "cavalo_peca_jogada.h"
#include "jogada_util.h"
#include "peao_peca_jogada.h"
#include "rainha_peca_jogada.h"
#include "rei_peca_jogada.h"
#include "torre_peca_jogada.h"

class JogadaGerenciador : public JogadaUtil {
	
	private:
		PeaoPecaJogada* peaoPecaJogada;
		ReiPecaJogada* reiPecaJogada;
		CavaloPecaJogada* cavaloPecaJogada;
		TorrePecaJogada* torrePecaJogada;
		BispoPecaJogada* bispoPecaJogada;
		RainhaPecaJogada* rainhaPecaJogada;
		
		Jogo* jogo;
						
	public:
		JogadaGerenciador( Jogo* jogo );
		~JogadaGerenciador();
		
		void filtraJogadas( JogadaLista* lista, int posX, int posY, bool isComp );
		
		void calculaJogadasPossiveis( JogadaLista* lista, Pecas* pecas, int posX, int posY, int tipo, bool isComp, bool isCaptura );
								
};

#endif
