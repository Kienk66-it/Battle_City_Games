#include "PowerUps.h"

PowerUp::PowerUp(SDL_Renderer* renderer, int x, int y, const std::string& file_path)
    : active(true), spawnTime(SDL_GetTicks()) {
    SDL_Surface* surface = IMG_Load(file_path.c_str()); // Load your power-up image
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    rect.x = x;
    rect.y = y;
    rect.w = 30; // Set appropriate width
    rect.h = 30; // Set appropriate height

	PowerUpTypes = file_path;
}

PowerUp::~PowerUp() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

std::string PowerUp::GetPowerUpTypes() const {
    return PowerUpTypes;
}

void PowerUp::SetPowerUpTypes(const std::string& s) {
    PowerUpTypes = s;
}

void PowerUp::Render(SDL_Renderer* renderer) {
    if (active) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
}

void PowerUp::Update(Uint32 deltaTime) {
    if (active && SDL_GetTicks() - spawnTime > POWERUP_DURATION) {
        active = false;
    }
}

bool PowerUp::IsActive() const {
    return active;
}

SDL_Rect PowerUp::GetRect() const {
    return rect;
}