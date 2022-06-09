
#include "abertura_grafico.h"

#include <SDL2/SDL_image.h>
#include <cstring>

AberturaGrafico::AberturaGrafico( GUI* gui ) {
	this->gui = gui;
	this->aberturaIMG = NULL;
	
	corTexto = { 255, 255, 255 };
	corFundo = { 0, 0, 0 };
	
	corTextoBTSobre = { 255, 255, 255 };
	corFundoBTSobre = { 0, 0, 200 };
}

void AberturaGrafico::inicializa() {	
	aberturaIMG = IMG_Load( "img/abertura.png" );
	opcoesTextoRet.cor = corTexto;
	
	facilBT.texto.cor = corTexto;
	normalBT.texto.cor = corTexto;
	dificilBT.texto.cor = corTexto;
	
	facilBT.corFundo = corFundo;
	normalBT.corFundo = corFundo;
	dificilBT.corFundo = corFundo;
	
	char opcoesTxt[127];
		
	char facilBTRotulo[127];
	char normalBTRotulo[127];
	char dificilBTRotulo[127];
	
	strcpy( opcoesTxt, "Dificuldade" );
	
	strcpy( facilBTRotulo, "Facil" );
	strcpy( normalBTRotulo, "Normal" );
	strcpy( dificilBTRotulo, "Dificil" );
				
	TTF_Font* fonte = gui->getMensagemFonte();
		
	int espacamento = Consts::MENU_ABERTURA_ESP;
		
	int espBT_H = Consts::MENU_ABERTURA_ESP_BT_H;
	int espBT_V = Consts::MENU_ABERTURA_ESP_BT_V;
	
	int larguraFundoTexto = Consts::MENU_ABERTURA_LARGURA_FUNDO_TEXTO;	
	
	int x = espacamento;
	int y = espacamento;
		
	int msg_l, msg_a;	
	TTF_SizeText( fonte, opcoesTxt, &msg_l, &msg_a );
				
	strcpy( opcoesTextoRet.rotulo, opcoesTxt );	
			
	opcoesTextoRet.textoRet.x = x + ( ( larguraFundoTexto - msg_l ) / 2 );
	opcoesTextoRet.textoRet.y = y + espBT_V;
	opcoesTextoRet.textoRet.largura = msg_l;
	opcoesTextoRet.textoRet.altura = msg_a;
	
	y += opcoesTextoRet.textoRet.altura + ( 2 * espacamento ) + ( 2 * espBT_V );		
		
	TTF_SizeText( fonte, facilBTRotulo, &msg_l, &msg_a );
								
	strcpy( facilBT.texto.rotulo, facilBTRotulo );	
		
	facilBT.texto.textoRet.x = x + espBT_H;
	facilBT.texto.textoRet.y = y + espBT_V;
	facilBT.texto.textoRet.largura = msg_l;
	facilBT.texto.textoRet.altura  = msg_a;
	facilBT.fundoRet.x = x;
	facilBT.fundoRet.y = y;
	facilBT.fundoRet.largura = larguraFundoTexto;
	facilBT.fundoRet.altura = ( 2 * espBT_V ) + msg_a;			
		
	TTF_SizeText( fonte, normalBTRotulo, &msg_l, &msg_a );
		
	y += facilBT.fundoRet.altura + ( 2 * espacamento );		
		
	strcpy( normalBT.texto.rotulo, normalBTRotulo );		
		
	normalBT.texto.textoRet.x = x + espBT_H;
	normalBT.texto.textoRet.y = y + espBT_V;
	normalBT.texto.textoRet.largura = msg_l;
	normalBT.texto.textoRet.altura  = msg_a;
	normalBT.fundoRet.x = x;
	normalBT.fundoRet.y = y;
	normalBT.fundoRet.largura = larguraFundoTexto;
	normalBT.fundoRet.altura = ( 2 * espBT_V ) + msg_a;

	TTF_SizeText( fonte, dificilBTRotulo, &msg_l, &msg_a );	
		
	y += normalBT.fundoRet.altura + ( 2 * espacamento );		
	
	strcpy( dificilBT.texto.rotulo, dificilBTRotulo );	

	dificilBT.texto.textoRet.x = x + espBT_H;
	dificilBT.texto.textoRet.y = y + espBT_V;
	dificilBT.texto.textoRet.largura = msg_l;
	dificilBT.texto.textoRet.altura  = msg_a;
	dificilBT.fundoRet.x = x;
	dificilBT.fundoRet.y = y;
	dificilBT.fundoRet.largura = larguraFundoTexto;
	dificilBT.fundoRet.altura = ( 2 * espBT_V ) + msg_a;
	
	y += dificilBT.fundoRet.altura + espacamento;		
	
	menuRet.largura = ( 2 * espacamento ) + larguraFundoTexto;
	menuRet.altura = y;
			
	int tela_l, tela_a;	
	gui->carregaTelaDIM( &tela_l, &tela_a );	
	
	menuRet.x = ( tela_l - menuRet.largura ) / 2;
	menuRet.y = 200;		
}

void AberturaGrafico::finaliza() {
	SDL_FreeSurface( aberturaIMG );
}

void AberturaGrafico::sobreNivel( int nivel ) {
	facilBT.texto.cor = corTexto;
	normalBT.texto.cor = corTexto;
	dificilBT.texto.cor = corTexto;
	
	facilBT.corFundo = corFundo;
	normalBT.corFundo = corFundo;
	dificilBT.corFundo = corFundo;
	
	switch( nivel ) {
		case Jogo::NIVEL_FACIL:
			facilBT.texto.cor = corTextoBTSobre;
			facilBT.corFundo = corFundoBTSobre;
			break;
		case Jogo::NIVEL_NORMAL:			
			normalBT.texto.cor = corTextoBTSobre;
			normalBT.corFundo = corFundoBTSobre;
			break;
		case Jogo::NIVEL_DIFICIL:			
			dificilBT.texto.cor = corTextoBTSobre;
			dificilBT.corFundo = corFundoBTSobre;
			break;		
	}				
}

void AberturaGrafico::desenha( SDL_Renderer* pintor ) {		
	SDL_SetRenderDrawColor( pintor, 0, 0, 0, SDL_ALPHA_OPAQUE );
	SDL_RenderClear( pintor );
		
	if ( aberturaIMG != NULL ) {			
		int l, a;	
		gui->carregaTelaDIM( &l, &a );
	
		SDL_Rect ret;
		
	 	ret.x = ( l - aberturaIMG->w ) / 2;
	 	ret.y = ( a - aberturaIMG->h ) / 2;
	 	ret.w = aberturaIMG->w;
	 	ret.h = aberturaIMG->h;
						
		SDL_Texture* tx = SDL_CreateTextureFromSurface( pintor, aberturaIMG );
		SDL_RenderCopy( pintor, tx, NULL, &ret );
		SDL_DestroyTexture( tx );
	}	
	
	this->desenhaMenu( pintor );
	
	SDL_RenderPresent( pintor );

}

void AberturaGrafico::desenhaMenu( SDL_Renderer* pintor ) {			
	this->desenhaTexto( pintor, opcoesTextoRet );	
	
	this->desenhaBTFundo( pintor, facilBT );
	this->desenhaBTFundo( pintor, normalBT );
	this->desenhaBTFundo( pintor, dificilBT );
	
	this->desenhaTexto( pintor, facilBT.texto );
	this->desenhaTexto( pintor, normalBT.texto );
	this->desenhaTexto( pintor, dificilBT.texto );			
}

void AberturaGrafico::desenhaTexto( SDL_Renderer* pintor, AberturaTexto at ) {
	TTF_Font* fonte = gui->getMensagemFonte();			

	char* rotulo = at.rotulo;
	SDL_Color texto_cor = at.cor;

	SDL_Rect texto_ret;	
	texto_ret.x = menuRet.x + at.textoRet.x;
	texto_ret.y = menuRet.y + at.textoRet.y;
	texto_ret.w = at.textoRet.largura;
	texto_ret.h = at.textoRet.altura;

	SDL_Surface* texto_sf = TTF_RenderText_Solid( fonte, rotulo, texto_cor );
	SDL_Texture* tx = SDL_CreateTextureFromSurface( pintor, texto_sf );
	SDL_RenderCopy( pintor, tx, NULL, &texto_ret );
	SDL_FreeSurface( texto_sf );
	SDL_DestroyTexture( tx );
}

void AberturaGrafico::desenhaBTFundo( SDL_Renderer* pintor, AberturaBT bt ) {							
	SDL_Rect fundo_ret;	
	fundo_ret.x = menuRet.x + bt.fundoRet.x;
	fundo_ret.y = menuRet.y + bt.fundoRet.y;
	fundo_ret.w = bt.fundoRet.largura;
	fundo_ret.h = bt.fundoRet.altura;
	
	SDL_Color fc = bt.corFundo;
		
	SDL_SetRenderDrawColor( pintor, fc.r, fc.g, fc.b, SDL_ALPHA_OPAQUE );
	SDL_RenderFillRect( pintor, &fundo_ret );
	
	SDL_SetRenderDrawColor( pintor, 255, 255, 255, SDL_ALPHA_OPAQUE );
	SDL_RenderDrawRect( pintor, &fundo_ret );	
}

bool AberturaGrafico::isMouseEmFacilBT( int mouseX, int mouseY ) {
	return this->isMouseEmBT( facilBT.fundoRet, mouseX, mouseY );	
}

bool AberturaGrafico::isMouseEmNormalBT( int mouseX, int mouseY ) {
	return this->isMouseEmBT( normalBT.fundoRet, mouseX, mouseY );	
}

bool AberturaGrafico::isMouseEmDificilBT( int mouseX, int mouseY ) {
	return this->isMouseEmBT( dificilBT.fundoRet, mouseX, mouseY );	
}

bool AberturaGrafico::isMouseEmBT( AberturaRet btFundoRet, int mouseX, int mouseY )	{
	int x1 = menuRet.x + btFundoRet.x;
	int y1 = menuRet.y + btFundoRet.y;
	int x2 = menuRet.x + btFundoRet.x + btFundoRet.largura;
	int y2 = menuRet.y + btFundoRet.y + btFundoRet.altura;
	
	return ( mouseX >= x1 && mouseX <= x2 && mouseY >= y1 && mouseY <= y2 );	
}


