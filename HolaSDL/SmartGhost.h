#pragma once
#include "Ghost.h"
#include <vector>
#include "PlayState.h"

class Game;

class SmartGhost : public Ghost
{
	const uint32_t TiempoChild = 3000;
	const int tDeath = 6000;
	const int tCuarentena = 1000;

protected:
	int mov1;
	const int TIEMPO1 = 300;
	enum State { Child = 0, Adult, Quarantine, Dead };
	State state;
	SDL_Rect rectAdulto;
	int tVivo, tQuar;

public:
	SmartGhost(Point2D, int, int, Game*, Vector2D, Point2D, PlayState*);
	SmartGhost(ifstream&, Game*, PlayState*);
	~SmartGhost();
	void handleState();
	virtual void render() const;
	virtual void update();
	virtual void saveToFile(ofstream&);
	bool canBreed();
	void FollowNotFollow();
	void Move(const vector<Vector2D>&, const vector<Vector2D>&);
};

