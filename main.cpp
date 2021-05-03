#include "Funtion.h"
#include "LTexture.h"
#include "Move.h"
#include "timer.h"
#include "Enemy.h"
#include "rungame.h"

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
		printf ("Failed to load Skate texture image!\n" ) ;
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
		printf ("Failed to load cactus' texture image!\n" );
		success = false;
	}

	if( !gUfoTexture.loadFromFile( "img/eufo1.png" ) )
	{
		printf( "Failed to load cactus' texture image!\n") ;
		success = false;
	}
	if(!gLoseTexture.loadFromFile("img/lose1.png") )
    {
        printf( "Failed to load gameover' texture image!\n") ;
		success = false;
    }
    if(!gMenuTexture.loadFromFile("img/menu2.png") )
    {
        printf( "Failed to load menu' texture image!\n") ;
		success = false;
    }

	//Load music
	gMusic = Mix_LoadMUS("img/music_backgr.wav" );
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMenu = Mix_LoadMUS("img/menuavenger.wav" );
	if( gMenu == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gJump = Mix_LoadWAV( "img/jump.wav" );
	if( gJump == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gDie = Mix_LoadWAV("img/oidoioi.wav");
	if( gDie == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gClick = Mix_LoadWAV("img/click.wav" );
	if( gClick == NULL )
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
	gLoseTexture.free();
	gPlayButtonTexture.free();
	gMenuTexture.free();


	TTF_CloseFont( gFont );
	gFont = NULL;

	Mix_FreeChunk(gJump);
	Mix_FreeChunk(gDie);
	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenu);
	Mix_FreeChunk(gClick);
	gMusic = NULL;
	gMenu = NULL;
	gJump = NULL;
	gDie = NULL;
	gClick = NULL;

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
		    bool quit_menu = false;
		    bool play_again = false;
		    Mix_PlayMusic(gMenu, -1);

		    LTimer timer;

		    while( !quit_menu )
            {
                SDL_Event e_key;
                while(SDL_PollEvent(&e_key) != 0)
                {
                    if (e_key.type == SDL_QUIT)
					{
						quit_menu = true;
					}
					if (e_key.type == SDL_KEYDOWN)
                    {
                        switch( e_key.key.keysym.sym)
                        {
                        case SDLK_s :
                            {
                                Mix_PlayChannel(-1, gClick, 0);
                                play_again = true;
                                timer.start();
                            }
                        case SDLK_ESCAPE:
                            {
                                quit_menu = true;
                            }
                        }
                    }
                }
             gMenuTexture.render(0,0);
             SDL_RenderPresent(gRenderer);
            }
            while(play_again)
        {
            bool quit = false;
            bool game_state = true;
			SDL_Event e;

			//Set màu của text
			SDL_Color textColor = { 0, 0, 0, 255 };



            std::stringstream timeText;

			Skate skate;

			Enemy enemyXuongrong(0);
			Enemy enemyUfo(1);

			srand(time(NULL));

			Mix_PlayMusic(gMusic, -1);

            double scrollingOffset ;
			double acceleration = 0;

			int time = 0;


			while( !quit )
        {
			    if(game_state){
                UpdateVelocity(time, acceleration);

				//Thao tác từ bàn phím
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                }

				timeText.str( "" );

				int score = timer.getTicks()/4000.f;

				timeText << "  Score: " <<( score );

				if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time texture!\n" );
				}

					skate.handleEvent( e );

				//di chuyển nhân vật
				skate.move();

				//Cuận màn hình

				scrollingOffset -= GROUND_SPEED + 0.8 ;
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

                enemyXuongrong.LoadFromFile("img/cactus1.png");
                enemyXuongrong.Move(acceleration);
                enemyXuongrong.Render(gRenderer, eclip);
                enemyXuongrong.GetSpeed(1);

                enemyUfo.LoadFromFile("img/eufo1.png");
                enemyUfo.Move(acceleration);
                enemyUfo.Render(gRenderer, eclip);
                enemyUfo.GetSpeed(1);

                if(checkAllCollision(skate, enemyXuongrong, enemyUfo)){
                    Mix_PauseMusic();
                    Mix_PlayChannel(-1, gDie, 0);
                    quit = false;
                    while(!quit){
                    while( SDL_PollEvent( &e ) != 0 )
				   {
					 if( e.type == SDL_KEYDOWN)
         {
             switch( e.key.keysym.sym )
            {
             case SDLK_ESCAPE:
                 {
                     play_again = false;
                     quit = true;
                 }
            }
         }
                   }
                        drawEndGame(gLoseTexture, play_again);
                    }
                }

                SDL_RenderPresent( gRenderer );
                    }
                }
            }

        }
	}
            close();

	return 0;
}




