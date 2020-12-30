#pragma once
#include "PacmanError.h"

class FileFormatError : public PacmanError
{
	//Debes detectar al menos dos tipos de errores de formato.
protected:
	string fileName;

public:
	FileFormatError(string, string);
	virtual string what();
};

