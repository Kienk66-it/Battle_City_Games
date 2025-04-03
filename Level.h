#ifndef LEVEL_H
#define LEVEL_H

#include "Header.h"
#include "Init.h"
#include "CommonFunction.h"
#include "GameDetails.h"

class Level : public GameDetails{
public:
    Level(SDL_Renderer* renderer, int x, int y, int fontSize);
    //~Level();

    void AddVal(int lives, SDL_Renderer* renderer);
    string writeString();
    //void Render(SDL_Renderer* renderer);
    //void UpdateTexture(SDL_Renderer* renderer);

};
#endif // LEVEL_H
