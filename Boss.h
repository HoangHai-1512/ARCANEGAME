//
// Created by MSI GF63 on 4/18/2025.
//

#ifndef BOSS_H
#define BOSS_H
#include <SDL.h>
#include <vector>

using  namespace std;


class Boss {
public:
    Boss(int x, int y);
    void render(SDL_Renderer* p_renderer, SDL_Texture* p_texture);
    SDL_Rect getRect();
    pair<float,float> bossPositioning();
private:
    SDL_Rect rect;
};

void spawnBoss(vector<pair<Boss,int>>& Bosses);

#endif //BOSS_H
