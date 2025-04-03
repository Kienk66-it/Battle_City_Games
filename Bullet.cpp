#include "Bullet.h"
#include <cmath>  // for std::cos and std::sin
#include <iostream>

Bullet::Bullet(int x_, int y_, int bullet_wid_, int bullet_hei_, int angle_, int bullet_speed_, SDL_Renderer* renderer)
{
    this->x = x_; this->y = y_; this->Object_Wid = bullet_wid_; this->Object_Hei = bullet_hei_; this->direction = angle_;
    bullet_speed = bullet_speed_;

    Bullet_Surface = IMG_Load("images/circular_bullet.png");
    if (!Bullet_Surface) {
        std::cerr << "Failed to load bullet surface: " << IMG_GetError() << std::endl;
        return; // Exit if surface creation failed
    }
    Bullet_Texture = SDL_CreateTextureFromSurface(renderer, Bullet_Surface);
    if (!Bullet_Texture) {
        std::cerr << "Failed to load bullet texture: " << IMG_GetError() << std::endl;
    }
    SDL_FreeSurface(Bullet_Surface);  // Free surface after creating texture
}

Bullet::~Bullet() {
    if (Bullet_Texture) {
        SDL_DestroyTexture(Bullet_Texture);
        Bullet_Texture = nullptr;  // Set to nullptr after destruction
    }
}

void Bullet::Move() {
    // Precompute direction in radians to avoid repetitive calculation
    float rad = direction * M_PI / 180.0f;
    x += bullet_speed * cos(rad);
    y += bullet_speed * sin(rad);

    Object_Rect.x = x;
    Object_Rect.y = y;
    Object_Rect.w = Object_Wid;
    Object_Rect.h = Object_Hei;
}

void Bullet::Show(SDL_Renderer* renderer) {
    if (Bullet_Texture) {
        SDL_RenderCopy(renderer, Bullet_Texture, nullptr, &Object_Rect);
    }
}

bool Bullet::Is_Off_Screen() const {
    return (y + Object_Hei < 0 || y > SCREEN_HEIGHT || x + Object_Wid < 0 || x > SCREEN_WIDTH - 150 - 10);
}

// Getter and Setter methods
int Bullet::getBulletSpeed() const {
    return bullet_speed;
}

void Bullet::setBulletSpeed(int speed) {
    bullet_speed = speed;
}

int Bullet::getX() const {
    return x;
}

void Bullet::setX(int x_) {
    x = x_;
}

int Bullet::getY() const {
    return y;
}

void Bullet::setY(int y_) {
    y = y_;
}

int Bullet::getDirection() const {
    return direction;
}

void Bullet::setDirection(int angle_) {
    direction = angle_;
}