//
// Created by MSI GF63 on 4/18/2025.
//

#include "Health.h"
Health::Health(int x, int y)
{
    rect.x = x;
    rect.y = y;
    rect.w = 50;
    rect.h = 50;
}

void Health::Render(SDL_Renderer* p_renderer, SDL_Texture* p_tex)
{
    SDL_RenderCopy(p_renderer, p_tex, nullptr, &rect);
}