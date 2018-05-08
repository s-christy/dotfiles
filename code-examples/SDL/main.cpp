#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int NUM_SURFACES=4;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld[NUM_SURFACES];

bool init()
{
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

SDL_Surface* loadSurface( std::string path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

void close()
{
	//Deallocate surface
	for(int i=0;i<NUM_SURFACES;i++){
		SDL_FreeSurface( gHelloWorld[i] );
		gHelloWorld[i] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	init();
	gHelloWorld[0]=loadSurface("resources/1.png");
	gHelloWorld[1]=loadSurface("resources/2.png");
	gHelloWorld[2]=loadSurface("resources/3.png");
	gHelloWorld[3]=loadSurface("resources/4.png");

	int currentSurface=0;
	bool run=true;
	SDL_Event e;
	while(run){
		while(SDL_PollEvent(&e)!=0){
			if(e.type==SDL_QUIT){
				run=false;
			}
			if(e.type==SDL_KEYDOWN){
				currentSurface=(currentSurface+1)%NUM_SURFACES;
			}
		}
		SDL_BlitSurface( gHelloWorld[currentSurface], NULL, gScreenSurface, NULL );
		SDL_UpdateWindowSurface( gWindow );
	}

	close();

	return 0;
}
