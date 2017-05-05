#include "General\Game.h"



int main(int argc, char* argv[]) {
	Game game = Game();

	game.beginLoop();

	//Should never reach here, if we do, something has gone terribly wrong. Upon termination, the beginLoop function will close GLFW and exit the program itself.
	return EXIT_FAILURE;

}