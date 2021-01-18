#pragma once


#include <string>
#include <istream> //entrada
#include <fstream> //salida
#include <iostream> //leer
#include <exception>
#include "SDLError.h"
#include "FileNotFound.h"
#include "SDL.h" // Windows
#include "SDL_image.h" // Windows

#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "Texture.h"
#include "SmartGhost.h"


using uint = unsigned int;

//DEFINICION DE LAS CONSTANTES
static const int NUM_TEXTURES = 10; //NUMERO DE IMAGENES QUE HAY QUE CARGAR

struct TextureAtribs {
	string filename;
	int numRows;
	int numCols;
};

const TextureAtribs TEXTURES_ATRIBS[NUM_TEXTURES] = {
	 {"wall.png",1,1},	 { "characters.png", 4, 14},  {"food.png", 1, 1},   {"burguer.png",1,1 }, 	 {"exit.png",1,3 },
     {"main.png",1,3 } , {"play.png",1,3 } ,       {"restart.png",1,3 },    {"resume.png",1,3 },      {"save.png",1,3} 
};

//FACILITA EL INDEXAR EL ARRAY
enum TextureName { 
		WallText,		    CharactersText,			    FoodText,              BurguerText,
		ExitText,          MainText,          PlayText,            RestartText,         ResumeText,         SaveText				
}; 

const uint WIN_WIDTH = 800; //FUERA CLASE?
const uint WIN_HEIGHT = 600;

class Game
{
private:		
	string imagenesGuardadas = "..\\imagenes_20201107\\";

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exitt = false;
	
	array<Texture*, NUM_TEXTURES> textures; //include SmartGhost
	
	GameStateMachine* gameStateMachine;

public:
	Game();
	~Game(); //destructora
	void run();
	Texture* getTexture(TextureName);
	void MenuGuardar();
	GameStateMachine* getStateMachine(); //app
	GameState* getCurrentState();
	
private:
	void MenuInicial();
	void render();
};

