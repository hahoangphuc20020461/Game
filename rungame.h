#ifndef RUNGAME_H_
#define RUNGAME_H_

#include "Funtion.h"
#include "Move.h"
#include "Enemy.h"
#include "LTexture.h"

bool checkCollision(Skate character, Enemy enemy);
bool checkAllCollision(Skate character, Enemy enemyXuongrong, Enemy enemyUfo);
void drawEndGame(LTexture gLoseTexture, bool& play_again);
int UpdateVelocity(int& time, int& speed);


bool checkCollision(Skate character, Enemy enemy)
{
    bool collide = false;
    int Xa1 = character.GetPosX();
    int Xa2 = character.GetPosX() + 47;
    int Ya1 = character.GetPosY();
    int Ya2 = character.GetPosY() + 65;

    int Xb1 = enemy.GetPosX();
    int Xb2 = enemy.GetPosX() + enemy.GetWidth() ;
    int Yb1 = enemy.GetPosY();
    int Yb2 = enemy.GetPosY() + enemy.GetHeight() ;

    if(enemy.GetType() == ON_GROUND_ENEMY){
        if(Xa2 - 20 >= Xb1 && Xa1 + 20 <= Xb2){
            if(Ya2 - 15 >= Yb1){
                collide = true;
            }
        }
    }
    else{
        if(Xa2 >= Xb1 + 7 && Xa1 <= Xb2 ){
            if(Ya1 + 10 <= Yb2 && Ya2 - 7 >= Yb1){
                collide = true;
            }
            if(Ya2 >= Yb2 && Ya2 <= Yb1){
                collide = true;
            }
        }
    }
    return collide;
}

bool checkAllCollision(Skate character, Enemy enemyXuongrong, Enemy enemyUfo)
{
    if(checkCollision(character, enemyXuongrong)||checkCollision(character,enemyUfo)){
        return true;
    }
    return false;
}

void drawEndGame(LTexture gLoseTexture, bool& play_again)
{
if(play_again)
  {
    gLoseTexture.render(0,0);
    SDL_RenderPresent(gRenderer);
   }
}

int UpdateVelocity(int& time,double& speed)
{
	if (time == TIME_MAX)
	{
		speed += SPEED_INCREASEMENT;
	}
	if (time > TIME_MAX)
	{
		time = 0;
	}
	time += TIME_INCREASEMENT;

	return time;
}


#endif // RUNGAME_H_
