#ifndef MAP_H
#define MAP_H

#include "Header.h"
#include "Init.h"
#include "CommonFunction.h"

const int TILE_SIZE = 25;
const int MAP_SIZE = SCREEN_HEIGHT/ TILE_SIZE;

static SDL_Texture* BrickTexture = nullptr;
static SDL_Texture* SteelTexture = nullptr;
static SDL_Texture* WaterTexture = nullptr;
static SDL_Texture* GrassTexture = nullptr;
static SDL_Texture* EagleTexture2 = nullptr;
static SDL_Texture* EagleTexture3 = nullptr;
static SDL_Texture* EagleTexture4 = nullptr;
static SDL_Texture* EagleTexture5 = nullptr;

static SDL_Surface* brick = nullptr;
static SDL_Surface* steel = nullptr;
static SDL_Surface* water = nullptr;
static SDL_Surface* grass = nullptr;
static SDL_Surface* eagle2 = nullptr;
static SDL_Surface* eagle3 = nullptr;
static SDL_Surface* eagle4 = nullptr;
static SDL_Surface* eagle5 = nullptr;

extern int Maps[MAP_SIZE + 1][MAP_SIZE + 1];

void readFileToMatrix(string& filename);

void InitMap(SDL_Renderer* renderer); 

void showMap(SDL_Renderer* renderer);
#endif // MAP_H