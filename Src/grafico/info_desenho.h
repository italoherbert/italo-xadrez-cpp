
#ifndef PLACAR_DESENHO_H
#define PLACAR_DESENHO_H

#include "../gui/GUI.h"
#include "../logica/jogo.h"

#include <string>

class InfoDesenho {

	private:
		std::string brancasNivelRotulo = "Pretas:";
		std::string pretasNivelRotulo = "Brancas:";
		std::string vitoriasRotulo = "Vitorias:";
		std::string derrotasRotulo = "Derrotas:";

		int painelH = 0;
		int borda = 25;
		int infoEsp = 20;
		int rotInfoEsp = 10;

		int desenhaInfo(
					GUI* gui,
					SDL_Renderer* pintor,
					const char* rotulo,
					const char* info,
					int x );

	public:
		int desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor );

		int getPainelAltura();

};

#endif



