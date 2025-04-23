//
// Created by MSI GF63 on 4/17/2025.
//

#ifndef ENEMY_H
#define ENEMY_H
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
#include "Game.h"
#include "Menu.h"
#include "Boss.h"
#include "Bullet.h"
using namespace std;



class Enemy {
public:
    Enemy(int x,int y, float speedbuff);
    void  move();
    void render(SDL_Renderer* p_renderer, SDL_Texture* p_tex);
    SDL_Rect getRect();
    bool isOutside();

private:
    SDL_Rect rect;
    float speed;
};

void spawnEnemy(vector <Enemy>& Enemies);




#endif //ENEMY_H
