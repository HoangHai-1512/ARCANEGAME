//
// Created by MSI GF63 on 4/18/2025.
//

#include "Boss.h"
#include "Globals.h" // Hoi cham
Boss::Boss(int x, int y)
{
    rect.x = x;
    rect.y = y;
    rect.w = 220;
    rect.h = 220;
}
void Boss::render(SDL_Renderer* p_renderer, SDL_Texture* p_texture)
{
    SDL_RenderCopy(p_renderer, p_texture, nullptr, &rect);
}


SDL_Rect Boss::getRect()
{
    return rect;
}

pair<float, float> Boss::bossPositioning()
{
    return {rect.x - 50 , rect.y + 120 };
}

void spawnBoss(vector<pair<Boss,int>>& Bosses)
{
    float x = Globals::SCREEN_GAME_WIDTH - 233;
    float y = rand() % (Globals::SCREEN_GAME_HEIGHT - 213);
    Boss bosses(x,y);
    Bosses.push_back({bosses,0});
}