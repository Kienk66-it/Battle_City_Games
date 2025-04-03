#ifndef INIT_H
#define INIT_H

#include "Header.h"

// Khởi tạo SDL, tạo cửa sổ và renderer
bool Init(SDL_Window*& gWindow, SDL_Renderer*& gRenderer);

// Tải ảnh nền
bool loadImage(SDL_Renderer* gRenderer, const std::string& path, SDL_Texture*& texture);

// Tải nhạc nền
bool loadMusic(const std::string& path, Mix_Music*& music);

// Tải hiệu ứng âm thanh
bool loadSoundEffect(const std::string& path, Mix_Chunk*& soundEffect);

// Tải phông chữ
bool loadFont(const std::string& path, int fontSize, TTF_Font*& font) ;

// Giải phóng tài nguyên và dọn dẹp SDL
void close(SDL_Window* gWindow, SDL_Renderer* gRenderer, Mix_Music* gMusic, Mix_Chunk* gSoundEffect, TTF_Font* gFont);




#endif