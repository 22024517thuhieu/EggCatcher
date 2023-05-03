#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include "SDL.h"
#include "SDL_image.h"
#include "windows.h"
#include <string>
#include <iostream>
#include "SDL_mixer.h"
#include "time.h"
#include "SDL_ttf.h"


#define  SCREEN_WIDTH 800
#define  SCREEN_HEIGHT 600
#define  SCREEN_BPP 32
const int NUM_OBSTACLE = 3;
const int NUM_BOMB = 1;
const int x1 = 248;
const int x2 = 448;
const int x3 = 648;
const int SPEED_EGG  = 1;
const int NUM_ROWS = 3;

static SDL_Window* g_window;
static SDL_Renderer* g_screen;
static SDL_Event g_event;
static Mix_Music* g_sound = NULL;


namespace SDLCommonFunc
{
	bool CheckCollision(const SDL_Rect *object1, const SDL_Rect *object2);
	int getRandomNumber(int a, int b);
	bool CheckFocusWithRect(int x1, int y1, int x, int y, int w, int h);
}

#endif // COMMON_FUNCTION_H