
#include "Menu.h"
Menu::Menu(SDL_Texture* p_texture, int p_x, int p_y, int p_w, int p_h)
{
    rect.x = p_x;
    rect.y = p_y;
    rect.w = p_w;
    rect.h = p_h;
    texture = p_texture;
}

void Menu::Render(SDL_Renderer* p_renderer)
{
    SDL_RenderCopy(p_renderer,texture,nullptr,&rect);
}

SDL_Rect Menu::getRect()
{
    return rect;
}


SDL_Texture* loadMenuTexture(SDL_Renderer* p_renderer, const char* p_filePath)
{
    SDL_Texture* tex = IMG_LoadTexture(p_renderer,p_filePath);
    if (tex == nullptr)
    {
        std::cout << "Failed to load texture: " << IMG_GetError() << std::endl;
    }
    return tex;
}

