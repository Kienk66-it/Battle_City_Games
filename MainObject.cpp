#include "MainObject.h"

MainObject::MainObject() : lastShotTime(0) {
    MainTexture = nullptr;
    Tank_Level = 1;
    this->Object_Speed = Object_Speed;
    //this->Set_Sound(Tank_Shooting_Sound);
}

MainObject::~MainObject() {
    if (MainTexture) {
        SDL_DestroyTexture(MainTexture);
        MainTexture = nullptr;
    }
}

void MainObject::HandleInputAction(SDL_Event Events, SDL_Renderer* renderer) {
    if (Events.type == SDL_KEYDOWN) {
        switch (Events.key.keysym.sym) {
            case SDLK_w:
                doc = -this->Object_Speed;
                direction = 270;
                break;
            case SDLK_s:
                doc = this->Object_Speed;
                direction = 90;
                break;
            case SDLK_a:
                ngang = -this->Object_Speed;
                direction = 180;
                break;
            case SDLK_d:
                ngang = this->Object_Speed;
                direction = 0;
                break;
            case SDLK_p:
                Shoot(renderer);
                break;
            default:
                break;
        }
    } else if (Events.type == SDL_KEYUP) {
        switch (Events.key.keysym.sym) {
            case SDLK_w:
            case SDLK_s:
                doc = 0;
                break;
            case SDLK_a:
            case SDLK_d:
                ngang = 0;
                break;
            default:
                break;
        }
    }
}

void MainObject::Shoot(SDL_Renderer* renderer) {
    Uint32 current_time = SDL_GetTicks();
    if (current_time - lastShotTime >= 600) {
        Bullet* bl = new Bullet(x + 15, y + 15, 10, 10, this->direction, bullet_speed * 2, renderer);
        bullets.push_back(bl);
        lastShotTime = current_time;
    }
    // Âm thanh bắn
    if (this->Tank_Shooting_Sound != nullptr) Mix_PlayChannel(-1, this->Tank_Shooting_Sound, 0);
}

void MainObject::ShowBullets(SDL_Renderer* renderer) {
    for (auto* bullet : bullets) {
        bullet->Show(renderer);
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

void MainObject::Move(SDL_Renderer* renderer) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastMoveTime > 5) {
        // Boundary checks
        prev_x = x;
        prev_y = y;

        if (x > SCREEN_WIDTH - 40 - 150) x = SCREEN_WIDTH - 40 - 150;
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (y > SCREEN_HEIGHT - Object_Hei) y = SCREEN_HEIGHT - Object_Hei;

        int new_x = x + ngang;
        int new_y = y + doc;
        SDL_Rect newRect = { new_x, new_y, Object_Wid, Object_Hei };

        bool collision = false;
        for (int i = 0; i < MAP_SIZE; ++i) {
            for (int j = 0; j < MAP_SIZE; ++j) {
                if (Maps[i][j] != 0) {
                    SDL_Rect tileRect = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                    if (CheckCollision(newRect, tileRect) && (Maps[i][j] == 1 || Maps[i][j] == 2 || Maps[i][j] == 3)) {
                        collision = true;
                        break;
                    }
                }
            }
            if (collision) break;
        }

        if (!collision) {
            x = new_x;
            y = new_y;
        }

        lastMoveTime = currentTime;
    }

    // Update and check bullets
    for (auto* bullet : bullets) {
        bullet->Move();
        SDL_Rect bulletRect = { bullet->getX(), bullet->getY(), BULLET_SIZE, BULLET_SIZE };
        for (int i = 0; i < MAP_SIZE; ++i) {
            for (int j = 0; j < MAP_SIZE; ++j) {
                if (Maps[i][j] == 1 || Maps[i][j] >= 5 || Maps[i][j] == 2) {
                    SDL_Rect tileRect = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                    if (CheckCollision(bulletRect, tileRect)) {
                        if (this->Collision_Sound != nullptr) Mix_PlayChannel(-1, this->Collision_Sound, 0);
                        if (Maps[i][j] != 2) {
                            bullet->setDirection(-1); // Mark for deletion
                            Maps[i][j] = 0;
                        } else {
                            bullet->setDirection(-1); // Mark for deletion
                        }
                        ShowExplode(renderer, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE + 15, TILE_SIZE + 15);
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

	// Check if immortality period has ended
    if (immortal && currentTime - immortalStartTime >= IMMORTAL_DURATION) {
        immortal = false;
    }
}

void MainObject::RevertMove() {
    this->x = prev_x;
    this->y = prev_y;
}

void MainObject::GetHit(SDL_Renderer* renderer) {
    this->health--;
    if (this->health > 0) {
        ResetPosition();
    } else {
        // Handle game over logic here, if needed
    }
}

void MainObject::ResetPosition() {
    x = 200;
    y = SCREEN_HEIGHT - 40;
    ngang = 0;
    doc = 0;
}

void MainObject::updateTank(string file_path, SDL_Renderer* renderer) {
    // = IMG_LoadTexture(renderer, file_path.c_str());
    /*if (MainTexture == nullptr) {
        std::cout << "Failed to load texture: " << file_path << std::endl;
    }*/
    renderTexture(MainTexture, renderer, this->x, this->y, this->Object_Wid, this->Object_Hei);
    //SDL_RenderPresent(renderer);
}

void MainObject::SetTankLevel(int tanklevel) {
    Tank_Level = tanklevel;
}

int MainObject::GetTankLevel() const {
    return Tank_Level;
}

void MainObject::LoadTexture(SDL_Renderer* renderer) {
    // Construct the file path based on tank level
    std::string file_path = "images/My_Tank_" + std::to_string(Tank_Level) + ".png";
    if (MainTexture) {
        SDL_DestroyTexture(MainTexture);
        MainTexture = nullptr;
    }
    MainTexture = IMG_LoadTexture(renderer, file_path.c_str());
    if (!MainTexture) {
        std::cerr << "Failed to load texture for tank level " << Tank_Level << ": " << SDL_GetError() << std::endl;
    }
}

void MainObject::SetImmortal(bool state, Uint32 start_time) {
    immortal = state;
    if (state) {
        immortalStartTime = start_time;
    }
}