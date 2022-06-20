
#ifndef SISTEMA_H
#define SISTEMA_H

#include "jogo_driver_adapter.h"

#include "logica/jogo.h"

#include "gui/GUI.h"

#include "grafico/abertura_grafico.h"
#include "grafico/jogo_grafico.h"

#include "audio/jogo_audio.h"
#include "animacao/animacao.h"

#include "algoritmo/algoritmo_gerenciador.h"

#include "controlador/GUI_Controlador.h"
#include "controlador/abertura_grafico_controlador.h"
#include "controlador/jogo_grafico_controlador.h"

class GUI_Controlador;
class AberturaGraficoControlador;
class JogoGraficoControlador;

class Sistema {

	private:
		Jogo* jogo;
		JogoDriverAdapter* jdrv;
		GUI* gui;

		JogoAudio* audio;

		AberturaGrafico* aberturaGrafico;
		JogoGrafico* jogoGrafico;

		AlgoritmoGerenciador* algoritmoGerenciador;
		Animacao* animacao;

		GUI_Controlador* guiControlador;
		AberturaGraficoControlador* aberturaGraficoControlador;
		JogoGraficoControlador* jogoGraficoControlador;

	public:
		Sistema();
		~Sistema();

		void inicia();
		void finaliza();

		void exec();

		Jogo* getJogo();
		JogoDriverAdapter* getJogoDriver();

		GUI* getGUI();
		AberturaGrafico* getAberturaGrafico();
		JogoGrafico* getJogoGrafico();

		JogoAudio* getJogoAudio();
		Animacao* getAnimacao();

		AlgoritmoGerenciador* getAlgoritmoGerenciador();

};

#endif




