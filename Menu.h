//
// Created by MSI GF63 on 4/6/2025.
//

#ifndef MENU_H
#define MENU_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <ctime>
#include  <utility>
#include "Globals.h"
#include "Player.h"
#include "Game.h"
#include "Menu.h"
#include "Bullet.h"
using namespace std;


class Menu
{
private:
    SDL_Texture* texture;
    SDL_Rect rect;
public:
    Menu(SDL_Texture* p_texture, int p_x, int p_y, int p_w, int p_h);
    void Render(SDL_Renderer* p_renderer);
    SDL_Rect getRect();
};

SDL_Texture* loadMenuTexture(SDL_Renderer* p_renderer, const char* p_filePath);




#endif //MENU_H
