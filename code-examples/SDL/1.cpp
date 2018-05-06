#include <SDL.h>
#include <stdio.h>
#include <iostream>

void init(){
	//init sdl
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
}

void create_window(win){
	//create window
	*win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
}

//void create_renderer(SDL_Window *win){
//	//create renderer
//	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//	if (ren == nullptr){
//		SDL_DestroyWindow(win);
//		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
//		SDL_Quit();
//	}
//}
//
//void load_image(SDL_Window *win){
//	//load image
//	std::string imagePath="//home//sam//Downloads//1523547110_map.bmp";
//	SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
//	if (bmp == nullptr){
//		SDL_DestroyRenderer(ren);
//		SDL_DestroyWindow(win);
//		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
//		SDL_Quit();
//	}
//}
//
//void create_texture(SDL_Window *win){
//	//create texture from bitmap
//	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
//	SDL_FreeSurface(bmp);
//	if (tex == nullptr){
//		SDL_DestroyRenderer(ren);
//		SDL_DestroyWindow(win);
//		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
//		SDL_Quit();
//	}
//}
//
//void display(){
//	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
//	for (int i = 0; i < 3; ++i){
//		//First clear the renderer
//		SDL_RenderClear(ren);
//		//Draw the texture
//		SDL_RenderCopy(ren, tex, NULL, NULL);
//		//Update the screen
//		SDL_RenderPresent(ren);
//		//Take a quick break after all that hard work
//		SDL_Delay(1000);
//	}
//}

int main(int, char**){
	init();
	SDL_Window *win;
	create_window(win);
	//create_renderer(win);
	//load_image(win);
	//create_texture(win);
	//display();
	//SDL_DestroyTexture(tex);
	//SDL_DestroyRenderer(ren);
	//SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
