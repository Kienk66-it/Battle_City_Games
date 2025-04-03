#include "CommonFunction.h"

// show image
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int width, int height) {
    SDL_Rect renderQuad = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

// check (x, y) is in rect?
bool isPointInRect(int x, int y, SDL_Rect rect) {
    return (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h);
}

void showMenu(SDL_Renderer* renderer, SDL_Texture* menu_background, SDL_Texture* newgameButton, SDL_Texture* exitButton,
              SDL_Texture* instructionButton, SDL_Texture* instructionMenu, bool &quit, bool &startGame) {
    SDL_Rect newGameRect = { SCREEN_WIDTH / 2 - 105, SCREEN_HEIGHT / 2 + 50, NEW_GAME_BUTTON_WIDTH, NEW_GAME_BUTTON_HEIGHT };
    SDL_Rect instructionRect = { SCREEN_WIDTH / 2 - 105, SCREEN_HEIGHT / 2 + 130, EXIT_GAME_BUTTON_WIDTH, EXIT_GAME_BUTTON_HEIGHT };
    SDL_Rect exitGameRect = { SCREEN_WIDTH / 2 - 105, SCREEN_HEIGHT / 2 + 210, EXIT_GAME_BUTTON_WIDTH, EXIT_GAME_BUTTON_HEIGHT };
    SDL_Rect instructionMenuRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    SDL_Event e;
    bool back = false;
    bool menuNeedsUpdate = true;

    while (!quit && !startGame) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                if (back) {
                    back = false;  // Quay lại menu chính nếu đang ở màn hình hướng dẫn
                } else {
                    quit = true;   // Thoát khỏi game nếu đang ở menu chính
                }
                menuNeedsUpdate = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (isPointInRect(x, y, newGameRect) && !back) {
                    startGame = true;
                    back = true;
                    menuNeedsUpdate = true;
					//SDL_RenderClear(renderer);
                } else if (isPointInRect(x, y, exitGameRect) && !back) {
                    quit = true;
                } else if (isPointInRect(x, y, instructionRect)) {
                    back = true;
                    menuNeedsUpdate = true;
                }
            }
        }

        if (menuNeedsUpdate && !startGame) {
            SDL_RenderClear(renderer);
            if (!back) {
                SDL_RenderCopy(renderer, menu_background, nullptr, nullptr);
                SDL_RenderCopy(renderer, instructionButton, nullptr, &instructionRect);
                SDL_RenderCopy(renderer, exitButton, nullptr, &exitGameRect);
                SDL_RenderCopy(renderer, newgameButton, nullptr, &newGameRect);
            } else  if(back){
               SDL_RenderCopy(renderer, instructionMenu, nullptr, &instructionMenuRect);
            }
            SDL_RenderPresent(renderer);
            menuNeedsUpdate = false;
        }
    }

    // clear mem
    /*if (menu_background) SDL_DestroyTexture(menu_background);
    if (exitButton) SDL_DestroyTexture(exitButton);
    if (instructionButton) SDL_DestroyTexture(instructionButton);
    if (newgameButton) SDL_DestroyTexture(newgameButton);*/
}

bool Check_Collision(SDL_Rect a, SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

void ReturnToMainMenu(SDL_Renderer* renderer, SDL_Texture* menuBackground, SDL_Texture* newGameButtonTexture,
                      SDL_Texture* exitButtonTexture, SDL_Texture* instructionButtonTexture, 
                      SDL_Texture* instructionMenuTexture, bool& quit, bool& startGame) {
    //reset score
    

    // Set the startGame flag to false to return to the menu
    startGame = false;

    // Show the menu screen
    showMenu(renderer, menuBackground, newGameButtonTexture, exitButtonTexture,
             instructionButtonTexture, instructionMenuTexture, quit, startGame);
}

bool CheckGameOver(){
    if(Maps[28][14] == 0 || Maps[28][15] == 0 || Maps[29][14] == 0 || Maps[29][15] == 0) return false;
    return true;
}
