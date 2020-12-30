#include "PacmanError.h"

PacmanError::PacmanError(string m) : logic_error(m) { 

}

string PacmanError::what() {
	return logic_error::what();
}
