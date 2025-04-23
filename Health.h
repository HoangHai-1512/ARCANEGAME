//
// Created by MSI GF63 on 4/18/2025.
//

#ifndef HEALTH_H
#define HEALTH_H
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Globals.h"
using namespace std;

class Health {
public:
    Health(int x, int y);
    void Render(SDL_Renderer* renderer, SDL_Texture* texture);
private:
    SDL_Rect rect;
};



#endif //HEALTH_H
