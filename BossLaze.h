//
// Created by MSI GF63 on 4/11/2025.
//

#ifndef BOSSLAZE_H
#define BOSSLAZE_H
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Boss.h"



class BossLaze {
public:
    BossLaze(int x, int y);
    void render(SDL_Renderer* p_renderer, SDL_Texture* p_texture);
    SDL_Rect getRect();
    void move();
private:
    SDL_Rect rect;
    float speed;
};

void spawnBossLaze(vector<BossLaze>& BossLazes, vector <pair<Boss,int>>& Bosses);


#endif //BOSSLAZE_H


