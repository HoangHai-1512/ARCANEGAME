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
#include "Enemy.h"
#include "Boss.h"
#include "BossLaze.h"
#include "Health.h"
#include "Entity.h"
using namespace std;


enum gameState
{
    MENU,
    TUTORIAL,
    PLAY
};


bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "Can not initialize SDL. Error: " << SDL_GetError << endl;
        success = false;
    }
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)))
    {
        cout << "Can not initialize SDL_image. Error: " << IMG_GetError() << endl;
        success = false;
    }
    if (TTF_Init() == -1) // Khoi tao SDL_ttf
    {
        cout << "Could not initialize SDL_ttf. Error: " << TTF_GetError() << endl;
        success = false;
    }
    if (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1) // Khoi tao SDL_mixer
    {
        cout << "Could not initialize SDL_mixer. Error: " << Mix_GetError() << endl;
        success = false;
    }
    return success;
}

bool RenderWindow()
{
    bool success = true;
    Globals::g_Window =SDL_CreateWindow("ARCANE",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Globals::SCREEN_MENU_WIDTH, Globals::SCREEN_MENU_HEIGHT, SDL_WINDOW_SHOWN);
    if (Globals::g_Window == nullptr)
    {
        cout << "Can not create window. Erorr: " << SDL_GetError() << endl;
        success = false;
    }
    Globals::g_Renderer = SDL_CreateRenderer(Globals::g_Window, - 1, SDL_RENDERER_ACCELERATED);
    if (Globals::g_Renderer == nullptr)
    {
        cout << "Can not create renderer. Error: " << SDL_GetError() << endl;
        success = false;
    }
    SDL_SetRenderDrawColor(Globals::g_Renderer, 0, 0, 0, 255); // Set mau ve cho renderer
    SDL_RenderSetLogicalSize(Globals::g_Renderer, Globals::SCREEN_MENU_WIDTH, Globals::SCREEN_MENU_HEIGHT);
    return success;
}

void close()
{
    SDL_DestroyRenderer(Globals::g_Renderer);
    SDL_DestroyWindow(Globals::g_Window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char* args[])
{
if (!init())
{
    cout << "Failed to initialize SDL" << endl;
}else
    {
        if (!RenderWindow())
        {
            cout << "Failed to create window or renderer" << endl;
        }else
        {

    // Tao game Menu
    // Load Texture
    SDL_Texture* background = loadMenuTexture(Globals::g_Renderer, "assets/Menu/arcane-2 - Copy.jpg"); //nap background
    SDL_Texture* playButton = loadMenuTexture(Globals::g_Renderer, "assets/Menu/play.png"); //nap nut play
    SDL_Texture* quitButton = loadMenuTexture(Globals::g_Renderer, "assets/Menu/quit.png"); //nap nut quit
    SDL_Texture* title = loadMenuTexture(Globals::g_Renderer, "assets/Menu/title2.png"); //nap tieu de
    SDL_Texture* tutorialButton = loadMenuTexture(Globals::g_Renderer, "assets/Menu/tutor.png");
    SDL_Texture* tutorialBackgroud = loadMenuTexture(Globals::g_Renderer, "assets/Menu/tutorialBackground.jpg");

    // Khoi tao everything trong menu
    Menu backgroundLayer (background,Globals::BACKGROUND_X,Globals::BACKGROUND_Y, Globals::BACKGROUND_WIDTH,Globals::BACKGROUND_HEIGHT); //khoi tao background
    Menu titleButton(title,Globals::TITLE_X,Globals::TITLE_Y,Globals::TITLE_WIDTH,Globals::TITLE_HEIGHT); //khoi tao tieu de
    Menu play(playButton,Globals::PLAY_X,Globals::PLAY_Y,Globals::PLAY_WIDTH,Globals::PLAY_HEIGHT);
    Menu quit(quitButton,Globals::QUIT_X,Globals::QUIT_Y,Globals::QUIT_WIDTH,Globals::QUIT_HEIGHT);
    Menu tutorial(tutorialButton,Globals::TUTOR_X,Globals::TUTOR_Y ,Globals::TUTOR_WIDTH,Globals::TUTOR_HEIGHT);


    // tao 1 cai hop de test, hop nay cung kich thuoc voi cac nut
    SDL_Rect playRect = play.getRect();
    SDL_Rect quitRect = quit.getRect();
    SDL_Rect tutorialRect = tutorial.getRect();
    enum gameState currentState = MENU; // set trang thai hien tai
    bool gameRunning = true;
    SDL_Event e;
    while (gameRunning)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (currentState == MENU) // Khi ma currentState la menu thi moi cho phep lay toa do chuot va check cac vi tri nut
                {
                int x,y;
                SDL_GetMouseState(&x, &y);
                if (x >= playRect.x && x <= playRect.x + playRect.w && y >= playRect.y && y <= playRect.y + playRect.h)
                {
                    currentState = PLAY;
                }
                else if (x >= tutorialRect.x && x <= tutorialRect.x + tutorialRect.w && y >= tutorialRect.y && y <= tutorialRect.y + tutorialRect.h)
                {
                    currentState = TUTORIAL;
                }
                else if (x >= quitRect.x && x <= quitRect.x + quitRect.w && y >= quitRect.y && y <= quitRect.y + quitRect.h)
                {
                    gameRunning = false;
                    break;
                }
            }
                if (currentState == TUTORIAL)
                {
                    SDL_RenderCopy(Globals::g_Renderer, tutorialBackgroud, nullptr, nullptr);
                    SDL_RenderPresent(Globals::g_Renderer);
                    SDL_Rect tutorialQuit = {40,32,120,125};
                    int x,y;
                    SDL_GetMouseState(&x, &y);
                    if (x >= tutorialQuit.x && x <= tutorialQuit.x + tutorialQuit.w && y >= tutorialQuit.y && y <= tutorialQuit.y + tutorialQuit.h)
                    {
                        currentState = MENU;
                        SDL_RenderClear(Globals::g_Renderer);
                    }

                }
            }
        }
        if (currentState == MENU)
        {
            // In ra man hinh
            backgroundLayer.Render(Globals::g_Renderer); // in ra background
            titleButton.Render(Globals::g_Renderer); // in ra tieu de
            play.Render(Globals::g_Renderer);
            quit.Render(Globals::g_Renderer);
            tutorial.Render(Globals::g_Renderer);
            SDL_RenderPresent(Globals::g_Renderer);
        }
        if (currentState == PLAY)
        {
            SDL_DestroyWindow(Globals::g_Window);
            SDL_DestroyRenderer(Globals::g_Renderer);
            SDL_DestroyTexture(background);
            SDL_DestroyTexture(playButton);
            SDL_DestroyTexture(quitButton);
            SDL_DestroyTexture(title);
            SDL_DestroyTexture(tutorialButton);
            SDL_DestroyTexture(tutorialBackgroud);
            Game game;
            game.Run(gameRunning);
            return 0;
        }

        SDL_Delay(100);
    }
        }
    }
    close();
    return 0;
}