#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer *ren;
SDL_Texture* texture;

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}


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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_SHOWN );
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
	ren=SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	return success;
}

int main( int argc, char* args[] )
{
	init();
	texture=IMG_LoadTexture(ren, "/home/sam/s-christy/dotfiles/code-examples/SDL/resources/1.png");

	bool run=true;
	SDL_Event e;
	while(run)
	{
		while(SDL_PollEvent(&e)!=0)
		{
			if(e.type==SDL_QUIT)
			{
				run=false;
			}
			if(e.type==SDL_KEYDOWN)
			{
			}
		}
		renderTexture(texture, ren, 10,10,200,200);
		SDL_RenderPresent(ren);
		SDL_UpdateWindowSurface( gWindow );
	}
	return 0;
}
