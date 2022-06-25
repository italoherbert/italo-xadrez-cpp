
#include "sistema.h"

#include <SDL2/SDL.h>

#include <windows.h>
#include <process.h>

Sistema * sistema = new Sistema();

void execJogo( void* id ) {
	sistema->execJogo( id );
}

int main(int argc, char** argv) {
	_beginthread( execJogo, 0, (void*)"Thread 0" );

	sistema->execGUI();

	return 0;
}
