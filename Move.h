#ifndef MOVE_H_
#define MOVE_H_
#include "LTexture.h"

#define JUMP 1
#define FALL 2


class Skate
{
    public:
		 double  JUMP_VEL = 0.5;
		 double FALL_VEL = 1;

		Skate();

		bool OnGround();

		void handleEvent( SDL_Event& e );

		void move();

		void render();

    private:
		int mPosX, mPosY;

		double status ;

};

Skate::Skate()
{
    mPosX = SCREEN_WIDTH - 900;
    mPosY = 630;

    status = 0;
}

void Skate::handleEvent( SDL_Event& e )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                {
                if(OnGround()){
                    status = JUMP;
                }
            }
        }
    }

}

void Skate::move(){

    if( status == JUMP&&mPosY >= MAX_HEIGHT )
    {
        mPosY += -JUMP_VEL;
    }
    if(mPosY <=MAX_HEIGHT)
    {
        status = FALL;
    }
    if(status == FALL&& mPosY < GROUND)
    {
        mPosY += FALL_VEL;
    }
}

void Skate::render()
{
	gCharTexture.render( mPosX, mPosY );
}

bool Skate::OnGround()
{
   return mPosY = GROUND;
}

#endif // MOVE_H_
