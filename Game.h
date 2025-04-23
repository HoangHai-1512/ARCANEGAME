
#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <ctime>
#include  <utility>
#include "Globals.h"
#include "Player.h"
#include "Menu.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Entity.h"
#include "Boss.h"
#include "BossLaze.h"
#include "Health.h"
using namespace std;


class Game {
public:
    Game();
    ~Game();
    void Run(bool &gameRunning);

private:
    bool InitWindowRenderer();
    void Clean();
    SDL_Texture* LoadGameTexture(SDL_Renderer* p_renderer, const char* p_filePath);
    TTF_Font* loadFont(const char* filePath, int size);
    SDL_Texture* renderText(const char* text, SDL_Renderer* p_renderer, TTF_Font* font, SDL_Color color);
    void LoadAudio();
    void PlayMusic();
    void PlaySound(Mix_Chunk* sound);
    SDL_Window* gameplay_window;
    SDL_Renderer*  gameplay_renderer;
    bool isRunning;

    SDL_Texture* backgroundTexture;
    SDL_Texture* playerTexture;
    SDL_Texture* bulletTexture;
    SDL_Texture* enemyTexture;
    SDL_Texture* entityTexture;
    SDL_Texture* bossTexture;
    SDL_Texture* bossLazeTexture;
    SDL_Texture* heartTexture;
    SDL_Texture* victoryTexture;
    SDL_Texture* defeatTexture;
    TTF_Font* font;
    Mix_Music* bgMusic;
    Mix_Chunk* shootSound;
    Mix_Chunk* enemyHitSound;
    Mix_Chunk* playerHitSound;
    Mix_Chunk* defeatSound;
    Mix_Chunk* victorySound;

    // Delay spawn cua enemy
    Uint32 lastSpawnTime = SDL_GetTicks();
    Uint32 spawnDelay = 400;

    //Delay spawn cua Boss
    Uint32 lastSpawnTimeBoss = SDL_GetTicks();
    Uint32 spawnDelayBoss = 2000;

    Uint32 lastShotTime = SDL_GetTicks();
    Uint32 shotDelay = 3000;

};



#endif //GAME_H
