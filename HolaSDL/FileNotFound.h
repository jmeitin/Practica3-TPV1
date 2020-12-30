#pragma once
#include "PacmanError.h"

class FileNotFound : public PacmanError
{
private:
	string fileName;

public:
	FileNotFound(string, string);
	virtual string what();
};

