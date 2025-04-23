//
// Created by MSI GF63 on 4/18/2025.
//

#include "BossLaze.h"
BossLaze::BossLaze(int x, int y)
{
    rect.x = x;
    rect.y = y;
    rect.w =64;
    rect.h =32;
    speed = 6;
}

void BossLaze::render(SDL_Renderer* p_renderer, SDL_Texture* p_texture)
{
    SDL_RenderCopy(p_renderer,p_texture, nullptr, &rect);
}

SDL_Rect BossLaze::getRect()
{
    return rect;
}

void BossLaze::move()
{
    rect.x -= speed;
}

void spawnBossLaze(vector<BossLaze>& BossLazes, vector <pair<Boss,int>>& Bosses)
{
    for (size_t i = 0; i < Bosses.size(); i++)
    {
        float x = Bosses[i].first.bossPositioning().first;
        float y = Bosses[i].first.bossPositioning().second;
        BossLaze bosslazee(x, y);
        BossLazes.push_back(bosslazee);
    }
}