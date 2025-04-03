#include "Map.h"

int Maps[MAP_SIZE + 1][MAP_SIZE + 1];

void readFileToMatrix(string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    string line;
    int row = 0;

    while (std::getline(file, line) && row < MAP_SIZE) {
        for (int col = 0; col < MAP_SIZE && col < line.size(); ++col) {
            Maps[row][col] = line[col] - '0'; // Chuyển từ ký tự sang số nguyên
        }
        ++row;
    }
    file.close();
}

void InitMap(SDL_Renderer* renderer){
	//khoi tao vien gach
	if(!loadImage(renderer, "images/brick.png", BrickTexture)){
		cout << "Fail to load brick image" << endl;
	}
	brick = IMG_Load("images/brick.png");
	BrickTexture = SDL_CreateTextureFromSurface(renderer, brick);

	//khoi tao steel
	if(!loadImage(renderer, "images/steel.png", SteelTexture)){
		cout << "Fail to load steel image" << endl;
	}
	steel = IMG_Load("images/steel.png");
	SteelTexture = SDL_CreateTextureFromSurface(renderer, steel);

    //khoi tao water
	if(!loadImage(renderer, "images/water.png", WaterTexture)){
		cout << "Fail to load water image" << endl;
	}
	water = IMG_Load("images/water.png");
	WaterTexture = SDL_CreateTextureFromSurface(renderer, water);

    //khoi tao grass
	if(!loadImage(renderer, "images/grass.png", GrassTexture)){
		cout << "Fail to load grass image" << endl;
	}
	grass = IMG_Load("images/grass.png");
	GrassTexture = SDL_CreateTextureFromSurface(renderer, grass);

	//khoi tao eagle
	if(!loadImage(renderer, "images/eagle02.png", EagleTexture2)){
		cout << "Fail to load eagle image" << endl;
	}
    if(!loadImage(renderer, "images/eagle03.png", EagleTexture3)){
		cout << "Fail to load eagle image" << endl;
	}
    if(!loadImage(renderer, "images/eagle04.png", EagleTexture4)){
		cout << "Fail to load eagle image" << endl;
	}
    if(!loadImage(renderer, "images/eagle05.png", EagleTexture5)){
		cout << "Fail to load eagle image" << endl;
	}
	eagle2 = IMG_Load("images/eagle02.png");
	EagleTexture2 = SDL_CreateTextureFromSurface(renderer, eagle2);

    eagle3 = IMG_Load("images/eagle03.png");
	EagleTexture3 = SDL_CreateTextureFromSurface(renderer, eagle3);

    eagle4 = IMG_Load("images/eagle04.png");
	EagleTexture4 = SDL_CreateTextureFromSurface(renderer, eagle4);

    eagle5 = IMG_Load("images/eagle05.png");
	EagleTexture5 = SDL_CreateTextureFromSurface(renderer, eagle5);
}

void showMap(SDL_Renderer* renderer){
	for(int i = 0; i < MAP_SIZE; i++){
		for(int j = 0; j < MAP_SIZE; j++){
			//cout << Maps[i][j] << " ";
			switch(Maps[i][j]){
			case 1:
				renderTexture(BrickTexture, renderer, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
				break;
			case 2:
				renderTexture(SteelTexture, renderer, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
				break;
            case 3:
                renderTexture(WaterTexture, renderer, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                break;
            case 4:
                renderTexture(GrassTexture, renderer, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                break;
			case 5:
				renderTexture(EagleTexture2, renderer, j * TILE_SIZE , i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
				break;
            case 6:
				renderTexture(EagleTexture3, renderer, j * TILE_SIZE , i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
				break;
            case 7:
				renderTexture(EagleTexture4, renderer, j * TILE_SIZE , i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
				break;
            case 8:
				renderTexture(EagleTexture5, renderer, j * TILE_SIZE , i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
				break;

			default:
				break;
			}
		}
		//cout << endl;
	}
	//clear mem
	SDL_FreeSurface(brick);
	SDL_FreeSurface(steel);
	SDL_FreeSurface(eagle2);
    SDL_FreeSurface(eagle3);
    SDL_FreeSurface(eagle4);
    SDL_FreeSurface(eagle5);
    SDL_FreeSurface(water);
    SDL_FreeSurface(grass);
	brick = nullptr;
	steel = nullptr;
	eagle2 = nullptr;
    eagle3 = nullptr;
    eagle4 = nullptr;
    eagle5 = nullptr;
    grass = nullptr;
    water = nullptr;
}
