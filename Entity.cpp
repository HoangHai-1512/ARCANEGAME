//
// Created by MSI GF63 on 4/18/2025.
//

#include "Entity.h"

Entity::Entity(int x, int y)
{
    rect.x = x;
    rect.y = y;
    rect.w = 150;
    rect.h = 150;
}



SDL_Rect Entity::getRect()
{
    return rect;
}
void Entity::render(SDL_Renderer* p_renderer, SDL_Texture* p_tex)
{
    SDL_RenderCopy(p_renderer, p_tex, nullptr, &rect);
}