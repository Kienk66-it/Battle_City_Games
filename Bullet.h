#ifndef BULLET_H
#define BULLET_H
#include "Header.h"
#include "CommonFunction.h"
#include "Init.h"
#include "BaseObject.h"

#define BULLET_SIZE 10

class Bullet : public Object{
private:
	
public:
	Bullet(int x_, int y_, int bullet_wid_, int bullet_hei_, int angle_, int bullet_speed_, SDL_Renderer* renderer);

	SDL_Texture* Bullet_Texture;
	SDL_Surface* Bullet_Surface;

	~Bullet();

	void Move();
	void Show(SDL_Renderer* renderer);
	bool Is_Off_Screen() const; 

	// Getter and Setter methods
    int getBulletSpeed() const;
    void setBulletSpeed(int speed);

    int getX() const;
    void setX(int x_);

    int getY() const;
    void setY(int y_);

    int getDirection() const;
    void setDirection(int angle_);
};

#endif 
