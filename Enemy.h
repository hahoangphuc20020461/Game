#ifndef ENEMY_H_
#define ENEMY_H_

#include "LTexture.h"
#include "Funtion.h"

#define ENEMY1_RANGE 100
#define ENEMY2_RANGE 350

class Enemy
{
public:

    Enemy(int _type);

    ~Enemy();

    //load ảnh enemy
   void LoadFromFile(std::string path);

   //làm enemy trượt qua màn hình
	void Move(const int& acceleration);

	void Render( SDL_Renderer* gRenderer ,SDL_Rect* clip);
	//kiểu enemy
	int GetType();
	//tốc độ của enemy
	int GetSpeed(const int& acceleration);

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();

private:
    SDL_Texture* eTexture;

    int ePosX, ePosY;

    int eWidth, eHeight;

    int status;

};

Enemy::Enemy(int _type)
{
	ePosX = 0;
	ePosY = 0;

	eWidth = 0;
	eHeight = 0;

	status = _type;
	if (status == IN_AIR_ENEMY)
	{
		ePosX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		ePosY =  rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;
	}
	else if (status == ON_GROUND_ENEMY)
	{
		ePosX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		ePosY = 630;
	}

	eTexture = NULL;
}

Enemy::~Enemy()
{
	ePosX = 0;
	ePosY = 0;

	eWidth = 0;
	eHeight = 0;

	status = 0;
	if (eTexture != NULL)
	{
		eTexture = NULL;
	}
}

void Enemy::LoadFromFile(std::string path)
{
	SDL_Texture* tmpTexture = NULL;

	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	if (tmpSurface == NULL)
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == NULL)
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			eWidth = tmpSurface->w;
			eHeight = tmpSurface->h;
		}

		SDL_FreeSurface(tmpSurface);
	}

	eTexture = tmpTexture;
}

void Enemy::Move(const int &acceleration)
{
	ePosX += -(ENEMY_SPEED + acceleration);
	if ((ePosX + MAX_ENEMY_WIDTH < 0))
	{
		ePosX =  rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;

		if (status == IN_AIR_ENEMY)
		{
			ePosY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;
		}
	}
}

void Enemy::Render( SDL_Renderer* gRenderer, SDL_Rect* clip)
{
	SDL_Rect renderSpace = { ePosX, ePosY, eWidth, eHeight };
	if (clip != NULL)
	{
		renderSpace.w = clip->w;
		renderSpace.h = clip->h;
	}
	SDL_RenderCopy(gRenderer ,eTexture, clip ,&renderSpace);
}

int Enemy::GetType()
{
	if (status == IN_AIR_ENEMY)
	{
		return IN_AIR_ENEMY;
	}
	else
	{
		return ON_GROUND_ENEMY;
	}
}

int Enemy::GetSpeed(const int &acceleration)
{
	return ENEMY_SPEED + acceleration;
}

int Enemy::GetPosX()
{
	return ePosX;
}

int Enemy::GetPosY()
{
	return ePosY;
}

int Enemy::GetWidth()
{
	return eWidth;
}

int Enemy::GetHeight()
{
	return eHeight;
}
 #endif
