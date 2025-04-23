

#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <ctime>
#include  <utility>
#include "Globals.h"
#include "Game.h"
#include "Menu.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Boss.h"
#include "BossLaze.h"
using namespace std;


class Player {
public:
    Player(int x, int y);

    void move(const Uint8* CurrentKeystate);
    void update(SDL_Renderer* p_renderer, SDL_Texture* p_tex);
    void limit(int screenWidth, int screenHeight);
    pair<int,int> gunPosition();
    SDL_Rect getRect();
private:
    int speed;
    SDL_Rect rect;
};



#endif //PLAYER_H
