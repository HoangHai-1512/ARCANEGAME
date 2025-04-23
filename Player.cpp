

#include "Player.h"
Player::Player(int x, int y)
{
    rect.x = x;
    rect.y = y;
    rect.w = 130;
    rect.h = 160;
    speed = 4;
}

void Player::move(const Uint8* CurrentKeystate)
{
    if (CurrentKeystate[SDL_SCANCODE_W])
    {
        rect.y -= speed;
    }
    if (CurrentKeystate[SDL_SCANCODE_S])
    {
        rect.y += speed;
    }
    if (CurrentKeystate[SDL_SCANCODE_A])
    {
        rect.x -= speed;
    }
    if (CurrentKeystate[SDL_SCANCODE_D])
    {
        rect.x += speed;
    }
}

void Player::limit(int screenWidth, int screenHeight)
{
    if (rect.x < 0)
    {
        rect.x = 0;
    }
    if (rect.y < 0)
    {
        rect.y = 0;
    }
    if (rect.x + rect.w > screenWidth)
    {
        rect.x = screenWidth - rect.w;
    }
    if (rect.y + rect.h > screenHeight)
    {
        rect.y = screenHeight - rect.h;
    }
}

void Player::update(SDL_Renderer* p_renderer, SDL_Texture* p_tex)
{
    SDL_RenderCopy(p_renderer, p_tex, nullptr, &rect);
}

pair<int, int> Player::gunPosition()
{
    return {rect.x + rect.w , rect.y + rect.h / 2 };
}

SDL_Rect Player::getRect()
{
    return rect;
}