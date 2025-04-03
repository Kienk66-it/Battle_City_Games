#ifndef ENEMIES_REMAINING_H
#define ENEMIES_REMAINING_H

#include "Header.h"
#include "Init.h"
#include "CommonFunction.h"
#include "GameDetails.h"

class Enemies_Remaining : public GameDetails {
public:

    Enemies_Remaining(SDL_Renderer* renderer, int x, int y, int fontSize);


    void AddEnemies_Remaining(int left, SDL_Renderer* renderer);
    string writeString();

};

#endif // ENEMIES_REMAINING_H
