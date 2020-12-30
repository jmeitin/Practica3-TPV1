#include "Game.h"

using namespace std;

Game::Game() {	
	//inicializacion sdl
	SDL_Init(SDL_INIT_EVERYTHING); //INICIALIZA SDL
	rows = cols = 0;
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN); //CREAR VENTANA

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //CREAR Renderer

	if (window == nullptr || renderer == nullptr)
		throw SDLError(SDL_GetError(),"No se ha podido crear window o renderer en Game()");// string("Error cargando window/renderer en SDL");

	for (int i = 0; i < NUM_TEXTURES; ++i) //CREACION TEXTURAS
	{
		textures[i] = new Texture(renderer, imagenesGuardadas + TEXTURES_ATRIBS[i].filename,
			TEXTURES_ATRIBS[i].numRows, TEXTURES_ATRIBS[i].numCols);
		if (textures[i] == nullptr) throw FileNotFound(TEXTURES_ATRIBS[i].filename,"No se ha podido encontrar/cargar la textura");
	}
	MenuInicial(); //ELEGIR PARTIDA NUEVA/GUARDADA
}

void Game::MenuInicial() {
	char c;	
	cout << "Introduzca j si quiere JUGAR y c si quiere CARGAR una partida GUARDADA: \n";
	cin >> c;

	if (c == 'j') {
		loadLevelFile(); //LEE UN ARCHIVO PARA INCIALIZAR LOS ATRIBUTOS
		DirGhost(); //le doy a los fantasmas una direccion inicial
	}

	else if (c == 'c') {
		string codigo;

		cout << "Introduzca el codigo numerico del nivel: \n";
		cin >> codigo;

		loadSavedGame(codigo);
		DirGhost(); //le doy a los fantasmas una direccion inicial
	}

	else cout << "Opción no valida";
}

//elegir nivel guardado
void Game::MenuGuardar() {
	char c;
	cout << "Introduzca g si quiere guardar la partida: ";
	cin >> c;

	if (c == 'g') {
		string codigo;
		cout << "Introduzca el codigo numerico del nivel: \n";
		cin >> codigo;
		saveGame(codigo);
	}
	else cout << "Que tenga un buen día.";
}

Game::~Game() {
	
	for (Texture* t : textures) delete t;
	for (GameObject* g : objects) delete g;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//le da direcciones iniciales a los ghost
void Game::DirGhost() {	
		for (Ghost* g : ghostsList) g->getDirIndice();			
}

void Game::EraseGhost(list<GameObject*>::iterator& it) {
	Ghost* g = static_cast<Ghost*>(*it);
	ghostsList.remove(g); //Remove elements with specific value 
	
	objectsToErase.push_back(it);
}

void Game::storeGhost (Ghost* g){
	//insert devuelve un iterador apuntando al nodo que acabas de insertar
	auto it = objects.insert(objects.end(), g);   //sustituye a objects.push_back(g); 
	g->SetItList(it);
	ghostsList.push_back(g);
}




//CARGA UN NUEVO NIVEL DESDE 0
void Game::loadLevelFile() { 
	level = Playing;

	ifstream file;
	string nivelS;
	nivelS = "0" + to_string(nivel);
	
	file.open(mapaASecas + nivelS + ".dat"); //esto esta bien? -----------------------------------------------------------------
	if (!file.is_open()) throw FileNotFound("level"+nivelS , "No se ha podido encontrar/cargar la textura");

	loadFile(file); //LEEO EL ARCHIVO ==> INCIALIZO

	file.close();
}

// CARGA UN NIVEL ==> A PARTIR DE UN FLUJO DE ENTRADA
void Game::loadFile(ifstream& file) {	
	short int valor;
	int fantasmas = 0;
	file >> rows >> cols;	
	cellWidth = WIN_WIDTH / cols;
	cellHeight = WIN_HEIGHT / rows;
	map = new GameMap(rows, cols, textures[WallText], textures[FoodText], textures[BurguerText],Point2D(0,0), cellWidth * cols,cellHeight * rows ,this); //CREAS GAMEMAP
	objects.push_back(map);
	
	//leo el mapa y creo los objetos
	for (int r = 0; r < rows; ++r)
		for (int c = 0; c < cols; ++c) {			
			file >> valor;
			if (cin.fail()) throw FileFormatError("level" + nivel, "Hay valores en el archivo que no son enteros");
			if (valor < 0 || valor > 9)  throw FileFormatError("level" + nivel, "Hay una casilla con un valor que no es un numero comprendido en el intervalo [0,9]"); 
            
			else if (valor >= 4) {  // 5-6-7-8 = fantasmas y 9 = Pacman 				
				map->cells[r][c] = Empty;

				if (valor == 4) {
					SmartGhost* g = new SmartGhost(mapCoordsToSDLPoint(Point2D(c,r)), cellWidth, cellHeight, this, Vector2D(0, 0), Vector2D(0, 8));
					storeGhost(g); 
				}
				else if (valor == 9) {		
					pacman = new PacMan(mapCoordsToSDLPoint(Point2D(c, r)), cellWidth, cellHeight, this, Vector2D(0, 0), Vector2D(0, 10)); //o POINT O VECTOR	
					auto it = objects.insert(objects.end(), pacman);
					pacman->SetItList(it); 
				}
				else {					
					Ghost* g = new Ghost(mapCoordsToSDLPoint(Point2D(c, r)), cellWidth, cellHeight, this, Vector2D(0, 0), Vector2D(0,fantasmas));
					fantasmas += 2; // avanza 2 posiciones en la sprite sheet
					storeGhost(g);
				}			
			}	

            // CUANDO ES UNA PARTIDA GUARDADA ==> no llega aqui info sobre la pos del pacman y los ghost ==> no entra en el if
			//solo entra en el else if si es COMIDA, y luego da valor a map.SetCell.
			else if (valor == 2) ++comida;
			map->SetCell(valor, r, c); //INCIALIZA LA CELDA
		}


}

//CARGA PARTIDA GUARDADA
void Game::loadSavedGame(string codigo) {
	ifstream file;
	string archivo = mapasGuardados + codigo + ".txt";
	file.open(archivo);

	if (file.is_open()) {
		int val;
		file >> vidas >> nivel;
		cout << nivel;

		file >> val;
		while (!file.eof()) {
			switch (val) {				
			   case Pacman: {
				   pacman = new PacMan(file, this);
				   auto it = objects.insert(objects.end(), pacman);
				   pacman->SetItList(it);
			   }
			   break;
			   case ghost: {
				   Ghost* g = new Ghost(file, this);
				   storeGhost(g);
			   }
			   break;
			   case Map:
				  loadFile(file);
				   break;
			   case Smart:
				   char c;
				   file >> c;
				   SmartGhost* g = new SmartGhost(file, this);
				   storeGhost(g);
				break;
			   }
			file >> val;
			if (cin.fail()) throw FileFormatError("level" + nivel, "Hay valores en el archivo que no son enteros");
		}

		file.close();
	}

	else { //ERROR RECUPERABLE
		cout << "codigo incorrecto  \n";
		file.close();
		MenuInicial();
	}
}

void Game::saveGame(string codigo) {	
	ofstream file(mapasGuardados + codigo + ".txt"); //creas nuevo archivo
	
	if (file.is_open()) {
		file << vidas <<" "<< nivel << '\n';
		for (GameObject* o : objects) {
			GameCharacter* c = dynamic_cast<GameCharacter*>(o);
			if (c != nullptr) c->saveToFile(file);
		}
		map->saveToFile(file);
	}
	file.close();
}

void Game::run() { //BUCLE PRINCIPAL DEL JUEGO
	int frameTime = 0, startTime = 0, FRAME_RATE = 10;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//negro

	startTime = SDL_GetTicks();//nos devuelve el tiempo actual en milisegundos 
	
	while (level == Playing || level == LevelPassed) {		
		handleEvents();				
		frameTime = SDL_GetTicks() - startTime;
						
		if (frameTime >= FRAME_RATE || level == GameOver){ //Solo se actualiza cada tanto tiempo
			update();
			startTime = SDL_GetTicks();
		}		
		render();		
	}	
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && level == Playing) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_q:
				level = GameOver;
				break;
			default:
				pacman->handleEvent(event);
				break;
			}
		}		
	}
}


void Game::update() { 	
	if (level == LevelPassed) { //HE GANADO
		if (nivel == numNivelesTot) level = Win; // GANE EL ULTIMO NIVEL			
		else loadNextLevel();  //PASO DE NIVEL
	}
	else if (level == GameOver) {
		MenuGuardar();
	}
	
	else{ 	// ESTOY JUGANDO
	    for (auto o : objects) {
		    GameCharacter* g = dynamic_cast<GameCharacter*>(o);
		    if(g != nullptr) g->update();
	    }		

	    for (auto it : objectsToErase) { 
			delete (*it);
			GameObject* go = static_cast<GameObject*>(*it);
			objects.remove(go);			  
        }	

		objectsToErase.clear();
	}
}

//PASO DE NIVEL ==> actualiza estado del juego borra fantasmas pacman gamemap y los vuelve a cargar
void Game::loadNextLevel() {	
	for (auto o : objects) delete o;
	ghostsList.clear(); //la lista no queda con basura
	objects.clear();

	nivel++; //paso al siguiente nivel
	
	loadLevelFile(); //CARGA EL SIGUIENTE NIVEL
}

void Game::render() {
	SDL_RenderClear(renderer); //MUESTRA EN EL RENDER EL COLOR ESPECIFICADO POR EL DRAWCOLOR		
	for (auto o : objects) o->render();
	
	SDL_RenderPresent(renderer); //MUESTRA EL RENDERIZADO	
}


//conversiones
Point2D Game::mapCoordsToSDLPoint(Point2D coords) {
	//multiplicacion y suma 
	return  Point2D((coords.getX() * cellWidth), (coords.getY() * cellHeight));
}

Point2D Game::SDLPointToMapCoords(Point2D coords) {
	//division y resta 
	return Point2D((coords.getX() / cellWidth ), (coords.getY() / cellHeight ));
}


int Game::getCellWidth() {
	return cellWidth;
}

int Game::getCellHeight() {
	return cellHeight;
}





//DEVUELVE UN PUNTERO A UNA TEXTURA
Texture* Game::getTexture(TextureName text) {
	return textures[text];
}


//MIRA SI EL MOVIMIENTO ES POSIBLE ==> EN ESE CASO, ACTUALIZA NEWPOS Y DEVUELVE TRUE				    
bool Game::TryMove(SDL_Rect rect,  Vector2D dir, Point2D& newPos) {
	SDL_Rect mapRect = map->getDestRect();	
	newPos = Point2D(rect.x, rect.y) + dir ;
	
	if (dir.getX() > 0 && (newPos.getX() + rect.w) >= mapRect.w) newPos.setX(0);//sales por la derecha, apareces por la iz
	else if(dir.getX() < 0 && (newPos.getX()/*-rect.w*/ ) <= 0) newPos.setX(mapRect.w);//sales por la izquierda, apareces por la dr.
	else if (dir.getY() < 0 && (newPos.getY() /*- rect.h*/) <= 0) newPos.setY(mapRect.h-cellHeight); //sales por abajo, apareces por arriba
	else if (dir.getY() > 0 && (newPos.getY() + rect.h) >= mapRect.h ) newPos.setY(0); //sales por arriba, apareces por abajo

	SDL_Rect rec{newPos.getX(), newPos.getY(), rect.w, rect.h};

	return(!map->intersectsWall(rec));
}

//DEVUELVE LO QUE HAY EN LA DA A LA QUE SE MUEVE
int Game::CheckCell(Point2D pos) {
	Point2D posCell = SDLPointToMapCoords(pos);
	
	return (map->cells[posCell.getY()][posCell.getX()]);
}

//me devuelve la sig casilla en coor de mapa
int Game::CheckCell(Point2D pos,Vector2D dir) {
	Point2D posCell = SDLPointToMapCoords(pos);

	posCell.setX((posCell.getX() + dir.getX() + cols) % cols);
	posCell.setY((posCell.getY() + dir.getY() + rows) % rows);

	return (map->cells[posCell.getY()][posCell.getX()]);
}

//PACMAN COMPRUEBA SI COLISIONA CON UN GHOST
void Game::checkGhost(Point2D pos, int canEat) {
	Point2D cell = SDLPointToMapCoords(pos);
	std::list<Ghost*>::iterator it = ghostsList.begin();
	while (it != ghostsList.end() && (SDLPointToMapCoords((*it)->getPos())) != cell) ++it;
	
	if (it != ghostsList.end() ) {
		SmartGhost* s = dynamic_cast<SmartGhost*>(*it);
		if (s == nullptr ||( s != nullptr && s->canBreed())) {
			if (canEat == 1) (*it)->die();
			else {
				--vidas;
				std::cout << vidas;
				if (vidas <= 0) {
					level = GameOver;
					std::cout << "Has perdido";
				}
				else pacman->reStart();
			}
		}
	}
}




//COMPRUEBA COLISIONES ENTRE GHOSTS
bool Game::GhostsCollide(Ghost* ghost) {
	std::list<Ghost*>::iterator it = ghostsList.begin();
	bool intersec = false;

	//MIENTRAS NO LLEGUE AL FINAL Y NO HAYA INTERSECCION
	while (it != ghostsList.end() && !intersec) {
		SDL_Rect rectG = (ghost->getDestRect());
		SDL_Rect rectT = ((*it)->getDestRect());
		//SI SE CORTAN, Y NO SON EL MISMO
		if (SDL_HasIntersection(&rectG, &rectT) && (*it) != ghost) intersec = true;
		else ++it;
	}

	
	if (it != ghostsList.end()) { // LO ENCONTRO
		SmartGhost* g = dynamic_cast<SmartGhost*>((*it));

		if (g != nullptr && g->canBreed()) { //ES SMARTGHOST Y LE TOCA DUPLICARSE
			SmartGhost* gh = new SmartGhost( ghost->getPos(), cellWidth, cellHeight, this, Vector2D(0, 0), Vector2D(0, 8));
			ghostsList.push_back(gh);
			objects.push_back(gh);
			return true;
		}
		
		else { //si es un ghost
			Ghost* gh = new Ghost(ghost->getPos(), cellWidth, cellHeight, this, Vector2D(0, 0), Vector2D(0, 5));
			ghostsList.push_back(gh);
			objects.push_back(gh);
			return true;
		}
	}
	return false;
}

bool Game::PacmanCanEat() {
	return pacman->CanEat();
}

//metodo para que el smartGhost siga a player
void Game::FollowPlayer(Point2D pos,Point2D& dir, int& distance) {
	SDL_Rect pacRect = pacman->getDestRect();
	int x = pacman->getDestRect().x - pos.getX();
	int y = pacman->getDestRect().y - pos.getY();
	distance = sqrt(pow(x,2)+pow(y,2));
	dir = Point2D(x, y);
}

void Game::MinusFood(Point2D point) {
	comida--;
	
	map->SetCell(0, point.getY(), point.getX());

	if (comida == 0) level = LevelPassed;
}

void Game::Vitamin(Point2D point) {	
	map->SetCell(0, point.getY(), point.getX());
}

