#pragma once
#include <stdexcept>
#include <string>

using namespace std;

class PacmanError : public logic_error
{

public:
	PacmanError(string) ;
	
	virtual string what();
};

