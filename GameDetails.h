#ifndef GAME_DETAILS_H
#define GAME_DETAILS_H

#include "Header.h"
#include "Init.h"
#include "CommonFunction.h"

class GameDetails
{
protected:
	int val;
	string valText;

public:
	GameDetails(SDL_Renderer* renderer, int x, int y, int fontSize);
	~GameDetails();
	SDL_Texture* texture;
	SDL_Rect rect;
	TTF_Font* font;

	int getVal();
	void setVal(int val_);

	virtual string writeString();
	void Render(SDL_Renderer* renderer);
	void UpdateTexture(SDL_Renderer* renderer);
	virtual void AddVal(int val, SDL_Renderer* renderer);


};



#endif // GAME_DETAILS_H

