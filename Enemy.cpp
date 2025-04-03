#include "Enemy.h"

Enemy::Enemy(){}

Enemy::~Enemy(){
    if (!this->Object_Texture) {
        SDL_DestroyTexture(this->Object_Texture);
        this->Object_Texture = nullptr;
    }
}

void Enemy::setScoreEnemy(int score_){
	this->scoreEnemy = score_;
}

int Enemy::getScoreEnemy(){
	return this->scoreEnemy;
}

void Enemy::Init(SDL_Renderer* renderer, string file_path) {
    this->x = x;  // Set initial x coordinate
    this->y = y;  // Set initial y coordinate
    this->Object_Wid = Object_Wid; // Width of the tank
    this->Object_Hei = Object_Hei; // Height of the tank

    this->bullet_speed = 1;

    //this->direction = rand() % 360; // Initial random direction
    this->Object_Speed = Object_Speed; // Movement speed
    this->Object_Rect.x = x;
    this->Object_Rect.y = y;
    this->Object_Rect.w = Object_Wid;
    this->Object_Rect.h = Object_Hei;

    SDL_Surface* EnemySurface = IMG_Load(file_path.c_str());
    if (EnemySurface == nullptr) {
        std::cerr << "Failed to load enemy image: " << IMG_GetError() << std::endl;
    }
    this->Object_Texture = SDL_CreateTextureFromSurface(renderer, EnemySurface);
    if (!this->Object_Texture) {
        std::cerr << "Failed to create texture from surface: " << IMG_GetError() << std::endl;
    }
    SDL_FreeSurface(EnemySurface);
}

void Enemy::Move(){
    Uint32 currentTime = SDL_GetTicks();
    Uint32 currentMoveTime = SDL_GetTicks();
    if(currentMoveTime - lastMoveTime > 15){
		this->prev_x = this->x;
        this->prev_y = this->y;
        if (currentTime - lastDirectionChangeTime >= directionChangeCooldown) {
            int direction = rand() % 4; // Thay đổi hướng ngẫu nhiên
			int percentage = rand() % 101;
			if(percentage >= 50) this->direction = 90;
			else{
				if(direction == 0) this->direction = 0;
				else if(direction == 1) this->direction = 90;
				else if(direction == 2) this->direction = 180;
				else this->direction = 270;
			}
            lastDirectionChangeTime = currentTime;
        }

        
        // Kiểm tra va chạm với rìa màn hình
        if (x > SCREEN_WIDTH - Object_Wid - 150){
            x = SCREEN_WIDTH - Object_Wid - 150;
            int direction = rand() % 4; // Thay đổi hướng ngẫu nhiên
			int percentage = rand() % 101;
			if(percentage >= 50) this->direction = 90;
			else{
				if(direction == 0) this->direction = 0;
				else if(direction == 1) this->direction = 90;
				else if(direction == 2) this->direction = 180;
				else this->direction = 0;
			}
        }
        if (x < 0){
            x = 0;
            int direction = rand() % 4; // Thay đổi hướng ngẫu nhiên
			int percentage = rand() % 101;
			if(percentage >= 50) this->direction = 90;
			else{
				if(direction == 0) this->direction = 0;
				else if(direction == 1) this->direction = 90;
				else if(direction == 2) this->direction = 180;
				else this->direction = 0;
			}
        }
        if (y < 0){
            y = 0;
            int direction = rand() % 4; // Thay đổi hướng ngẫu nhiên
			int percentage = rand() % 101;
			if(percentage >= 50) this->direction = 90;
			else{
				if(direction == 0) this->direction = 0;
				else if(direction == 1) this->direction = 90;
				else if(direction == 2) this->direction = 180;
				else this->direction = 0;
			}
        }
        if (y > SCREEN_HEIGHT - Object_Wid){
            y = SCREEN_HEIGHT -  Object_Wid;
            int direction = rand() % 4; // Thay đổi hướng ngẫu nhiên
			int percentage = rand() % 101;
			if(percentage >= 50) this->direction = 90;
			else{
				if(direction == 0) this->direction = 0;
				else if(direction == 1) this->direction = 90;
				else if(direction == 2) this->direction = 180;
				else this->direction = 270;
			}
        }
        int newX = x + this->Object_Speed * cos(this->direction * M_PI / 180);
        int newY = y + this->Object_Speed * sin(this->direction * M_PI / 180);

        SDL_Rect EnemyRect = {newX, newY, this->Object_Wid, this->Object_Hei};

        bool collision = false;
        for(int i = 0; i < MAP_SIZE; i++){
            for(int j = 0; j < MAP_SIZE; j++){
                if(Maps[i][j] == 1 || Maps[i][j] == 2 ||  Maps[i][j] == 3 ||  Maps[i][j] == 5){
                    SDL_Rect tileRect = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                    if(CheckCollision(EnemyRect, tileRect)){
                        int direction = rand() % 4; // Thay đổi hướng ngẫu nhiên
                        if(direction == 0) this->direction = 0;
                        else if(direction == 1) this->direction = 90;
                        else if(direction == 2) this->direction = 180;
                        else this->direction = 270;
                        collision = true;
                        break;
                    }
                }
            }
            if(collision) break;
        }

        if (!collision) {
            x = newX;
            y = newY;
        }
        lastMoveTime = currentMoveTime;
    }
    // Update and check bullets

    for (auto *bullet : bullets) {
        bullet->Move();
        SDL_Rect bulletRect = { bullet->getX(), bullet->getY(), BULLET_SIZE, BULLET_SIZE };
        for (int i = 0; i < MAP_SIZE; ++i) {
            for (int j = 0; j < MAP_SIZE; ++j) {
                if (Maps[i][j] == 1 || Maps[i][j] >= 5 || Maps[i][j] == 2) {
                    SDL_Rect tileRect = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                    if (CheckCollision(bulletRect, tileRect)) {
                        if (Maps[i][j] != 2) {
                            bullet->setDirection(-1); // Mark for deletion
                            Maps[i][j] = 0;
                        } else {
                            bullet->setDirection(-1); // Mark for deletion
                        }
                    }
                }
            }
        }
    }

    // Remove bullets that are off-screen or have direction -1
    auto newEnd = std::remove_if(bullets.begin(), bullets.end(), [](Bullet* bullet) {
        bool remove = bullet->Is_Off_Screen() || bullet->getDirection() == -1;
        if (remove) {
            delete bullet;
        }
        return remove;
    });
    bullets.erase(newEnd, bullets.end());
}

void Enemy::Shoot(SDL_Renderer* renderer) {
    Uint32 current_time = SDL_GetTicks();
    if (current_time - lastShotTime >= this->shotCooldown) {
        Bullet* bl = new Bullet(x + 15, y + 15, 10, 10, this->direction, this->bullet_speed, renderer);
        bullets.push_back(bl);
        lastShotTime = current_time;
    }
}

void Enemy::takeDamage(int damage){
	this->health -= damage;
    if (health < 0) health = 0; // Đảm bảo mạng không âm
}