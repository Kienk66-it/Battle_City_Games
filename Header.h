#ifndef HEADER_H
#define HEADER_H
#pragma once	

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <fstream>

using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 750;
const int NEW_GAME_BUTTON_WIDTH = 210;
const int NEW_GAME_BUTTON_HEIGHT = 70;

const int EXIT_GAME_BUTTON_WIDTH = 210;
const int EXIT_GAME_BUTTON_HEIGHT = 70;

static SDL_Window* gWindow = nullptr;
static SDL_Renderer* gRenderer = nullptr;
static SDL_Texture* gTexture = nullptr;
static Mix_Music* gMusic = nullptr;
static Mix_Chunk* gSoundEffect = nullptr;
static TTF_Font* gFont = nullptr;
static SDL_Event e;

enum GameState {
    STATE_MENU,
    STATE_GAME
};


#endif