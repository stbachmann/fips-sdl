//#include <stdio.h>
#define SDL_MAIN_HANDLED
#include "SDL.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("SDL Window", 150, 150, 800, 600, SDL_WINDOW_SHOWN);

	SDL_Delay(5000);

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}