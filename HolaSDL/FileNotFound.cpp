#include "FileNotFound.h"

FileNotFound::FileNotFound(string name, string m) : PacmanError(m){
	fileName = name;
}

string FileNotFound::what(){
	 return "No se ha podido abrir " + fileName+". \nError: " + PacmanError::what();
}
