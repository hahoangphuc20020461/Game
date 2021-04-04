#include "Funtion.h"
#include "LTexture.h"
#include "Move.h"
#include "timer.h"

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Skateboard Jump", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	gFont = TTF_OpenFont( "img/font.ttf", 12 );
	if( gFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };

		//Load stop prompt texture
		if( !gStartPromptTexture.loadFromRenderedText( "Press S to Start or Stop the Timer", textColor ) )
		{
			printf ("Unable to render start/stop prompt texture!\n") ;
			success = false;
		}

		//Load pause prompt texture
		if( !gPausePromptTexture.loadFromRenderedText( "Press P to Pause or Unpause the Timer", textColor ) )
		{
			printf ("Unable to render pause/unpause prompt texture!\n") ;
			success = false;
		}
	}
	//Load character texture
	if( !gCharTexture.loadFromFile( "img/sk.png" ) )
	{
		printf ("Failed to load Skate texture image!\n") ;
		success = false;
	}

	//Load background texture
	if( !gBackgroundTexture.loadFromFile( "img/background.png" ) )
	{
		printf ("Failed to load background texture image!\n") ;
		success = false;
	}
// Load Enemy texture
	if( !gCactusTexture.loadFromFile( "img/cactus1.png" ) )
	{
		printf ("Failed to load cactus' texture image!\n");
		success = false;
	}

	if( !gUfoTexture.loadFromFile( "img/ufo1.png" ) )
	{
		printf( "Failed to load cactus' texture image!\n") ;
		success = false;
	}

	return success;
}

void close()
{
	gCharTexture.free();
	gBackgroundTexture.free();
	gCactusTexture.free();
	gUfoTexture.free();
	gTimeTextTexture.free();
	gStartPromptTexture.free();
	gPausePromptTexture.free();


	TTF_CloseFont( gFont );
	gFont = NULL;


	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* argv[] )
{
	//Khởi tạo SDL và window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			//Set màu của text
			SDL_Color textColor = { 0, 0, 0, 255 };
            LTimer timer;
            std::stringstream timeText;

			Skate skate;

			srand(time(NULL));
			double scrollingOffset = 0;
			int time = 0;
			int acceleration = 0;
			while( !quit )
			{
				//Thao tác từ bàn phím
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN )
					{
						//Start/stop
						if( e.key.keysym.sym == SDLK_s )
						{
							if( timer.isStarted() )
							{
								timer.stop();
							}
							else
							{
								timer.start();
							}
						}
						//Pause/unpause
						else if( e.key.keysym.sym == SDLK_p )
						{
							if( timer.isPaused() )
							{
								timer.unpause();
							}
							else
							{
								timer.pause();
							}
						}
					}
				}

				timeText.str( "" );
				timeText << "Seconds since start time " << ( timer.getTicks() / 100.f ) ;
				if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time texture!\n" );
				}
					skate.handleEvent( e );

				//di chuyển nhân vật
				skate.move();


				//Cuận màn hình
				scrollingOffset -= GROUND_SPEED + 0.5 ;
				if( scrollingOffset < -gBackgroundTexture.getWidth() )
				{
					scrollingOffset = 0;
				}


				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				gStartPromptTexture.render( ( SCREEN_WIDTH - gStartPromptTexture.getWidth() ) / 2, 0 );
				gPausePromptTexture.render( ( SCREEN_WIDTH - gPausePromptTexture.getWidth() ) / 2, gStartPromptTexture.getHeight() );
				gTimeTextTexture.render( ( SCREEN_WIDTH - gTimeTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTimeTextTexture.getHeight() ) / 2 );

				//Render BackgroundTexture lên màn hình
				gBackgroundTexture.render( scrollingOffset, 0 );
				gBackgroundTexture.render(scrollingOffset + gBackgroundTexture.getWidth(), 0);


				//Render skate lên màn hình
				skate.render();

				int airX, airY;
				int groundX, groundY;
                // Tạo vị trí ngẫu nhiên xuất hiện chướng ngại vật
				airX = SCREEN_WIDTH/2 + rand() % (SCREEN_WIDTH + 1 - SCREEN_WIDTH/2);
				airY = ENEMY_MIN_HEIGHT + rand() % (ENEMY_MAX_HEIGHT + 1 - ENEMY_MIN_HEIGHT);

				groundX = SCREEN_WIDTH/2 + rand() % (SCREEN_WIDTH + 150 - SCREEN_WIDTH/2);
				groundY = 630;

                     //gUfoTexture.render(airX, airY); //480
				gUfoTexture.render(scrollingOffset + airX, airY);
				gUfoTexture.render(scrollingOffset + gBackgroundTexture.getWidth(),airY);

                // gCactusTexture.render(groundX, groundY);
                gCactusTexture.render( scrollingOffset + groundX ,groundY);
				gCactusTexture.render(scrollingOffset + gBackgroundTexture.getWidth() ,groundY);

				SDL_RenderPresent( gRenderer );
			   }
            }
		}

	close();

	return 0;
}

