//#include "ScoreManager.h"
//#include <sstream>
//#include <iostream>
//
//ScoreManager::ScoreManager(SDL_Renderer* renderer, int x, int y, int fontSize)
//    : score(0), scoreTexture(nullptr), EnemyRemainingTexture(nullptr) {
//    // Initialize SDL_ttf
//    if (TTF_Init() == -1) {
//        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
//        // Handle error appropriately
//    }
//
//    // Open the font
//    font = TTF_OpenFont("Fonts/Calibri.ttf", fontSize);
//    if (!font) {
//        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
//        // Handle error appropriately
//    }
//
//    // Set the position for rendering
//    scoreRect.x = x;
//    scoreRect.y = y;
//    scoreRect.w = 0; // Will be updated when rendering
//    scoreRect.h = 0; // Will be updated when rendering
//
//    // Create the initial score texture
//    UpdateScoreTexture(renderer);
//}
//
//ScoreManager::~ScoreManager() {
//    if (scoreTexture) {
//        SDL_DestroyTexture(scoreTexture);
//    }
//    if (font) {
//        TTF_CloseFont(font);
//    }
//    TTF_Quit();
//    if(EnemyRemainingTexture) SDL_DestroyTexture(EnemyRemainingTexture);
//}
//
//void ScoreManager::AddScore(int points, SDL_Renderer* renderer) {
//    score += points;
//    UpdateScoreTexture(renderer);
//}
//
//void ScoreManager::UpdateScoreTexture(SDL_Renderer* renderer) {
//    if (scoreTexture) {
//        SDL_DestroyTexture(scoreTexture);
//    }
//
//    // Create the score text without the "Score:" prefix
//    std::ostringstream ss;
//    ss << score;  // Only show the numerical score
//    scoreText = ss.str();
//
//    // Render the text to a surface
//    SDL_Color textColor = {0, 0, 0}; // Black color
//    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
//    if (!textSurface) {
//        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
//        return; // Early return on error
//    }
//
//    // Create the texture from the surface
//    scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//    if (!scoreTexture) {
//        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
//        SDL_FreeSurface(textSurface);
//        return; // Early return on error
//    }
//
//    // Update the size of the rendering rectangle
//    scoreRect.w = textSurface->w;
//    scoreRect.h = textSurface->h;
//    SDL_FreeSurface(textSurface);
//}
//
//void ScoreManager::Render(SDL_Renderer* renderer) {
//    if (scoreTexture) {
//        SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
//    }
//}
//
//void ScoreManager::RenderEnemyCount(SDL_Renderer* renderer, int &remainingEnemies, int fontSize) {
//    if (TTF_Init() == -1) {
//        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
//        // Handle error appropriately
//    }
//    SDL_Color textColor = {0, 0, 0}; // Black color
//    TTF_Font* font = TTF_OpenFont("Fonts/Calibri.ttf", fontSize);
//    std::string text = "Enemies: " + std::to_string(remainingEnemies);
//    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
//
//    EnemyRemainingTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//    //remainingEnemies--;
//    
//    renderTexture(EnemyRemainingTexture, renderer, 750, 150, 100, 40);
//    SDL_FreeSurface(textSurface);
//    TTF_CloseFont(font);
//    
//}
//
//
//void ScoreManager::setScore(int score_){score = score_;};
//
//int ScoreManager::getScore(){return score;};
//

#include "ScoreManager.h"
#include <sstream>
#include <iostream>

ScoreManager::ScoreManager(SDL_Renderer* renderer, int x, int y, int fontSize)
    : GameDetails(renderer, x, y, fontSize) {
    
}

void ScoreManager::AddVal(int val_, SDL_Renderer* renderer) {
    val += val_;
    UpdateTexture(renderer);
}

string ScoreManager::writeString() {
    std::ostringstream ss;
    ss << val;  // Include the prefix "Level:"
    valText = ss.str();
    return valText;
}


