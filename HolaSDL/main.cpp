
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Game.h"
#include "PacmanError.h"

using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	try {
		Game game;
		game.run();
	}
	catch (PacmanError& e) {
		cout << e.what();
	}


	return 0;
}