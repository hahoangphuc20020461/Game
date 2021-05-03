#ifndef TIMER_H_
#define TIMER_H_

#include "LTexture.h"
#include "Funtion.h"

class LTimer
{
    public:
		LTimer();

		void start();

		Uint32 getTicks();

		bool isStarted();


    private:
		Uint32 mStartTicks;

		bool mStarted;
};

LTimer::LTimer()
{
    mStartTicks = 0;

    mStarted = false;
}

void LTimer::start()
{
    mStarted = true;

    mStartTicks = SDL_GetTicks();

}

Uint32 LTimer::getTicks()
{
	Uint32 time = 0;

    if( mStarted )
    {
        time = SDL_GetTicks();
    }

    return time;
}

bool LTimer::isStarted()
{
    return mStarted;
}



#endif // TIMER_H_
