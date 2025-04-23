//
// Created by MSI GF63 on 4/18/2025.
//

#ifndef BULLET_H
#define BULLET_H
#include <SDL.h>
#include <iostream>
using namespace std;


class Bullet {
public:
    Bullet(int x, int y);

    void move();
    void update( SDL_Renderer* p_renderer,  SDL_Texture* p_tex);
    bool bulletLimit(int ScreenWidth);
    SDL_Rect getRect();

private:
    SDL_Rect rect;
    float speed;
};



#endif //BULLET_H
