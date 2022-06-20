
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
#include "jogo_driver_adapter.h"
#include "logica/jogo.h"

int main(int argc, char** argv) {		
	Sistema* sistema = new Sistema;
	sistema->exec();
	
	return 0;
}
