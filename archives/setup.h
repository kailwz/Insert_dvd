#include "header.h"

bool coinFlip () {
	return rand() % 2 == 1 ? true : false;
}

void playMusic () {
	Mix_Music *music = Mix_LoadMUS("../music/audio.mp3");
	Mix_VolumeMusic(80);
	Mix_PlayMusic(music, -1);
}

void playSound () {
	Mix_Chunk *sound = Mix_LoadWAV("../music/sound.wav");
	Mix_VolumeChunk(sound, 20);
	Mix_PlayChannel(-1, sound, 0);
}

void dvdConfig (DVD *dvd) {
	const float SPEED = 120;
	dvd->i = 0;
	dvd->size = 100;
	dvd->x = (WIDTH/2)-(dvd->size/2);
	dvd->y = (HEIGHT/2)-(dvd->size/2);
	dvd->xSpeed = SPEED * (coinFlip() ? 1 : -1);
	dvd->ySpeed = SPEED * (coinFlip() ? 1 : -1);
	dvd->colors[0] = "../images/red.png";
	dvd->colors[1] = "../images/blue.png";
	dvd->colors[2] = "../images/green.png";
}

void movement (DVD *dvd, float elapsed) {
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	dvd->x += dvd->xSpeed * elapsed;
	dvd->y += dvd->ySpeed * elapsed;
}

void drawRect (DVD *dvd, float elapsed) {
	SDL_SetRenderDrawColor(ren, 10, 10, 10, 255);
	SDL_RenderClear(ren);
	   
	movement(dvd, elapsed);

	SDL_Rect dvdRect = {dvd->x, dvd->y, dvd->size, dvd->size};
	SDL_RenderCopy(ren, tex, NULL, &dvdRect);

	SDL_RenderPresent(ren);
}

void drawImg (DVD *dvd) {
	img = IMG_Load(dvd->colors[dvd->i]);
	if (img == NULL) {
		printf("Cannot find dvd image!\n");
		SDL_Quit();
		exit(1);
	}

	tex = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
}

void collision (DVD *dvd) {
	int wh = WIDTH - (dvd->size-10);
	int hg = HEIGHT - (dvd->size-10);

	if (dvd->x>=wh) {
		playSound();
		dvd->xSpeed = -fabs(dvd->xSpeed);
		dvd->i++;
		if (dvd->i>2) {
			dvd->i=0;
		}
		drawImg(dvd);
	}
	else if (dvd->y>=hg) {
		playSound();
		dvd->ySpeed = -fabs(dvd->ySpeed);
		dvd->i++;
		if (dvd->i>2) {
			dvd->i=0;
		}
		drawImg(dvd);
	}
	if (dvd->x<=-10) {
		playSound();
		dvd->xSpeed = fabs(dvd->xSpeed);
		dvd->i++;
		if (dvd->i>2) {
			dvd->i=0;
		}
		drawImg(dvd);
	}
	else if (dvd->y<=-10) {
		playSound();
		dvd->ySpeed = fabs(dvd->ySpeed);
		dvd->i++;
		if (dvd->i>2) {
			dvd->i=0;
		}
		drawImg(dvd);
	}
}

void window () {
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 1024);
	win = SDL_CreateWindow("Insert - DVD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!win) {
		printf("Window could not be created\n");
	}
	else if (!ren) {
		printf("Renderer could not be created\n");
	}
}

void gameLoop (DVD *dvd) {
	int loop=1;
	Uint32 lastTick = SDL_GetTicks();

	playMusic();
	playSound();
	while (loop) {
	    collision(dvd);
	    while (SDL_PollEvent(&event)) {
		    switch (event.type) {
			    case SDL_QUIT:
			    {
				    loop=0;
				    break;
			    }
		    }
	    }
	    Uint32 curTick = SDL_GetTicks();
	    Uint32 diff = curTick - lastTick;
	    float elapsed = diff / 1000.0f;
	    drawRect(dvd, elapsed);
	    lastTick = curTick;
	}
}

void finishOff () {
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	
	Mix_HaltMusic();
	Mix_CloseAudio();
	Mix_Quit();

	IMG_Quit();
	SDL_Quit();
	exit(0);
}

// sound work
// https://www.youtube.com/watch?v=ODDwTQWwN7I
