//
// Created by MSI GF63 on 4/18/2025.
//

#ifndef GLOBALS_H
#define GLOBALS_H
#include <SDL.h>


class Globals {
public:
    // Menu
    static SDL_Window* g_Window;
    static SDL_Renderer* g_Renderer;
    static  int SCREEN_MENU_WIDTH, SCREEN_MENU_HEIGHT;
    static  int BACKGROUND_X, BACKGROUND_Y, BACKGROUND_WIDTH, BACKGROUND_HEIGHT;
    static  int PLAY_X, PLAY_Y, PLAY_WIDTH, PLAY_HEIGHT;
    static  int QUIT_X, QUIT_Y, QUIT_WIDTH, QUIT_HEIGHT;
    static  int TITLE_X, TITLE_Y, TITLE_WIDTH, TITLE_HEIGHT;
    static int TUTOR_X, TUTOR_Y, TUTOR_WIDTH, TUTOR_HEIGHT;

    //Game
    static  int SCREEN_GAME_WIDTH, SCREEN_GAME_HEIGHT;
    static const Uint32 timeBoss ;

};



#endif //GLOBALS_H
