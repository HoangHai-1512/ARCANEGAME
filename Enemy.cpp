//
// Created by MSI GF63 on 4/17/2025.
//

#include "Enemy.h"

Enemy::Enemy(int x,int y, float speedbuff)
{
    rect.x = x;
    rect.y = y;
    rect.w = 120;
    rect.h = 120;
    speed = 3 + speedbuff;
}

void  Enemy::move()
{
    rect.x -= speed;
}

void Enemy::render(SDL_Renderer* p_renderer, SDL_Texture* p_tex)
{
    SDL_RenderCopy(p_renderer, p_tex, nullptr, &rect);
}

SDL_Rect Enemy::getRect() {
    return rect;
}

bool Enemy::isOutside() {
    return rect.x + rect.w < 0;
}


void spawnEnemy(vector<Enemy>& Enemies)
{
    int x = Globals::SCREEN_GAME_WIDTH;
    int y = rand() % (Globals::SCREEN_GAME_HEIGHT - 122);
    float speedbuff =  SDL_GetTicks() / 50000;
    Enemy kedich(x,y,speedbuff);
    Enemies.push_back(kedich);
}
