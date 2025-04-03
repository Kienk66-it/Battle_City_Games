#include "Level.h"
#include <sstream>
#include <iostream>

Level::Level(SDL_Renderer* renderer, int x, int y, int fontSize)
    : GameDetails(renderer, x, y, fontSize){ // Call the base class constructor
}



void Level::AddVal(int lvl, SDL_Renderer* renderer) {
    val = lvl;
    UpdateTexture(renderer);
}

string Level::writeString() {
    std::ostringstream ss;
    ss << "Level: " << val;  // Include the prefix "Level:"
    valText = ss.str();
    return valText;
}


