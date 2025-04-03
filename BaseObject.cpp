#include "BaseObject.h"

Object::Object() : x(0), y(0), ngang(0), doc(0), direction(0), Object_Speed(0), Object_Wid(0), Object_Hei(0), 
		Object_Surface(nullptr), Object_Texture(nullptr), lastMoveTime(0), 
		ExplodeFrames(4), startTimeExplode(0), durationExplode(500), health(0) {};

Object::~Object() {
    if(!Object_Texture){
        SDL_DestroyTexture(Object_Texture); // Giải phóng texture khi object bị hủy
	    Object_Texture = nullptr;
    }
	if(!ExplodeTexture){
		SDL_DestroyTexture(ExplodeTexture);
		ExplodeTexture = nullptr;
	}
}

// Getters
int Object::GetX() const {
    return x;
}

int Object::GetY() const {
    return y;
}

int Object::GetDir() const{
	return direction;
}

int Object::GetObjectWidth() const {
    return Object_Wid;
}

int Object::GetObjectHeight() const {
    return Object_Hei;
}

int Object::GetExplodeFrames(){
	return ExplodeFrames;
}

int Object::GetHealth(){
	return health;
}

int Object::GetObjectSpeed(){
	return Object_Speed;
}

string Object::GetTankTypes(){
    return Tank_Types;
}



// Setters
void Object::SetX(int x) {
    this->x = x;
}

void Object::SetY(int y) {
    this->y = y;
}

void Object::SetDir(int dir){
	this->direction = dir;
}

void Object::SetObjectWidth(int width) {
    Object_Wid = width;
}

void Object::SetObjectHeight(int height) {
    Object_Hei = height;
}

void Object::SetHealth(int health_){
	health = health_;
}

void Object::SetTankTypes(string tanktype){
    Tank_Types = tanktype;
}

void Object::SetObjectSpeed(int speed_){
	Object_Speed = speed_;
}

// Getter and Setter methods
int Object::getBulletSpeed() const {
    return bullet_speed;
}

void Object::setBulletSpeed(int speed) {
    bullet_speed = speed;
}



SDL_Rect Object::GetRect() const {
    return Object_Rect;
}

void Object::Get_Parameters(int x_, int y_, int wid, int hei, int speed){
    x = x_;
    y = y_;
    Object_Wid = wid;
    Object_Hei = hei;
    Object_Speed = speed;
	lastMoveTime = SDL_GetTicks();
   
    Object_Rect.x = x_;
    Object_Rect.y = y_;
    Object_Rect.w = wid;
    Object_Rect.h = hei;
}

 bool Object::loadImage(string file_path, SDL_Renderer* renderer){
	 Object_Surface = IMG_Load(file_path.c_str());
    if (Object_Surface == nullptr) {
        std::cout << "Fail to load object image" << std::endl;
        return false;
    }
	//cout << "Load OK" << endl;
    Object_Texture = SDL_CreateTextureFromSurface(renderer, Object_Surface);
    SDL_FreeSurface(Object_Surface); // Giải phóng surface sau khi tạo texture
    return Object_Texture != nullptr;
}

void Object::ShowObject(SDL_Renderer* renderer){
    Object_Rect.x = x;
    Object_Rect.y = y;
    Object_Rect.w = Object_Wid;
    Object_Rect.h = Object_Hei;
    SDL_RenderCopyEx(renderer, Object_Texture, NULL, &Object_Rect, direction, NULL, SDL_FLIP_NONE);
}


bool Object::CheckCollision(SDL_Rect a, SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

void Object::ShowExplode(SDL_Renderer* renderer, int x_, int y_, int wid_, int hei_){
	Uint32 currentTime = SDL_GetTicks();

	ExplodeTexture = IMG_LoadTexture(renderer, "images/explosion.png");
	if(!ExplodeTexture) cout << "fail to load explosion png" << endl;
	for(int i = 0; i < ExplodeFrames; i++){
		//if(currentTime - startTimeExplode < durationExplode){
			renderTexture(ExplodeTexture, renderer, x_, y_, wid_, hei_);
			SDL_Delay(3);
			
	//	}
		//else startTimeExplode = currentTime;
	}
}

void Object::Set_Sound(Mix_Chunk* sound) {
    Tank_Shooting_Sound = sound;
}

void Object::Set_Collision_Sound(Mix_Chunk* sound){
    Collision_Sound = sound;
}