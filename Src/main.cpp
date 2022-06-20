
#include "sistema.h"

#include <SDL2/SDL.h>

int main(int argc, char** argv) {		
	Sistema* sistema = new Sistema();
	sistema->exec();

	return 0;
}
