//#ifndef SCOREMANAGER_H
//#define SCOREMANAGER_H
//
//#include "Header.h"
//#include "Init.h"
//#include "CommonFunction.h"
//
//class ScoreManager {
//public:
//    SDL_Texture* EnemyRemainingTexture;
//    SDL_Texture* scoreTexture;
//    SDL_Rect scoreRect;
//    TTF_Font* font;
//    ScoreManager(SDL_Renderer* renderer, int x, int y, int fontSize);
//    ~ScoreManager();
//
//    void AddScore(int points, SDL_Renderer* renderer);
//    void Render(SDL_Renderer* renderer);
//    void UpdateScoreTexture(SDL_Renderer* renderer);
//
//    void RenderEnemyCount(SDL_Renderer* renderer, int &remainingEnemies, int fontSize);
//
//    void setScore(int score_);
//    int getScore();
//private:
//    int score;
//    
//    string scoreText;
//    
//};
//
//#endif // SCOREMANAGER_H

#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "Header.h"
#include "Init.h"
#include "CommonFunction.h"
#include "GameDetails.h"

class ScoreManager : public GameDetails {
public:
    //SDL_Texture* EnemyRemainingTexture;
    SDL_Texture* scoreTexture;
    SDL_Rect scoreRect;
    TTF_Font* font;
    ScoreManager(SDL_Renderer* renderer, int x, int y, int fontSize);

    string writeString();
    void AddVal(int points, SDL_Renderer* renderer);
    //void Render(SDL_Renderer* renderer);
    //void UpdateTexture(SDL_Renderer* renderer);

    // RenderEnemyCount(SDL_Renderer* renderer, int &remainingEnemies, int fontSize);

    
};

#endif // SCOREMANAGER_H
