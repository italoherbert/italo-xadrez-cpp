
#include "algoritmo/algoritmo_gerenciador.h"
#include "animacao/animacao.h"
#include "audio/jogo_audio.h"
#include "controlador/abertura_grafico_controlador.h"
#include "controlador/GUI_Controlador.h"
#include "controlador/jogo_grafico_controlador.h"
#include "grafico/abertura_grafico.h"
#include "grafico/jogo_grafico.h"
#include "gui/abertura_grafico_listener.h"
#include "gui/GUI.h"
#include "gui/GUI_Listener.h"
#include "gui/jogo_grafico_listener.h"
#include "logica/jogo.h"
#include "tela_driver_adapter.h"

int main(int argc, char** argv) {		
	GUI* gui = new GUI();
	
	TelaDriverAdapter* tdAdapter = new TelaDriverAdapter( gui );
		
	Jogo* jogo = new Jogo( tdAdapter );
	
	AlgoritmoGerenciador* algGer = new AlgoritmoGerenciador( jogo );
	Animacao* animacao = new Animacao( jogo );
	
	JogoAudio* jA = new JogoAudio();

	AberturaGrafico* aG = new AberturaGrafico( gui );
	JogoGrafico* jG = new JogoGrafico( jogo, gui );
	
	GUI_Controlador* guiCtrl = new GUI_Controlador( jogo, gui, aG, jG, jA );
	AberturaGraficoControlador* aberturaGCtrl = new AberturaGraficoControlador( jogo, gui, aG, jA );
	JogoGraficoControlador* jogoGCtrl = new JogoGraficoControlador( jogo, algGer, animacao, gui, jG, jA );
		
	gui->setGUIListener( guiCtrl );
	gui->setAberturaGraficoListener( aberturaGCtrl );
	gui->setJogoGraficoListener( jogoGCtrl );
	
	gui->setAberturaGrafico( aG );		
	gui->setJogoGrafico( jG );

	gui->executa( "Jogo de Xadrez", Consts::JANELA_LARGURA, Consts::JANELA_ALTURA ); 
	
	return 0;
}
