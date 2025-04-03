#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include "Header.h"
#include "Map.h"

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int width, int height);

bool isPointInRect(int x, int y, SDL_Rect rect);

void showMenu(SDL_Renderer* renderer, SDL_Texture* menu_background,  SDL_Texture* newgameButton, SDL_Texture* exitButton, 
			  SDL_Texture* instructionButton, SDL_Texture* instructionMenu, bool &quit, bool &startGame);

void ReturnToMainMenu(SDL_Renderer* renderer, SDL_Texture* menuBackground, SDL_Texture* newGameButtonTexture,
                      SDL_Texture* exitButtonTexture, SDL_Texture* instructionButtonTexture, 
                      SDL_Texture* instructionMenuTexture, bool& quit, bool& startGame);

bool CheckGameOver();

bool Check_Collision(SDL_Rect a, SDL_Rect b);

#endif