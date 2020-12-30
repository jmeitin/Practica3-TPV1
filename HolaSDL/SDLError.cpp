#include "SDLError.h"

SDLError::SDLError(string n, string m) : PacmanError(m){
	sdlE = n;
}

string SDLError::what(){	
	return "Se produjo un error SDL :"+sdlE+ "\n Error: " + PacmanError::what();
}