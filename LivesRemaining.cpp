#include "LivesRemaining.h"

LivesRemaining::LivesRemaining(SDL_Renderer* renderer, int x, int y, int fontSize)
	: GameDetails(renderer, x, y, fontSize) { // Call the base class constructor
}

void LivesRemaining::AddVal(int lives, SDL_Renderer* renderer) {
	val = lives;
	UpdateTexture(renderer);
}

string LivesRemaining::writeString() {
	std::ostringstream ss;
	ss << "Lives: " << val;  // Include the prefix "Lives:"
	valText = ss.str();
	return valText;
}