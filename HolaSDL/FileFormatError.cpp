#include "FileFormatError.h"

FileFormatError::FileFormatError(string name, string m) : PacmanError(m){
	fileName = name;
}

string FileFormatError::what(){
	return "Se ha producido un error de formato al cargar el archivo " + fileName + ".\nError: " + PacmanError::what();
}
