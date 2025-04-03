#include "Init.h"

bool Init(SDL_Window*& gWindow, SDL_Renderer*& gRenderer) {
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Khởi tạo SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Khởi tạo SDL_mixer
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
        std::cerr << "SDL_mixer could not initialize! MIX_Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! MIX_Error: " << Mix_GetError() << std::endl;
        return false;
    }

    // Khởi tạo SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    // Tạo cửa sổ
    gWindow = SDL_CreateWindow("Battle City", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Tạo renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

// Hàm để tải ảnh nền
bool loadImage(SDL_Renderer* gRenderer, const std::string& path, SDL_Texture*& texture) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (texture == nullptr) {
        std::cerr << "Unable to create texture from " << path << "! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    SDL_FreeSurface(loadedSurface);
    return true;
}

// Hàm để tải nhạc nền
bool loadMusic(const std::string& path, Mix_Music*& music) {
    music = Mix_LoadMUS(path.c_str());
    if (music == nullptr) {
        std::cerr << "Unable to load music " << path << "! MIX_Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

// Hàm để tải hiệu ứng âm thanh
bool loadSoundEffect(const std::string& path, Mix_Chunk*& soundEffect) {
    soundEffect = Mix_LoadWAV(path.c_str());
    if (soundEffect == nullptr) {
        std::cerr << "Unable to load sound effect " << path << "! MIX_Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

// Hàm để tải phông chữ
bool loadFont(const std::string& path, int fontSize, TTF_Font*& font) {
    font = TTF_OpenFont(path.c_str(), fontSize);
    if (font == nullptr) {
        std::cerr << "Unable to load font " << path << "! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void close(SDL_Window* gWindow, SDL_Renderer* gRenderer, Mix_Music* gMusic, Mix_Chunk* gSoundEffect, TTF_Font* gFont) {
    // Giải phóng phông chữ
    if (gFont != nullptr) {
        TTF_CloseFont(gFont);
        gFont = nullptr;
    }

    // Giải phóng nhạc nền
    if (gMusic != nullptr) {
        Mix_FreeMusic(gMusic);
        gMusic = nullptr;
    }

    // Giải phóng hiệu ứng âm thanh
    if (gSoundEffect != nullptr) {
        Mix_FreeChunk(gSoundEffect);
        gSoundEffect = nullptr;
    }

    // Giải phóng background texture
    if (gTexture != nullptr) {
        SDL_DestroyTexture(gTexture);
        gTexture = nullptr;
    }

    // Giải phóng renderer
    if (gRenderer != nullptr) {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = nullptr;
    }

    // Giải phóng cửa sổ
    if (gWindow != nullptr) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }

    // Dọn dẹp SDL_mixer
    Mix_Quit();

    // Dọn dẹp SDL_ttf
    TTF_Quit();

    // Dọn dẹp SDL_image
    IMG_Quit();

    // Dọn dẹp SDL
    SDL_Quit();
}