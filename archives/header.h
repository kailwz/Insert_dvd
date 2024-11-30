#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define WIDTH 940
#define HEIGHT 720

SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;
SDL_Surface *img = NULL;
SDL_Texture *tex = NULL;
SDL_Event event;

typedef struct {
	int size, i;
	float x, y;
	float xSpeed, ySpeed;
	char *colors[3];
} DVD;

