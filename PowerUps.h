#ifndef POWERUPS_H
#define POWERUPS_H

#include "Header.h"
#include "Init.h"
#include "Map.h"
#include "BaseObject.h"
#include "CommonFunction.h"
#include <string>

class PowerUp {
public:
    PowerUp(SDL_Renderer* renderer, int x, int y, const std::string& file_path);
    ~PowerUp();

    void Render(SDL_Renderer* renderer);
    void Update(Uint32 deltaTime);
    bool IsActive() const;
    SDL_Rect GetRect() const;

    std::string GetPowerUpTypes() const;
    void SetPowerUpTypes(const std::string& s);

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    bool active;
    Uint32 spawnTime;
    static const Uint32 POWERUP_DURATION = 5000; // 5 seconds

    std::string PowerUpTypes;
};

#endif // POWERUPS_H
