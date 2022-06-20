
#include "abertura_grafico.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>

AberturaGrafico::AberturaGrafico( GUI* gui ) {
	this->gui = gui;
	this->aberturaIMG = NULL;
	
	corTexto->r = 255;
	corTexto->g = 255;
	corTexto->b = 255;

	corFundo->r = 0;
	corFundo->g = 0;
	corFundo->b = 0;

	corTextoBTSobre->r = 255;
	corTextoBTSobre->g = 255;
	corTextoBTSobre->b = 255;
	
	corFundoBTSobre->r = 0;
	corFundoBTSobre->g = 0;
	corFundoBTSobre->b = 200;

	strcpy( maxOpcaoTextDefaultStr, "##########" );
	strcpy( opcoesStr, "Opções" );
	strcpy( jogarStr, "Jogar" );
	strcpy( humanoStr, "Humano" );
	strcpy( facilStr, "Fácil" );
	strcpy( normalStr, "Normal" );
	strcpy( dificilStr, "Difícil" );
}

void AberturaGrafico::inicializa() {	
	aberturaIMG = IMG_Load( "img/abertura.png" );

	int espacamento = MENU_ABERTURA_ESP;
		
	int espBT_H = MENU_ABERTURA_ESP_BT_H;
	int espBT_V = MENU_ABERTURA_ESP_BT_V;
	
	int larguraFundoTexto = MENU_ABERTURA_LARGURA_FUNDO_TEXTO;
	
	int x = espacamento;
	int y = espacamento;

	TTF_Font* fonte = TTF_OpenFont( "BASKVILL.TTF", 24 );

	int msg_l, msg_a;	
	TTF_SizeText( fonte, opcoesStr, &msg_l, &msg_a );

	opcoesTituloRet = new SDL_Rect;
	opcoesTituloRet->x = x + ( ( larguraFundoTexto - msg_l ) / 2 );
	opcoesTituloRet->y = y + espBT_V;
	opcoesTituloRet->w = msg_l;
	opcoesTituloRet->h = msg_a;
	
	y += opcoesTituloRet->h + ( 2 * espacamento ) + ( 2 * espBT_V );
		
	jogadorTextoOpcaoRet = new SDL_Rect;
	jogadorTextoOpcaoRet->x = x + espBT_H;
	jogadorTextoOpcaoRet->y = y + espBT_V;
	jogadorTextoOpcaoRet->w = msg_l;
	jogadorTextoOpcaoRet->h  = msg_a;

	jogadorOpcaoRet = new SDL_Rect;
	jogadorOpcaoRet->x = x;
	jogadorOpcaoRet->y = y;
	jogadorOpcaoRet->w = larguraFundoTexto;
	jogadorOpcaoRet->h = ( 2 * espBT_V ) + msg_a;

	y += jogadorOpcaoRet->h + ( 2 * espacamento );

	computadorTextoOpcaoRet = new SDL_Rect;
	computadorTextoOpcaoRet->x = x + espBT_H;
	computadorTextoOpcaoRet->y = y + espBT_V;
	computadorTextoOpcaoRet->w = msg_l;
	computadorTextoOpcaoRet->h  = msg_a;

	computadorOpcaoRet = new SDL_Rect;
	computadorOpcaoRet->x = x;
	computadorOpcaoRet->y = y;
	computadorOpcaoRet->w = larguraFundoTexto;
	computadorOpcaoRet->h = ( 2 * espBT_V ) + msg_a;
		
	y += computadorOpcaoRet->h + ( 2 * espacamento );
	
	jogarBTTextoOpcaoRet = new SDL_Rect;
	jogarBTTextoOpcaoRet->x = x + espBT_H;
	jogarBTTextoOpcaoRet->y = y + espBT_V;
	jogarBTTextoOpcaoRet->w = msg_l;
	jogarBTTextoOpcaoRet->h  = msg_a;

	jogarBTOpcaoRet = new SDL_Rect;
	jogarBTOpcaoRet->x = x;
	jogarBTOpcaoRet->y = y;
	jogarBTOpcaoRet->w = larguraFundoTexto;
	jogarBTOpcaoRet->h = ( 2 * espBT_V ) + msg_a;
	
	y += jogarBTOpcaoRet->h + espacamento;
	
	menuRet = new SDL_Rect;
	menuRet->w = ( 2 * espacamento ) + larguraFundoTexto;
	menuRet->h = y;
			
	int tela_l, tela_a;	
	gui->carregaTelaDIM( &tela_l, &tela_a );	
	
	menuRet->x = ( tela_l - menuRet->w ) / 2;
	menuRet->y = 200;

	TTF_CloseFont( fonte );
}

void AberturaGrafico::finaliza() {
	SDL_FreeSurface( aberturaIMG );
}

void AberturaGrafico::sobreOpcao( int opcao ) {
	jogadorTextoOpcaoCor = corTexto;
	computadorTextoOpcaoCor = corTexto;
	jogarBTTextoOpcaoCor = corTexto;
	
	jogadorFundoOpcaoCor = corFundo;
	computadorFundoOpcaoCor = corFundo;
	jogarBTFundoOpcaoCor = corFundo;
	
	switch( opcao ) {
		case OPCAO_SET_TIPO_JOGADOR:
			jogadorTextoOpcaoCor = corTextoBTSobre;
			jogadorFundoOpcaoCor = corFundoBTSobre;
			break;
		case OPCAO_SET_TIPO_COMPUTADOR:
			computadorTextoOpcaoCor = corTextoBTSobre;
			computadorFundoOpcaoCor = corFundoBTSobre;
			break;
		case OPCAO_JOGAR:
			jogarBTTextoOpcaoCor = corTextoBTSobre;
			jogarBTFundoOpcaoCor = corFundoBTSobre;
			break;		
	}				
}

void AberturaGrafico::desenha( SDL_Renderer* pintor ) {		
	SDL_SetRenderDrawColor( pintor, 0, 0, 0, SDL_ALPHA_OPAQUE );
	SDL_RenderClear( pintor );
		
	if ( aberturaIMG != NULL ) {			
		int l, a;	
		gui->carregaTelaDIM( &l, &a );
	
		SDL_Rect* ret = new SDL_Rect;
		
	 	ret->x = ( l - aberturaIMG->w ) / 2;
	 	ret->y = ( a - aberturaIMG->h ) / 2;
	 	ret->w = aberturaIMG->w;
	 	ret->h = aberturaIMG->h;
						
		SDL_Texture* tx = SDL_CreateTextureFromSurface( pintor, aberturaIMG );
		SDL_RenderCopy( pintor, tx, NULL, ret );
		SDL_DestroyTexture( tx );
	}	
	
	this->desenhaMenu( pintor );
	
	SDL_RenderPresent( pintor );

}

void AberturaGrafico::desenhaMenu( SDL_Renderer* pintor ) {
	this->desenhaTexto( pintor, opcoesTituloRet, opcoesStr, corTexto );
	
	this->desenhaBTFundo( pintor, jogadorOpcaoRet, jogadorFundoOpcaoCor );
	this->desenhaBTFundo( pintor, computadorOpcaoRet, computadorFundoOpcaoCor );
	this->desenhaBTFundo( pintor, jogarBTOpcaoRet, jogarBTFundoOpcaoCor );
	
	char* jogador1OpcaoTexto = this->getJogadorStringTipo( this->jogador1Tipo );
	char* jogador2OpcaoTexto = this->getJogadorStringTipo( this->jogador2Tipo );

	this->desenhaTexto( pintor, jogadorTextoOpcaoRet, jogador1OpcaoTexto, jogadorTextoOpcaoCor );
	this->desenhaTexto( pintor, computadorTextoOpcaoRet, jogador2OpcaoTexto, computadorTextoOpcaoCor );
	this->desenhaTexto( pintor, jogarBTOpcaoRet, jogarStr, jogarBTTextoOpcaoCor );
}

void AberturaGrafico::desenhaTexto( SDL_Renderer* pintor, SDL_Rect* rect, char* texto, SDL_Color* cor ) {
	TTF_Font* fonte = TTF_OpenFont( "BASKVILL.TTF", 24 );

	SDL_Rect* texto_ret = new SDL_Rect;
	texto_ret->x = menuRet->x + rect->x;
	texto_ret->y = menuRet->y + rect->y;
	texto_ret->w = rect->w;
	texto_ret->h = rect->h;

	SDL_Color cor2 = { cor->r, cor->g, cor->b };

	SDL_Surface* texto_sf = TTF_RenderText_Solid( fonte, texto, cor2 );
	SDL_Texture* tx = SDL_CreateTextureFromSurface( pintor, texto_sf );
	SDL_RenderCopy( pintor, tx, NULL, texto_ret );
	SDL_FreeSurface( texto_sf );
	SDL_DestroyTexture( tx );

	TTF_CloseFont( fonte );
}

void AberturaGrafico::desenhaBTFundo( SDL_Renderer* pintor, SDL_Rect* rect, SDL_Color* cor ) {

	SDL_Rect* fundo_ret = new SDL_Rect;
	fundo_ret->x = menuRet->x + rect->x;
	fundo_ret->y = menuRet->y + rect->y;
	fundo_ret->w = rect->w;
	fundo_ret->h = rect->h;

	SDL_SetRenderDrawColor( pintor, cor->r, cor->g, cor->b, SDL_ALPHA_OPAQUE );
	SDL_RenderFillRect( pintor, fundo_ret );

	SDL_SetRenderDrawColor( pintor, 255, 255, 255, SDL_ALPHA_OPAQUE );
	SDL_RenderDrawRect( pintor, fundo_ret );
}

bool AberturaGrafico::isMouseJogadorUmOpBT( int mouseX, int mouseY ) {
	return this->isMouseEmBT( jogadorOpcaoRet, mouseX, mouseY );
}

bool AberturaGrafico::isMouseJogador2OpBT( int mouseX, int mouseY ) {
	return this->isMouseEmBT( computadorOpcaoRet, mouseX, mouseY );
}

bool AberturaGrafico::isMouseJogarBT( int mouseX, int mouseY ) {
	return this->isMouseEmBT( jogarBTOpcaoRet, mouseX, mouseY );
}

bool AberturaGrafico::isMouseEmBT( SDL_Rect* rect, int mouseX, int mouseY )	{
	int x1 = menuRet->x + rect->x;
	int y1 = menuRet->y + rect->y;
	int x2 = menuRet->x + rect->x + rect->w;
	int y2 = menuRet->y + rect->y + rect->h;
	
	return ( mouseX >= x1 && mouseX <= x2 && mouseY >= y1 && mouseY <= y2 );	
}

char* AberturaGrafico::getJogadorStringTipo( int tipo ) {
	switch( tipo ) {
		case HUMANO:  return humanoStr;
		case FACIL:   return facilStr;
		case NORMAL:  return normalStr;
		case DIFICIL: return dificilStr;
	}
	return NULL;
}

void AberturaGrafico::setJogadorUmTipo( int tipo ) {
	jogador1Tipo = tipo;
}

void AberturaGrafico::setJogadorDoisTipo( int tipo ) {
	jogador2Tipo = tipo;
}
