#ifndef LIVESREMAINING_H
#define LIVESREMAINING_H

#include "Header.h"
#include "Init.h"
#include "CommonFunction.h"
#include "GameDetails.h"

class LivesRemaining : public GameDetails {
public:
    LivesRemaining(SDL_Renderer* renderer, int x, int y, int fontSize);

    void AddVal(int lives, SDL_Renderer* renderer);
    string writeString();
};
#endif // LIVESREMAINING_H
