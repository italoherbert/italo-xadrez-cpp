
#include "GUI_Controlador.h"

#include <cmath>

#include <SDL2/SDL_image.h>

#include <iostream>
using namespace std;

GUI_Controlador::GUI_Controlador( Jogo* jogo, GUI* gui, AberturaGrafico* aG, JogoGrafico* jG, JogoAudio* audio ) {
	this->jogo = jogo;
	this->gui = gui;
	this->jogoGrafico = jG;
	this->aberturaGrafico = aG;
	this->audio = audio;
}

void GUI_Controlador::inicializou() {			
	aberturaGrafico->inicializa();
	jogoGrafico->inicializa();	
	audio->inicializa();
	
	jogo->reinicia();
	audio->reinicia();	
	gui->reinicia();
}

void GUI_Controlador::finalizando() {
	aberturaGrafico->finaliza();
	jogoGrafico->finaliza();	
	audio->finaliza();
}
		
void GUI_Controlador::janelaFechada() {
	
}



