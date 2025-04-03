#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H
#pragma once

#include "Header.h"
#include "Init.h"
#include "CommonFunction.h"
#include "Map.h"

class Object{
protected:
    // Tọa độ
    int x, y;
    // Kích thước object image
    int Object_Wid, Object_Hei;
    // Di chuyển
    int ngang, doc;
    // Góc xoay
    int direction;
    // Tốc độ di chuyển

    //toc do dan
    int bullet_speed;

    int Object_Speed;
    // Surface và Texture của object
    int ExplodeFrames;
	//số mạng của tank
	int health;

	Uint32 lastMoveTime;

    string Tank_Types;


public:
	Uint32 startTimeExplode;
    int durationExplode; 

	SDL_Texture* ExplodeTexture;

	SDL_Surface* Object_Surface;
    SDL_Texture* Object_Texture;

    Mix_Chunk* Tank_Shooting_Sound;
    Mix_Chunk* Collision_Sound;
    // Rectangle của object
    SDL_Rect Object_Rect;

    SDL_Rect GetRect() const;

    // Getters
    int GetX() const;
    int GetY() const;
	int GetDir() const;
    int GetObjectWidth() const;
    int GetObjectHeight() const;
	int GetExplodeFrames();
	int GetHealth();
	int GetObjectSpeed();
    string GetTankTypes();
    

    // Setters
    void SetX(int x);
    void SetY(int y);
	void SetDir(int dir);
    void SetObjectWidth(int width);
    void SetObjectHeight(int height);
	void SetHealth(int health_);
	void SetObjectSpeed(int speed_);
    void SetTankTypes(string tanktype);
    

    // Constructor khởi tạo các giá trị ban đầu
	Object();
	// Destructor để giải phóng tài nguyên
    ~Object();

    // Phương thức để lấy thông số cho object
    void Get_Parameters(int x_, int y_, int wid, int hei, int speed);

    // Phương thức để tải ảnh và tạo texture
    bool loadImage(string file_path, SDL_Renderer* renderer);

    // Phương thức để hiển thị object
    void ShowObject(SDL_Renderer* renderer);

    bool CheckCollision(SDL_Rect a, SDL_Rect b);

	void ShowExplode(SDL_Renderer* renderer, int x_, int y_, int wid_, int hei_);



    // Getter and Setter methods
    int getBulletSpeed() const;
    void setBulletSpeed(int speed);

    void Set_Sound(Mix_Chunk* sound);

    void Set_Collision_Sound(Mix_Chunk* sound);
};

#endif // BASE_OBJECT_H