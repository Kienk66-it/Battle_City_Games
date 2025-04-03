#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#pragma once

#include "BaseObject.h"
#include "Bullet.h"

class MainObject : public Object {
private:
	Uint32 lastShotTime;
	Uint32 currentTime;
    static const Uint32 shotCooldown = 500; // 500 milliseconds cooldown
	

    //int lives; // Number of lives
    int startX; // Starting X position
    int startY; // Starting Y position

	void LoadTexture(SDL_Renderer* renderer);

	bool immortal;
    Uint32 immortalStartTime;
    static const int IMMORTAL_DURATION = 5000;

public:
	int Tank_Level;
    SDL_Texture* MainTexture;
	
	vector<Bullet*> bullets;
	int prev_x;
    int prev_y;
    MainObject();
    ~MainObject();

    void HandleInputAction(SDL_Event Events, SDL_Renderer* renderer);
    virtual void Move(SDL_Renderer* renderer);

	virtual void Shoot(SDL_Renderer* renderer);
	void ShowBullets(SDL_Renderer* renderer);
	void RevertMove();

	void ResetPosition();
    void GetHit(SDL_Renderer* renderer);
    //int GetLives() const { return lives; }
    void updateTank(string file_path, SDL_Renderer* renderer);

	int GetTankLevel() const;
	void SetTankLevel(int tanklevel);

	void SetImmortal(bool state, Uint32 start_time);

};

#endif // MAIN_OBJECT_H
