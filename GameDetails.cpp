#include "GameDetails.h"

GameDetails::GameDetails(SDL_Renderer* renderer, int x, int y, int fontSize) : val(0), texture(nullptr)
{
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        // Handle error appropriately
    }

    // Open the font
    font = TTF_OpenFont("Fonts/Calibri.ttf", fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        // Handle error appropriately
    }


    // Set the position for rendering level
    rect.x = x;
    rect.y = y; // Adjust position as needed
    rect.w = 0; // Will be updated when rendering
    rect.h = 0; // Will be updated when rendering


    // Create the initial textures
    UpdateTexture(renderer);
}

GameDetails::~GameDetails()
{
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}

int GameDetails::getVal()
{
	return val;
}

void GameDetails::setVal(int val_)
{
	val = val_;
}

string GameDetails::writeString()
{  
    return string();
}

void GameDetails::Render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
    
    // Provide a default implementation or leave it empty if it's meant to be overridden
}

void GameDetails::UpdateTexture(SDL_Renderer* renderer) {
	// Provide a default implementation or leave it empty if it's meant to be overridden
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    // Create the level text
    valText = writeString();

    // Render the text to a surface
    SDL_Color textColor = { 0, 0, 0 }; // Black color
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, valText.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return; // Early return on error
    }

    // Create the texture from the surface
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return; // Early return on error
    }

    // Update the size of the rendering rectangle
    rect.w = textSurface->w;
    rect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
}

void GameDetails::AddVal(int val, SDL_Renderer* renderer) {
	// Provide a default implementation or leave it empty if it's meant to be overridden
}
