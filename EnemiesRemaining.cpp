#include "EnemiesRemaining.h"
#include <sstream>
#include <iostream>

Enemies_Remaining::Enemies_Remaining(SDL_Renderer* renderer, int x, int y, int fontSize)
    : GameDetails(renderer, x, y, fontSize) {
}


void Enemies_Remaining::AddEnemies_Remaining(int left, SDL_Renderer* renderer) {
    val = left;
    UpdateTexture(renderer);
}

string Enemies_Remaining::writeString() {
	std::ostringstream ss;
	ss << val << " left";  
	valText = ss.str();
	return valText;
}

