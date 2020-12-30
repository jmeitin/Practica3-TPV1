#pragma once

#include <string>
#include <istream>
#include <fstream>
#include <iostream>
#include <list>
#include <iterator>
#include <exception>
#include "SDLError.h"
#include "FileNotFound.h"
#include "FileFormatError.h"
#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "Texture.h"
#include "GameMap.h"
#include "PacMan.h"
#include "Ghost.h"
#include "SmartGhost.h"
#include <cmath>

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

const int velMov = 1;
const uint WIN_WIDTH = 800; //FUERA CLASE?
const uint WIN_HEIGHT = 600;

class Game
{
private:	
	string mapasGuardados = ".\\MapasGuardados\\level";
	string mapaASecas = "..\\Mapas-20201107\\level";
	string imagenesGuardadas = "..\\imagenes_20201107\\";


	enum loadType {Pacman = 0, ghost, Map, Smart};
	enum State { Playing, LevelPassed, GameOver, Win }; 
	State level = Playing;
	int nivel = 1;
	int numNivelesTot = 5;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	int cellWidth, cellHeight;

	int vidas = 30;
	int comida; //comida restante
	


	int rows, cols;
	
	array<Texture*, NUM_TEXTURES> textures;
	
	GameMap* map;
	PacMan* pacman;
	list<Ghost*> ghostsList;
	list<GameObject*> objects; // lista polimorfica
	list<list<GameObject*>::iterator> objectsToErase; // lista polimorfica

public:
	Game();
	~Game(); //destructora
	void run();
	bool  TryMove(SDL_Rect ,  Vector2D , Point2D&);
	Texture* getTexture(TextureName);
    int CheckCell(Point2D);
	int CheckCell(Point2D,Vector2D);
	void checkGhost(Point2D,int);
	int getCellWidth();
	int getCellHeight();	
	void MinusFood(Point2D); 
	void Vitamin(Point2D);
	void loadNextLevel();
	Point2D mapCoordsToSDLPoint(Point2D);
	Point2D SDLPointToMapCoords(Point2D);
	void saveGame(string);
	void loadSavedGame(string);	
	bool GhostsCollide(Ghost*);
	void FollowPlayer(Point2D , Point2D&,int& );
	void EraseGhost(list<GameObject*>::iterator&);
	void storeGhost(Ghost*);
	bool PacmanCanEat();
	
private:
	void MenuInicial();
	void MenuGuardar();
	void DirGhost();
	void loadLevelFile();	
	void handleEvents();
	void update();
	void render();
	void loadFile(ifstream&);
	
};

