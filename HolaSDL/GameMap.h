#pragma once
#include <array>
#include "Texture.h"
#include "GameObject.h"
class Game;

enum MapCell{ Wall, Food, Vitamins, Empty};

class GameMap : public GameObject
{
	friend Game;

private:	
	int rows;
	int cols;
	MapCell** cells;
	array <Texture*, 3> mapTextures;
public:
	GameMap(int, int, Texture*, Texture*,Texture* ,Point2D , int , int , Game* );
	~GameMap();
	bool intersectsWall(const SDL_Rect& );
	void saveToFile(ofstream&);
	virtual void render()const;
	void SetCell(int, int, int);
	virtual void update(); //jona y havi unidos en el infierno----------------------------- (en Game salia error en la constructora de GameMap)
};

