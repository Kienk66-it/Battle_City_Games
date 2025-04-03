#ifndef ENEMY_H
#define ENEMY_H

#include "MainObject.h"
#include "BaseObject.h"
#include "Bullet.h"

// Forward declaration of the Bullet class to avoid circular dependency
//class Bullet;

class Enemy : public MainObject {
private:
    
    
    Uint32 lastShotTime;
    Uint32 lastDirectionChangeTime;

    static const Uint32 shotCooldown = 800;
    static const Uint32 directionChangeCooldown = 4000;

    int hits_require;
    int hits_shooted;

	int scoreEnemy;
public:
	void setScoreEnemy(int score_);
	int getScoreEnemy();
    //SDL_Texture* EnemyTexture;
    //vector<Bullet*> bullets;
    Enemy();
    ~Enemy();

    //vector<Bullet*> bullets; // Assume Bullet is a class for bullets

    void Init(SDL_Renderer* renderer, string file_path);
 
    void Move();

    void Shoot(SDL_Renderer* renderer);

	void takeDamage(int damage);

};

#endif // ENEMY_H
