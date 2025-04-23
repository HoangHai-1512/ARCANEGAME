//
// Created by MSI GF63 on 4/18/2025.
//

#include "Globals.h"
// Menu
 SDL_Window* Globals::g_Window = nullptr;
 SDL_Renderer* Globals::g_Renderer = nullptr;
  int Globals::SCREEN_MENU_WIDTH = 1407, Globals::SCREEN_MENU_HEIGHT = 745;
  int Globals::BACKGROUND_X = 0, Globals::BACKGROUND_Y = 0, Globals::BACKGROUND_WIDTH = 1407, Globals::BACKGROUND_HEIGHT = 745;
  int Globals::PLAY_X = 900 , Globals::PLAY_Y = 360, Globals::PLAY_WIDTH = 256 , Globals::PLAY_HEIGHT = 127;
  int Globals::QUIT_X = 925, Globals::QUIT_Y = 610, Globals::QUIT_WIDTH = 206, Globals::QUIT_HEIGHT = 90;
  int Globals::TITLE_X = 650, Globals::TITLE_Y = 100, Globals::TITLE_WIDTH = 760, Globals::TITLE_HEIGHT = 200;
  int Globals::TUTOR_X = 900, Globals::TUTOR_Y = 500, Globals::TUTOR_WIDTH = 251, Globals::TUTOR_HEIGHT = 95;

// Game
int Globals::SCREEN_GAME_WIDTH = 1550, Globals::SCREEN_GAME_HEIGHT = 885;
const Uint32 Globals::timeBoss = 60000;