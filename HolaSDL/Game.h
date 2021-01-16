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
#include "Texture.h"
#include "GameStateMachine.h"

using uint = unsigned int;

//DEFINICION DE LAS CONSTANTES

struct TextureAtribs {
	string filename;
	int numRows;
	int numCols;
};

static const int NUM_TEXTURES = 4; //UNO PARA LOS MUROS, PACMAN Y
const TextureAtribs TEXTURES_ATRIBS[NUM_TEXTURES] =
				{ {"wall.png",1,1},	 { "characters.png", 4, 14},		{"food.png", 1, 1},   {"burguer.png",1,1 } };
enum TextureName { WallText,		    CharactersText,					 FoodText,              BurguerText}; //FACILITA EL INDEXAR EL ARRAY

const uint WIN_WIDTH = 800; //FUERA CLASE?
const uint WIN_HEIGHT = 600;

class Game
{
private:		
	string imagenesGuardadas = "..\\imagenes_20201107\\";

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	array<Texture*, NUM_TEXTURES> textures; //include SmartGhost
	
	GameStateMachine* gameStateMachine;

public:
	Game();
	~Game(); //destructora
	void run();
	Texture* getTexture(TextureName);
	void MenuGuardar();
	GameStateMachine* getStateMachine(); //app
	
private:
	void MenuInicial();
	void render();
};

