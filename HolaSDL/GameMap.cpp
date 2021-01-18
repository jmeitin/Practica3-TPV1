#include "GameMap.h"
#include "Game.h" //TIENE QUE IR EN EL CPP PARA QUE NO DE ERROR


GameMap::GameMap (int row, int col, Texture* wall, Texture* food, Texture* vitamins, Point2D p, int w, int h, Game* g, PlayState* p) : GameObject (p,w,h,g){ //cels*
	rows = row;
	cols = col;
	cells = new MapCell*[rows];

	for (int i = 0; i < rows; ++i) 
		cells[i] = new MapCell[cols];

	mapTextures[Wall] = wall;
	mapTextures[Food] = food;
	mapTextures[Vitamins] = vitamins;
	game = p;
}

GameMap::~GameMap() { 
	for (int i = 0; i < rows; ++i) delete[] cells[i];
	delete[] cells;
}

void GameMap::update() { //flipada de jona y javi--------------------------------------------------------------------------------------------------

}

//COMPRUEBA SI UN SDL Rect choca con WALL
bool GameMap::intersectsWall(const SDL_Rect& rect) {
	Point2D topLeftCoords = game->SDLPointToMapCoords(Vector2D(rect.x, rect.y));
	
	Point2D bottomRightCoords = game->SDLPointToMapCoords(Vector2D((rect.x + game->getCellWidth())-1, (rect.y + game->getCellHeight())-1));

	int x = topLeftCoords.getX();
	int y = topLeftCoords.getY();

	//compruebo si hay alguna casilla entre mi esquina super izq y mi inf der que este dentro de una casilla que sea wall
	bool intersects = false; //fil = y, col = x
	while (y <= bottomRightCoords.getY() && !intersects) { //filas
		while (x <= bottomRightCoords.getX() && !intersects) {//columnas
			if (cells[y][x] == Wall) intersects = true;
			else x++; 
		}		
		y++;
		x = topLeftCoords.getX();		
	}

	return intersects;
}

void GameMap::render()const {
	int cellWidth = game->getCellWidth();
	int cellHeight = game->getCellHeight();
	SDL_Rect destRect;
	destRect.w = cellWidth;
	destRect.h = cellHeight;

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			destRect.y = (r * cellHeight);

			if (cells[r][c] != Empty) {
				destRect.x = (c * cellWidth); 
				mapTextures[cells[r][c]]->render(destRect);
			}	
		}		
	}	
}


void GameMap::saveToFile(ofstream& file) {
	file << 2 << '\n'; //IDENTIFICADOR
	file << rows <<" " << cols<< '\n';

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {			
			switch (cells[r][c]) {
			case Wall:
				file << 1;
				break;
			case Food:
				file << 2;
				break;
			case Vitamins:
				file << 3;
				break;
			default:
				file << 0; //vacio, ghost o pacman	
				break;
			}
			file << " ";
		}
		file << "\n";
	}
}


//enum MapCell { Empty, Wall, Food, Vitamins };
// 0 = vacio, 1 = muro, 2 = comida, 3 = vitamina, 5-6-7-8 = fantasmas y 9 = Pacman. L
void GameMap:: SetCell (int val, int r, int c){ //INCIALIZA LA CELDA CUANDO SE LEE EL MAPA
	switch (val) {
	case 1:
		cells[r][c] = Wall;
		break;
	case 2:
		cells[r][c] = Food;
		break;
	case 3:
		cells[r][c] = Vitamins;
		break;
	default:
		cells[r][c] = Empty; //vacio, ghost o pacman
		break;
	}
}


