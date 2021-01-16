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
#include "Texture.h"
#include "GameMap.h"
#include "PacMan.h"
#include "Ghost.h"
#include "SmartGhost.h"
#include "GameStateMachine.h"
#include <cmath> //raiz cuadrada

class PlayState
{
private:
	string mapasGuardados = ".\\MapasGuardados\\level";
	string mapaASecas = "..\\Mapas-20201107\\level";

	enum loadType { Pacman = 0, ghost, Map, Smart };
	enum State { Playing, LevelPassed, GameOver, Win };
	State level = Playing;

	int nivel = 1;
	int numNivelesTot = 5;
	int vidas = 30;
	int comida; //comida restante
	const int velMov = 1;
	int rows, cols;
	int cellWidth, cellHeight;

	GameMap* map;
	PacMan* pacman;
	list<Ghost*> ghostsList;
	list<GameObject*> objects; // lista polimorfica
	list<list<GameObject*>::iterator> objectsToErase; // lista polimorfica

public:
	PlayState();
	~PlayState();
	void loadNextLevel();
	void saveGame(string);
	void loadSavedGame(string);

	void renderObjects();
	void run();
	bool  TryMove(SDL_Rect, Vector2D, Point2D&);
	int CheckCell(Point2D);
	int CheckCell(Point2D, Vector2D);
	void checkGhost(Point2D, int);
	int getCellWidth();
	int getCellHeight();
	void MinusFood(Point2D);
	void Vitamin(Point2D);	
	Point2D mapCoordsToSDLPoint(Point2D);
	Point2D SDLPointToMapCoords(Point2D);
	bool GhostsCollide(Ghost*);
	void FollowPlayer(Point2D, Point2D&, int&);
	void EraseGhost(list<GameObject*>::iterator&);
	void storeGhost(Ghost*);
	bool PacmanCanEat();


private:
	void DirGhost();
	void loadLevelFile();
	void loadFile(ifstream&);
	void handleEvents();
	void update();
};

