
#include "sistema.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

int exec(void*) {
	Sistema* sistema = new Sistema();
	sistema->exec();

	return 0;
}

int main(int argc, char** argv) {		
	SDL_Thread* thread = SDL_CreateThread( exec, "Thread Jogo", (void*)NULL );
	if ( thread == NULL ) {
		exec( NULL );
	} else {
		int threadRetVal = 0;
		SDL_WaitThread( thread, &threadRetVal );
	}

	return 0;
}
