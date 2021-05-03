#ifndef MOVE_H_
#define MOVE_H_
#include "LTexture.h"

#define JUMP 1
#define FALL 2


class Skate
{
    public:
		//vận tốc khi nhảy
		 double JUMP_VEL = 1.1;
		 double FALL_VEL = 2;

		Skate();

		bool OnGround();

		void move();

		void handleEvent( SDL_Event& e );

		//hiển thị nhân vật ra màn hình
		void render();

		int GetPosX();

	    int GetPosY();


    private:
		//tọa độ của nhân vật
		int mPosX, mPosY;

		//trạng thái của nhân vật
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
    //thiết lập trạng thái phím bấm
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                {
                if(OnGround()){
                    Mix_PlayChannel(-1,gJump,0);
                    status = JUMP;
                    break;
                }
            }
        }
    }

}

void Skate::move()
{
    //thiết lập trang thái nhảy lên hạ xuống
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

int Skate::GetPosX()
{
    return mPosX;
}

int Skate::GetPosY()
{
    return mPosY;
}


#endif // MOVE_H_
