#include "Init.h"
#include "CommonFunction.h"
#include "Map.h"
//#include "BaseObject.h"
#include "MainObject.h"
#include "Enemy.h"
#include "ScoreManager.h"
#include "PowerUps.h"
#include "Level.h"
#include "EnemiesRemaining.h"
#include "LivesRemaining.h"

// Initialize ScoreManager with the renderer and desired position and font size
ScoreManager scoreManager(gRenderer, 780, 350, 30);
Level level(gRenderer, 780, 645, 30);
Enemies_Remaining enemiesRemaining(gRenderer, 780, 210, 30);
LivesRemaining livesRemaining(gRenderer, 780, 140, 30);

string EnemyTankTypes[] = {"images/enemyTank1R.png", "images/enemyTank1R_1.png", "images/enemyTank2R.png", "images/enemyTank2R_1.png", 
                        "images/enemyTank3R.png", "images/enemyTank4R_3.png", "images/enemyTank3R_1.png", 
						"images/enemyTank4R_4.png"};

string Maps_array[] = {"maps/map1.txt", "maps/map2.txt", "maps/map3.txt", "maps/map4.txt", "maps/map5.txt", "maps/map6.txt"};

string PowerUps_array[] = {"images/star.png", "images/tank.png", "images/shovel.png", "images/helmet.png", "images/bomb.png", "images/clock.png"};

int currentLevel = 1;
int enemiesDestroyed = 0;
const int enemiesToAdvance = 20; // Number of enemies needed to advance to the next level

int Mark_Postion[SCREEN_WIDTH][SCREEN_WIDTH];

const int FRAME_DELAY = 20;

bool shovelActive = false;
Uint32 shovelStartTime = 0;

int EnemyNum = 5;

void CheckShovelEffect(Uint32& shovelStartTime, bool& shovelActive) {
    if (shovelActive) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - shovelStartTime >= 5000) { // 5 giây
            shovelActive = false;
            Maps[29][13] = 1; Maps[28][13] = 1; Maps[27][13] = 1; Maps[27][13] = 1; Maps[27][14] = 1;
            Maps[27][15] = 1; Maps[27][16] = 1; Maps[28][16] = 1; Maps[29][16] = 1;
        }
    }
}

bool CheckCollision(SDL_Rect a, SDL_Rect b) {
    // Kiểm tra nếu không có sự chồng chéo
    if (a.x + a.w <= b.x || a.x >= b.x + b.w || a.y + a.h <= b.y || a.y >= b.y + b.h) {
        return false;
    }
    return true;
}


bool CheckPowerUpCollision(const MainObject& MyTank, const PowerUp& powerUp) {
    return CheckCollision(MyTank.GetRect(), powerUp.GetRect());
}


void HandlePowerUpCollection(MainObject& player, std::vector<PowerUp>& powerUps, 
                             std::vector<Enemy>& enemyTanks, SDL_Renderer* renderer, Mix_Chunk* &buffs) {
    SDL_Rect playerRect = player.GetRect();
    
    for (auto it = powerUps.begin(); it != powerUps.end(); ) {
        if (CheckCollision(playerRect, it->GetRect())) {
			Mix_PlayChannel(-1, buffs, 0);
        //    if (it->GetType() == 1) { // Type 1 for health increase
			//cout << it->GetPowerUpTypes() << endl;
            if(it->GetPowerUpTypes() == "images/tank.png"){
				player.SetHealth(player.GetHealth() + 1);
				livesRemaining.AddVal(player.GetHealth(), renderer);
			}
            else if(it->GetPowerUpTypes() == "images/star.png"){
                
                player.SetTankLevel(player.GetTankLevel() + 1);
				//cout << "level :" << player.GetTankLevel() << endl;
                if(player.GetTankLevel() == 2){
					player.Object_Texture = IMG_LoadTexture(renderer, "images/My_Tank_2.png");
                    //player.ShowObject(renderer);
					player.setBulletSpeed(3);
                }
                else if(player.GetTankLevel() == 3){
                    player.Object_Texture = IMG_LoadTexture(renderer, "images/My_Tank_3.png");
                    //player.ShowObject(renderer);
					player.setBulletSpeed(3);
                    player.SetObjectSpeed(2);
                }
                else if(player.GetTankLevel() == 4){
                    player.Object_Texture = IMG_LoadTexture(renderer, "images/My_Tank_4.png");
                    //player.ShowObject(renderer);
					player.setBulletSpeed(4);
                    player.SetObjectSpeed(3);
                }
                else if(player.GetTankLevel() == 5){
                    player.Object_Texture = IMG_LoadTexture(renderer, "images/My_Tank_5.png");
					player.setBulletSpeed(4);
                    //player.ShowObject(renderer);
                    player.SetObjectSpeed(2);
                }
            }
			else if(it->GetPowerUpTypes() == "images/helmet.png"){
				player.SetImmortal(true, SDL_GetTicks());
			}
			else if(it->GetPowerUpTypes() == "images/shovel.png"){
				shovelActive = true;
                shovelStartTime = SDL_GetTicks();
				for(int i = 0; i < 1e5; i++){
                Maps[29][13] = 2; Maps[28][13] = 2; Maps[27][13] = 2; Maps[27][13] = 2; Maps[27][14] = 2;
                Maps[27][15] = 2; Maps[27][16] = 2; Maps[28][16] = 2; Maps[29][16] = 2;
				
				}CheckShovelEffect(shovelStartTime, shovelActive);
			}
            //else if (it->GetPowerUpTypes() == "images/clock.png"){
            //    for(auto i = enemyTanks.begin(); i != enemyTanks.end(); ){
            //        i->SetObjectSpeed(0);
            //    }
            //}
            
            // Remove power-up from the vector
            it = powerUps.erase(it);
        } else {
            ++it;
        }
    }
}

void CheckCollisionWithEnemyBullets(MainObject& MyTank, vector<Enemy>& Enemy_array, SDL_Renderer* renderer) {
    SDL_Rect MyTankRect = {MyTank.GetX(), MyTank.GetY(), MyTank.GetObjectWidth(), MyTank.GetObjectHeight()};
    for (auto& enemy : Enemy_array) {
        for (auto* bullet : enemy.bullets) {
            SDL_Rect BulletRect = {bullet->getX(), bullet->getY(), bullet->GetObjectWidth(), bullet->GetObjectHeight()};
            if (Check_Collision(MyTankRect, BulletRect)) {
                MyTank.GetHit(renderer);
				MyTank.setBulletSpeed(1);
                MyTank.SetTankLevel(1);
                MyTank.Object_Texture = IMG_LoadTexture(renderer, "images/My_Tank_1.png");

                bullet->setDirection(-1); // Mark bullet for deletion

				livesRemaining.AddVal(MyTank.GetHealth(), renderer);
                return; // Exit after first hit to prevent multiple hits in one frame
            }
        }
    }
}

void CheckCollisionWithEnemy(MainObject& MyTank, std::vector<Enemy>& enemyTanks, SDL_Renderer* renderer, ScoreManager& scoreManager, 
                             int &tmp, int& enemiesDestroyed, std::vector<PowerUp>& powerUps) {
    SDL_Texture* explosionTexture = IMG_LoadTexture(renderer, "images/explosion.png");
    const int explosionFrameWid = 50;
    const int explosionFrameHei = 50;
    const int totalExplosionFrames = 8;

    for (auto it = MyTank.bullets.begin(); it != MyTank.bullets.end(); ) {
        bool hit = false;
        for (auto et = enemyTanks.begin(); et != enemyTanks.end(); ) {
            SDL_Rect EnemyRect = {et->GetX(), et->GetY(), et->GetObjectWidth(), et->GetObjectHeight()};
            SDL_Rect BulletRect = {(*it)->GetX(), (*it)->getY(), (*it)->GetObjectWidth(), (*it)->GetObjectHeight()};

            if (MyTank.CheckCollision(EnemyRect, BulletRect)) {
                Mix_Chunk* DieSound = Mix_LoadWAV("sounds/EnemyDie.wav");
                Mix_PlayChannel(-1, DieSound, 0);

                enemiesDestroyed++;
                cout << enemiesDestroyed << endl;
                if (et->Object_Texture) {
                    SDL_DestroyTexture(et->Object_Texture);
                    et->Object_Texture = nullptr;
                    tmp--;
                }
                // Explosion animation
                for (int frame = 0; frame < totalExplosionFrames; frame++) {
                    renderTexture(explosionTexture, renderer, et->GetX(), et->GetY(), et->GetObjectWidth(), et->GetObjectHeight());
                    SDL_RenderPresent(renderer);
                    SDL_Delay(15);
                }
                // Add score when enemy is destroyed
                //scoreManager.AddScore(et->getScoreEnemy(), renderer);
				scoreManager.AddVal(et->getScoreEnemy(), renderer);

                if(et->GetTankTypes() == "1_red" || et->GetTankTypes() == "2_red" || et->GetTankTypes() == "3_red" || et->GetTankTypes() == "4_red"){
                    // Create a power-up at a random position
                    int powerUpX = rand() % (SCREEN_WIDTH - 150 - 40);
                    int powerUpY = rand() % (SCREEN_HEIGHT - 40);
                    int powerUp_index = rand() % 6;
					powerUps.emplace_back(renderer, powerUpX, powerUpY, PowerUps_array[powerUp_index]);
                }

                et = enemyTanks.erase(et);
                hit = true;
                
                break;
            } else {
                ++et;
            }
        }
        if (hit) {
            delete *it;
            it = MyTank.bullets.erase(it);
        } else {
            ++it;
        }
    }
	enemiesRemaining.AddEnemies_Remaining(EnemyNum - enemiesDestroyed, renderer);
    SDL_DestroyTexture(explosionTexture);
}

void SpawnEnemy(vector<Enemy>& Enemy_array, SDL_Renderer* gRenderer, Uint32& lastSpawnTime, const Uint32 spawnCooldown, int& cnt, const int EnemyNum) {
    Uint32 currentTime = SDL_GetTicks();
    int index = rand() % 8;
    if (cnt < EnemyNum && currentTime - lastSpawnTime >= spawnCooldown) {
        Enemy enemy;
        int startX = rand() % (SCREEN_WIDTH - 40 - 150); // Random vị trí x trong khoảng chiều rộng màn hình
        int startY = 0; // Hàng đầu tiên
		if(EnemyTankTypes[index] == "images/enemyTank1R.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 1);
			enemy.setScoreEnemy(200);
			enemy.SetHealth(1);
            enemy.setBulletSpeed(1);
            enemy.SetTankTypes("1_normal");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank1R_1.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 1);
			enemy.setScoreEnemy(200);
			enemy.SetHealth(1);
            enemy.setBulletSpeed(1);
            enemy.SetTankTypes("1_red");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank2R.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 4);
			enemy.setScoreEnemy(300);
			enemy.SetHealth(2);
            enemy.setBulletSpeed(3);
            enemy.SetTankTypes("2_normal");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank2R_1.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 4);
			enemy.setScoreEnemy(300);
			enemy.SetHealth(2);
            enemy.setBulletSpeed(3);
            enemy.SetTankTypes("2_red");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank3R.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 3);
			enemy.setScoreEnemy(300);
			enemy.SetHealth(3);
            enemy.setBulletSpeed(3);
            enemy.SetTankTypes("3_normal");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank3R_1.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 3);
			enemy.setScoreEnemy(400);
			enemy.SetHealth(4);
            enemy.setBulletSpeed(3);
            enemy.SetTankTypes("3_red");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank4R_3.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 2);
			enemy.setScoreEnemy(400);
			enemy.SetHealth(4);
            enemy.setBulletSpeed(2);
            enemy.SetTankTypes("4_normal");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank4R_4.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 2);
			enemy.setScoreEnemy(400);
			enemy.SetHealth(4);
            enemy.setBulletSpeed(2);
            enemy.SetTankTypes("4_red");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
        
        Enemy_array.push_back(enemy);
        lastSpawnTime = currentTime;
        cnt++;
    }
	else if(cnt == 0){
		Enemy enemy;
		int startX = rand() % (SCREEN_WIDTH - 40 - 150); // Random vị trí x trong khoảng chiều rộng màn hình
		int startY = 0; // Hàng đầu tiên
		//int Enemy_Index = rand() % 6;
		if(EnemyTankTypes[index] == "images/enemyTank1R.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 1);
			enemy.setScoreEnemy(200);
			enemy.SetHealth(1);
            enemy.setBulletSpeed(1);
            enemy.SetTankTypes("1_normal");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank1R_1.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 1);
			enemy.setScoreEnemy(200);
			enemy.SetHealth(1);
            enemy.setBulletSpeed(1);
            enemy.SetTankTypes("1_red");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank2R.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 4);
			enemy.setScoreEnemy(300);
			enemy.SetHealth(2);
            enemy.setBulletSpeed(3);
            enemy.SetTankTypes("2_normal");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank2R_1.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 4);
			enemy.setScoreEnemy(300);
			enemy.SetHealth(2);
            enemy.setBulletSpeed(3);
            enemy.SetTankTypes("2_red");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank3R.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 3);
			enemy.setScoreEnemy(300);
			enemy.SetHealth(3);
            enemy.setBulletSpeed(3);
            enemy.SetTankTypes("3_normal");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank3R_1.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 3);
			enemy.setScoreEnemy(400);
			enemy.SetHealth(4);
            enemy.setBulletSpeed(3);
            enemy.SetTankTypes("3_red");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank4R_3.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 2);
			enemy.setScoreEnemy(400);
			enemy.SetHealth(4);
            enemy.setBulletSpeed(2);
            enemy.SetTankTypes("4_normal");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		else if(EnemyTankTypes[index] == "images/enemyTank4R_4.png"){
			enemy.Get_Parameters(startX, startY, 40, 40, 2);
			enemy.setScoreEnemy(400);
			enemy.SetHealth(4);
            enemy.setBulletSpeed(2);
            enemy.SetTankTypes("4_red");
			enemy.Init(gRenderer, EnemyTankTypes[index]);
		}
		Enemy_array.push_back(enemy);
		cnt++;
	}
}

bool CheckTankCollision(MainObject& MyTank, vector<Enemy>& Enemy_array) {
    SDL_Rect MyTankRect = {MyTank.GetX(), MyTank.GetY(), MyTank.GetObjectWidth(), MyTank.GetObjectHeight()};
    for (auto& enemy : Enemy_array) {
        SDL_Rect EnemyRect = {enemy.GetX(), enemy.GetY(), enemy.GetObjectWidth(), enemy.GetObjectHeight()};
        if (MyTank.CheckCollision(MyTankRect, EnemyRect)) {
            MyTank.RevertMove();  // Khôi phục lại vị trí cũ của MyTank
            enemy.RevertMove();   // Khôi phục lại vị trí cũ của enemy (nếu cần)
			int tmp = rand() % 4;
			if(tmp == 0) enemy.SetDir(0);
			else if(tmp == 90) enemy.SetDir(90);
			else if(tmp == 180) enemy.SetDir(180);
			else enemy.SetDir(270);//o day
            return true;
        }
    }
    return false;
}



void CheckEnemyCollisions(vector<Enemy>& enemies) {
    for (size_t i = 0; i < enemies.size(); ++i) {
        SDL_Rect rect1 = {enemies[i].GetX(), enemies[i].GetY(), enemies[i].GetObjectWidth(), enemies[i].GetObjectHeight()};
        for (size_t j = i + 1; j < enemies.size(); ++j) {
            SDL_Rect rect2 = {enemies[j].GetX(), enemies[j].GetY(), enemies[j].GetObjectWidth(), enemies[j].GetObjectHeight()};
            if (CheckCollision(rect1, rect2)) {
                // Nếu có va chạm, khôi phục lại vị trí cũ của cả hai xe
                enemies[i].RevertMove();
                enemies[j].RevertMove();
				int tmp = rand() % 4;
				if(tmp == 0) enemies[i].SetDir(0);
				else if(tmp == 90) enemies[i].SetDir(90);
				else if(tmp == 180) enemies[i].SetDir(180);
				else enemies[i].SetDir(270);	

				int temp = rand() % 4;
				if(temp == 0) enemies[j].SetDir(0);
				else if(temp == 90) enemies[j].SetDir(90);
				else if(temp == 180) enemies[j].SetDir(180);
				else enemies[j].SetDir(270);	
            }
        }
    }
}

#undef main
int main(int argc, char* argv[]) {
    srand(time(0));
	bool quit = false;
	bool startGame = false;


	if (!Init(gWindow, gRenderer)) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }
	//khoi tao background
	if(!loadImage(gRenderer, "images/cover.png", gTexture)){
		cout << "Faild to load background" << IMG_GetError() << endl;
		close(gWindow, gRenderer, gMusic,  gSoundEffect, gFont);
	}
	//create menu and buttons
	//menu
	SDL_Surface* MenuSurface = IMG_Load("images/cover.png");
	SDL_Texture* MenuBackground = SDL_CreateTextureFromSurface(gRenderer, MenuSurface);
    SDL_FreeSurface(MenuSurface);

	//newgame button
	if(!loadImage(gRenderer, "images/NewGameButton.png", gTexture)){
		cout << "Faild to load newgame button" << IMG_GetError() << endl;
		close(gWindow, gRenderer, gMusic,  gSoundEffect, gFont);
	}
	SDL_Surface* NewGameButtonSurface = IMG_Load("images/NewGameButton.png");
	SDL_Texture* NewGameButtonTexture = SDL_CreateTextureFromSurface(gRenderer, NewGameButtonSurface);
    SDL_FreeSurface(NewGameButtonSurface);

	//instruction button
	if(!loadImage(gRenderer, "images/Instruction_Button.png", gTexture)){
		cout << "Faild to load instruction button" << IMG_GetError() << endl;
		close(gWindow, gRenderer, gMusic,  gSoundEffect, gFont);
	}
	SDL_Surface* InstructionButtonSurface = IMG_Load("images/Instruction_Button.png");
	SDL_Texture* InstructionButtonTexture = SDL_CreateTextureFromSurface(gRenderer, InstructionButtonSurface);
    SDL_FreeSurface(InstructionButtonSurface);

	//exit button
	if(!loadImage(gRenderer, "images/ExitGameButton.png", gTexture)){
		cout << "Faild to load exit button" << IMG_GetError() << endl;
		close(gWindow, gRenderer, gMusic,  gSoundEffect, gFont);
	}
	SDL_Surface* ExitGameButtonSurface = IMG_Load("images/ExitGameButton.png");
	SDL_Texture* ExitGameButtonTexture = SDL_CreateTextureFromSurface(gRenderer, ExitGameButtonSurface);
    SDL_FreeSurface(ExitGameButtonSurface);

	//instruction menu
	if(!loadImage(gRenderer, "images/Instruction_Menu.png", gTexture)){
		cout << "Faild to load Instruction_Menu" << IMG_GetError() << endl;
		//close(gWindow, renderer, gMusic,  gSoundEffect, gFont);
	}
	SDL_Surface* InstructionMenuSurface = IMG_Load("images/Instruction_Menu.png");
	SDL_Texture* InstructionMenuTexture = SDL_CreateTextureFromSurface(gRenderer, InstructionMenuSurface);
    //SDL_FreeSurface(InstructionButtonSurface);

	 //game loop
    gameLoop:
    Mix_HaltMusic();

	//khoi tao music background
	if(!loadMusic("sounds/We_The_People.mp3", gMusic)){
		cout << "Failed to load music background" << endl;
		close(gWindow, gRenderer, gMusic,  gSoundEffect, gFont);
	}

	//chay music background
	Mix_Music* MenuMusic = gMusic;
	//Mix_PlayMusic(MenuMusic, -1);

    //tieng nhac nen
    


	//hien ra menu va cac nut bam va dong thi xoa het ca texture
	showMenu(gRenderer, MenuBackground, NewGameButtonTexture, ExitGameButtonTexture, InstructionButtonTexture, InstructionMenuTexture, quit, startGame);

	//tat  nhac
	//Mix_HaltMusic();
    Mix_Chunk* GameOverSound = Mix_LoadWAV("sounds/GameOverSound.wav");
    Mix_Chunk* CollectBuffsSound = Mix_LoadWAV("sounds/CollectBuffsSound.wav");
    Mix_Chunk* NextLevelSound = Mix_LoadWAV("sounds/NexLevelSound.wav");
    Mix_Chunk* IntroSound = Mix_LoadWAV("sounds/IntroStageSound.wav");

	//background chinh cua game
	if(!loadImage(gRenderer, "images/GameBackground.png", gTexture)){
		cout << "Faild to load background" << IMG_GetError() << endl;
		close(gWindow, gRenderer, gMusic,  gSoundEffect, gFont);
	}
	SDL_Surface* MainBackgroundSurface = IMG_Load("images/GameBackground.png");
	SDL_Texture* MainBackgroundTexture = SDL_CreateTextureFromSurface(gRenderer, MainBackgroundSurface);
    SDL_FreeSurface(MainBackgroundSurface);

	//thanh ben phai cua game
	if(!loadImage(gRenderer, "images/Right_bar.png", gTexture)){
		cout << "Fail to load Right bar image" << endl;
		close(gWindow, gRenderer, gMusic,  gSoundEffect, gFont);
	}
	SDL_Surface* RightBarSurface = IMG_Load("images/Right_bar.png");
	SDL_Texture* RightBarTexture = SDL_CreateTextureFromSurface(gRenderer, RightBarSurface);
    SDL_FreeSurface(RightBarSurface);

	//la co level cua game
	if(!loadImage(gRenderer, "images/Level_Flag.png", gTexture)){
		cout << "Fail to load Level_Flag image" << endl;
		close(gWindow, gRenderer, gMusic,  gSoundEffect, gFont);
	}
	SDL_Surface* LevelFlagSurface = IMG_Load("images/Level_Flag.png");
	SDL_Texture* LevelFlagTexture = SDL_CreateTextureFromSurface(gRenderer, LevelFlagSurface);
    SDL_FreeSurface(LevelFlagSurface);
	
	//doc vao map
	
	//khoi tao nhac nen game
	/*if(!loadMusic("sounds/BgMusic.mp3", gMusic)){
		cout << "Failed to load Moving_Sound" << endl;
		close(gWindow, gRenderer, gMusic,  gSoundEffect, gFont);
	}
	Mix_Music* GameMusicBackround = gMusic;*/
	//Mix_PlayMusic(GameMusicBackround, -1);
 //   if(!loadMusic("sounds/Moving_Sound.mp3", gMusic)){
	//	cout << "Failed to load music background" << endl;
	//	close(gWindow, gRenderer, gMusic,  gSoundEffect, gFont);
	//}
 //   Mix_Music* MainGameMusic = gMusic;
    //Mix_PlayMusic(MainGameMusic, -1);
    Mix_Chunk* MainGameMusic = Mix_LoadWAV("sounds/Moving_Sound.wav");

	//Khoi tao main Object - My tank
	MainObject My_Tank;
	
	My_Tank.SetTankLevel(1);
	My_Tank.setBulletSpeed(1);
    My_Tank.SetHealth(3);
    My_Tank.SetObjectSpeed(1);
    Mix_Chunk* ShootingSound = Mix_LoadWAV("sounds/ShootingSound.wav");
    My_Tank.Set_Sound(ShootingSound);

    Mix_Chunk* CollisionSound = Mix_LoadWAV("sounds/CollisionSound.wav");
    My_Tank.Set_Collision_Sound(CollisionSound);

	if(My_Tank.loadImage("images/My_Tank_1.png", gRenderer) == true){
		My_Tank.Get_Parameters(200, SCREEN_HEIGHT - 40, 40, 40, 1);
	}
	

    //khoi tao gameover image
    if(!loadImage(gRenderer, "images/gameover.png", gTexture)){
		cout << "Fail to load gameover image" << endl;
		close(gWindow, gRenderer, gMusic,  gSoundEffect, gFont);
	}
	SDL_Surface* GameOverSurface = IMG_Load("images/gameover.png");
	SDL_Texture* GameOverTexture = SDL_CreateTextureFromSurface(gRenderer, GameOverSurface);
    SDL_FreeSurface(GameOverSurface);

	//khoi tao score counter
	SDL_Surface* ScoreSurface = IMG_Load("images/score_counter.png");
	SDL_Texture* ScoreTexture = SDL_CreateTextureFromSurface(gRenderer, ScoreSurface);
	SDL_FreeSurface(ScoreSurface);

	scoreManager.AddVal(-scoreManager.getVal(), gRenderer);
    scoreManager.Render(gRenderer);

    //scoreManager.AddScore(-scoreManager.getScore(), gRenderer);
    //scoreManager.Render(gRenderer);
    
    bool turnOn = false;
    EnemyNum = 5;
    
	for(int i = currentLevel - 1; i < 6; i++){
        if(i == 0){
            Mix_PlayChannel(-1, IntroSound, 0);
            turnOn = true;
        }
        Mix_PlayChannel(5, MainGameMusic, 0);
        Mix_Volume(5, MIX_MAX_VOLUME / 2);
        
        //Mix_HaltMusic();

        

        readFileToMatrix(Maps_array[i]);
	    InitMap(gRenderer);

        //My_Tank.SetHealth(3);
        My_Tank.SetX(200);
        My_Tank.SetY(SCREEN_HEIGHT - 40);
        My_Tank.SetObjectSpeed(1);

        //khoi tao enemies
        
        int tmp = EnemyNum;
        int enemiesDestroyed = 0;

        vector<Enemy> Enemy_array;
        int cnt = 0;
	    Uint32 lastSpawnTime = 0; // Thời gian lần cuối cùng sinh ra enemy tank
	    const Uint32 spawnCooldown = 3000; // Thời gian giữa mỗi lần sinh ra enemy tank (5 giây)

        vector<PowerUp> powerUps;

		level.AddVal(currentLevel, gRenderer);
		level.Render(gRenderer);
		enemiesRemaining.AddEnemies_Remaining(EnemyNum, gRenderer);
		enemiesRemaining.Render(gRenderer);
		livesRemaining.AddVal(My_Tank.GetHealth(), gRenderer);
		livesRemaining.Render(gRenderer);

	    while(!quit){
            while(SDL_PollEvent(&e) != 0){
			    if (e.type == SDL_QUIT) {
                    quit = true;

				    //nhan ban phim di chuyen
                }
			    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                            // Handle ESC key press to return to the main menu
					//Mix_Music* MenuMusic = gMusic;
	                //Mix_PlayMusic(MenuMusic, -1);
                    Mix_HaltChannel(-1);
                    ReturnToMainMenu(gRenderer, MenuBackground, NewGameButtonTexture, 
                                        ExitGameButtonTexture, InstructionButtonTexture, 
                                        InstructionMenuTexture, quit, startGame);
                   // scoreManager.AddScore(-scoreManager.getScore(), gRenderer);
                    goto gameLoop;
                }
                else 
                {
                    My_Tank.HandleInputAction(e, gRenderer);
                }
            }
		        SDL_RenderClear(gRenderer);

                

		        CheckCollisionWithEnemyBullets(My_Tank, Enemy_array, gRenderer);
                //game over
                if (My_Tank.GetHealth() <= 0) {
                    SDL_RenderClear(gRenderer);
                    Mix_HaltChannel(-1);

                    
                    Mix_PlayChannel(-1, GameOverSound, 0);

                    renderTexture(GameOverTexture, gRenderer, 0 ,0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    SDL_RenderPresent(gRenderer);
                    SDL_Delay(5000);

                    
                    ReturnToMainMenu(gRenderer, MenuBackground, NewGameButtonTexture, ExitGameButtonTexture, InstructionButtonTexture, InstructionMenuTexture, quit, startGame);
                    goto gameLoop;
                }
		        else if(enemiesDestroyed == 20) goto gameLoop;


		        //in ra main background, rigth bar, level flag, 
		        renderTexture(MainBackgroundTexture, gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		        renderTexture(RightBarTexture, gRenderer, 750, 0, 150, SCREEN_HEIGHT);
		        renderTexture(LevelFlagTexture, gRenderer, 790, 550, 75, 75);

		        //renderTexture(BulletTexture, gRenderer, 0, 0, 50, 50);
                
		        //show my tank
		        My_Tank.Move(gRenderer);
		        if (CheckTankCollision(My_Tank, Enemy_array)) {
			        // If collision detected, revert the tank position
			        My_Tank.RevertMove();
		        }
		        My_Tank.ShowBullets(gRenderer);
		        My_Tank.ShowObject(gRenderer);

				level.AddVal(i + 1, gRenderer);
				level.Render(gRenderer);

                //check game over
                if(!CheckGameOver()){
                    SDL_RenderClear(gRenderer);
                    Mix_HaltChannel(-1);
                    Mix_PlayChannel(-1, GameOverSound, 0);

                    renderTexture(GameOverTexture, gRenderer, 0 ,0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    SDL_RenderPresent(gRenderer);
                    SDL_Delay(5000);
                    
                    //game over sound
                    //Mix_HaltMusic();

                    //Mix_Chunk* GameOverSound = Mix_LoadWAV("sounds/GameOverSound.wav");
                    

                    //reset
                    ReturnToMainMenu(gRenderer, MenuBackground, NewGameButtonTexture, ExitGameButtonTexture, 
                        InstructionButtonTexture, InstructionMenuTexture, quit, startGame);
                        goto gameLoop;
                }


		        SpawnEnemy(Enemy_array, gRenderer, lastSpawnTime, spawnCooldown, cnt, EnemyNum);

		        // Enemy Tanks/kiem tra va cham dan va dic
		        for (auto& enemy : Enemy_array) {
			        enemy.Move();
			        enemy.Shoot(gRenderer);
			        enemy.ShowBullets(gRenderer);
                
			        enemy.ShowObject(gRenderer);
		        }
                
                showMap(gRenderer);
                //if(turnOn) Mix_PlayChannel(-1, MainGameMusic, 0);
		 
                CheckEnemyCollisions(Enemy_array);

		        CheckCollisionWithEnemy(My_Tank, Enemy_array, gRenderer, scoreManager, tmp, enemiesDestroyed, powerUps);

                //check(Mark_Postion, gRenderer);
 
                //kiem tra len lv
                if(enemiesDestroyed == EnemyNum) break;

                // Render the score
                scoreManager.Render(gRenderer);

				enemiesRemaining.Render(gRenderer);
				livesRemaining.Render(gRenderer);

                // Update power-ups
                Uint32 deltaTime = SDL_GetTicks();
                for (auto& powerUp : powerUps) {
                    powerUp.Update(deltaTime);
                }
                // Remove inactive power-ups
                powerUps.erase(std::remove_if(powerUps.begin(), powerUps.end(), [](const PowerUp& p) { return !p.IsActive(); }), powerUps.end());

                // Render power-ups
                for (auto& powerUp : powerUps) {
                    powerUp.Render(gRenderer);
                }

                // Handle power-up collection
                HandlePowerUpCollection(My_Tank, powerUps, Enemy_array, gRenderer, CollectBuffsSound);

				//hien score counter
				renderTexture(ScoreTexture, gRenderer, 750, 280, 150, 100);

		        SDL_RenderPresent(gRenderer);
                SDL_Delay(1);
	        }
        //Mix_HaltMusic();
        if(enemiesDestroyed == EnemyNum) Mix_PlayChannel(-1, NextLevelSound, 0);
        EnemyNum+= 2;
        //if(i > 0) Mix_HaltChannel(-1);
    }
		


	//system("pause");
	SDL_DestroyTexture(ScoreTexture);
    SDL_DestroyTexture(MenuBackground);
    SDL_DestroyTexture(NewGameButtonTexture);
    SDL_DestroyTexture(InstructionButtonTexture);
    SDL_DestroyTexture(ExitGameButtonTexture);
    SDL_DestroyTexture(InstructionMenuTexture);
    SDL_DestroyTexture(MainBackgroundTexture);
    SDL_DestroyTexture(RightBarTexture);

	close(gWindow, gRenderer, gMusic,  gSoundEffect, gFont);
    return 0;
}
