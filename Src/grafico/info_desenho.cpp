
#include "info_desenho.h"

#include <cstring>
#include <SDL2/SDL_ttf.h>

int InfoDesenho::desenha( Jogo* jogo, GUI* gui, SDL_Renderer* pintor ) {
	int brancasNivel = jogo->getNivel( false );
	int pretasNivel = jogo->getNivel( true );
	int vitorias = jogo->getVitoriasCont( false );
	int derrotas = jogo->getVitoriasCont( true );

	const char* brancasNivelStr = jogo->getNivelString( brancasNivel ).c_str();
	const char* pretasNivelStr = jogo->getNivelString( pretasNivel ).c_str();

	const char* vitoriasStr = std::to_string( vitorias ).c_str();
	const char* derrotasStr = std::to_string( derrotas ).c_str();

	int x = borda;

	x = this->desenhaInfo( gui, pintor, brancasNivelRotulo.c_str(), brancasNivelStr, x );
	x = this->desenhaInfo( gui, pintor, pretasNivelRotulo.c_str(), pretasNivelStr, x );
	x = this->desenhaInfo( gui, pintor, vitoriasRotulo.c_str(), vitoriasStr, x );
	x = this->desenhaInfo( gui, pintor, derrotasRotulo.c_str(), derrotasStr, x );

	TTF_Font* fonte = gui->getFonte();
	int msg_l, msg_a;

	TTF_SizeText( fonte, vitoriasStr, &msg_l, &msg_a );

	painelH = msg_a + ( 2 * borda );

	return painelH;
}

int InfoDesenho::desenhaInfo( GUI* gui, SDL_Renderer* pintor, const char* rotulo, const char* info, int x ) {
	TTF_Font* fonte = gui->getInfoFonte();

	SDL_Color corRotulo = { 0, 0, 0 };
	SDL_Color corInfo = { 0, 50, 200 };

	int msg_l, msg_a;

	TTF_SizeText( fonte, rotulo, &msg_l, &msg_a );

	SDL_Rect* brancasNivelRotuloRet = new SDL_Rect;
	brancasNivelRotuloRet->x = x;
	brancasNivelRotuloRet->y = borda;
	brancasNivelRotuloRet->w = msg_l;
	brancasNivelRotuloRet->h = msg_a;

	SDL_Surface* texto_sf = TTF_RenderText_Blended( fonte, rotulo, corRotulo );
	SDL_Texture* tx = SDL_CreateTextureFromSurface( pintor, texto_sf );
	SDL_RenderCopy( pintor, tx, NULL, brancasNivelRotuloRet );
	SDL_FreeSurface( texto_sf );
	SDL_DestroyTexture( tx );

	int x2 = x + brancasNivelRotuloRet->w + rotInfoEsp;

	TTF_SizeText( fonte, info, &msg_l, &msg_a );

	SDL_Rect* brancasNivelInfoRet = new SDL_Rect;
	brancasNivelInfoRet->x = x2;
	brancasNivelInfoRet->y = borda;
	brancasNivelInfoRet->w = msg_l;
	brancasNivelInfoRet->h = msg_a;

	texto_sf = TTF_RenderText_Blended( fonte, info, corInfo );
	tx = SDL_CreateTextureFromSurface( pintor, texto_sf );
	SDL_RenderCopy( pintor, tx, NULL, brancasNivelInfoRet );
	SDL_FreeSurface( texto_sf );
	SDL_DestroyTexture( tx );

	delete brancasNivelRotuloRet;
	delete brancasNivelInfoRet;

	return x2 + msg_l + infoEsp;
}

int InfoDesenho::getPainelAltura() {
	return painelH;
}

