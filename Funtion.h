#ifndef FUNTION_H_
#define FUNTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <SDL_mixer.h>
#include <vector>
#include <ctime>
#include <SDL_ttf.h>
#include <cstdlib>

using namespace std;

#define MAX_HEIGHT 300


#define ENEMY_POSITION_RANGE 300

//#define BASE_OFFSET_SPEED 0

#define IN_AIR_ENEMY 1
#define ON_GROUND_ENEMY 0

#define GROUND_SPEED 0
#define ENEMY_SPEED 1

#define MAX_ENEMY_WIDTH 100

#define TIME_INCREASEMENT 1
#define TIME_MAX 1000
#define SPEED_INCREASEMENT 1

#define SLOW_FRAME_CHAR 4
#define SLOW_FRAME_ENEMY 4

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2



const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 785;
const int BPP = 32;
static const int GROUND = 630;
const double BACKGROUND_SPEED = -5;
const int FLYING_FRAME = 4;
const int ENEMY_MAX_HEIGHT = 320;
const int ENEMY_MIN_HEIGHT = 500;

const int COMMON_BUTTON_WIDTH = 150;
const int COMMON_BUTTON_HEIGHT = 98;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;

const int PLAY_BUTON_POSX = 389;
const int PLAY_BUTTON_POSY= 186;
const int HELP_BUTTON_POSX = 389;
const int HELP_BUTTON_POSY = 293;
const int EXIT_BUTTON_POSX = 389;
const int EXIT_BUTTON_POSY = 402;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;

enum ButtonSprite
{
    BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};
/*
Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
*/
bool init();

//tải media
bool loadMedia();

//giải phóng media và thoát SDL
void close();


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;

SDL_Rect* gSpriteClips[BUTTON_TOTAL];

Mix_Chunk* gJump = NULL;
Mix_Chunk* gDie = NULL;
Mix_Chunk* gMenu = NULL;
Mix_Chunk* gClick = NULL;


#endif
