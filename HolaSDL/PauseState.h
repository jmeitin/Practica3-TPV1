#pragma once

#include "GameState.h"
#include "MenuButton.h"
#include "MainMenuState.h"

class Game;

class PauseState : public  GameState
{
	//FACILITA EL INDEXAR EL ARRAY------------------------------------------------------------------------
	enum TextureName {
		WallText, CharactersText, FoodText, BurguerText,
		ExitText, MainText, PlayText, RestartText, ResumeText, SaveText
	};

private:	
	Point2D pos; //HAY QUE DARLE UN VALOR -------------------------------------------------------------------
	

	//resume, save, back to menu
	TextureName resumeText = ResumeText;
	TextureName saveText = SaveText;
	TextureName mainText = MainText;

public:
	PauseState(Game*);
	static void resume(Game*);
	static void save(Game*);
	static void backToMenu(Game*);
};
