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

#define BASE_OFFSET_SPEED 0

#define IN_AIR_ENEMY 1
#define ON_GROUND_ENEMY 0

#define GROUND_SPEED 0
#define ENEMY_SPEED 1

#define MAX_ENEMY_WIDTH 100

#define TIME_INCREASEMENT 1
#define TIME_MAX 4000



#define SMALL_BUTTON 1
#define COMMON_BUTTON 2



const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 785;
const int BPP = 32;
static const int GROUND = 630;
const double BACKGROUND_SPEED = -5;
const int FLYING_FRAME = 4;
const int ENEMY_MAX_HEIGHT = 320;
const int ENEMY_MIN_HEIGHT = 490;

double SPEED_INCREASEMENT = 0.5;


bool init();

//tải media
bool loadMedia();

//giải phóng media và thoát SDL
void close();


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;


Mix_Chunk* gJump = NULL;
Mix_Chunk* gDie = NULL;
Mix_Music* gMenu = NULL;
Mix_Music* gMusic = NULL;
Mix_Chunk* gClick = NULL;


#endif
