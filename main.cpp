#include "Funtion.h"
#include "LTexture.h"
#include "Move.h"
#include "timer.h"
#include "Enemy.h"
//#include "rungame.h"
//#include "button.h"

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
				//Khởi tạo màu
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//khởi tạo PNG
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				 //Khởi tao SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				//Khởi tạo âm thanh
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
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

	if( !gUfoTexture.loadFromFile( "img/eufo.png" ) )
	{
		printf( "Failed to load cactus' texture image!\n") ;
		success = false;
	}

	//Load music
	gJump = Mix_LoadWAV( "img/jump.wav" );
	if( gJump == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
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
	gPlayButtonTexture.free();
	//gHelpButtonTexture.free();
	//gExitButtonTexture.free();
	//gBackButtonTexture.free();
	//gInstructionTexture.free();
	//gMenuTexture.free();


	TTF_CloseFont( gFont );
	gFont = NULL;

	Mix_FreeChunk(gJump);
	gJump = NULL;

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
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

			Enemy enemyXuongrong(0);
			Enemy enemyUfo(1);

			srand(time(NULL));

			double scrollingOffset = 0;
			int acceleration = 0;
			int frame_enemy = 0;

             timer.start();

			while( !quit )
			{
				//Thao tác từ bàn phím
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                }

				timeText.str( "" );
				timeText << "Play time " << ( timer.getTicks() / 1000.f );
				timeText << "  Score: " <<(timer.getTicks()/4000.f);

				if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time texture!\n" );
				}

					skate.handleEvent( e );

				//di chuyển nhân vật
				skate.move();

				//Cuận màn hình
				scrollingOffset -= GROUND_SPEED + 1 ;
				if( scrollingOffset < -gBackgroundTexture.getWidth() )
				{
					scrollingOffset = 0;
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );


				//Render BackgroundTexture lên màn hình
				gBackgroundTexture.render( scrollingOffset, 0 );
				gBackgroundTexture.render(scrollingOffset + gBackgroundTexture.getWidth(), 0);

				gTimeTextTexture.render( ( SCREEN_WIDTH - gTimeTextTexture.getWidth() ) / 2 - 15, 5 );

				//Render skate lên màn hình
				skate.render();

                SDL_Rect* eclip = NULL;
                SDL_Rect* skclip = NULL;

                enemyXuongrong.LoadFromFile("img/cactus1.png");
                enemyXuongrong.Move(acceleration);
                enemyXuongrong.Render(gRenderer, eclip);

                enemyUfo.LoadFromFile("img/eufo.png");
                enemyUfo.Move(acceleration);
                enemyUfo.Render(gRenderer, eclip);

				SDL_RenderPresent( gRenderer );

            }
        }
	}
            close();

	return 0;
}




