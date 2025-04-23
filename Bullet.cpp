//
// Created by MSI GF63 on 4/18/2025.
//

#include "Bullet.h"

Bullet::Bullet(int x, int y)
{
    rect.x = x;
    rect.y = y;
    rect.w = 20;
    rect.h = 20;
    speed = 10;
}

void Bullet::move()
{
    rect.x += speed;
}


void Bullet::update( SDL_Renderer* p_renderer,  SDL_Texture* p_tex)
{
    SDL_RenderCopy(p_renderer, p_tex, nullptr, &rect);
}

bool Bullet::bulletLimit(int screenWidth) {
    return rect.x > screenWidth;
}


SDL_Rect Bullet::getRect() {
    return rect;
}

