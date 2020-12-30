#pragma once
#include "PacmanError.h"
#include <string>

class SDLError : public PacmanError
{
private:
	string sdlE;
public :
	SDLError(string, string);
	virtual string what();

};

