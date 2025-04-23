//
// Created by MSI GF63 on 4/18/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <SDL.h>


class Entity {
public:
    Entity(int x, int y);
    void render(SDL_Renderer* p_renderer, SDL_Texture* p_tex);
    SDL_Rect getRect();
private:
    SDL_Rect rect;
};



#endif //ENTITY_H
