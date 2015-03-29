#include "SDLDisplay.h"
#include <SDL.h>

SDLDisplay::SDLDisplay()
{
    dt = 0;

    SDL_Init(SDL_INIT_EVERYTHING);	

	maxDT = 0.15f;

    screen = SDL_SetVideoMode(640, 480, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
}


SDLDisplay::~SDLDisplay()
{
    SDL_Quit();
}

SDL_Surface* SDLDisplay::getScreen() const
{
    return screen;
}

void SDLDisplay::Flip()
{
    SDL_Flip(screen);
}

void SDLDisplay::Update()
{
    static unsigned int oldms = SDL_GetTicks();
    unsigned int ms = SDL_GetTicks();
    dt = ((float)(ms - oldms)) / 1000.0f;
    oldms = ms;
	if (dt > maxDT)
	{
		dt = maxDT;
	}
}

float SDLDisplay::getDtSecs() const
{
    return dt;
}


SDLDisplay* SDLDisplay::instance()
{
	static SDLDisplay* inst = 0;
	if (!inst)
	{
		inst = new SDLDisplay;
	}
	return inst;
}

void SDLDisplay::clear()
{
	SDLDisplay* inst = SDLDisplay::instance();
	//yeah, I know this might end up initialising this unnecessarily
	//but I couldn't really find an alternative
	delete(inst);
}

void SDLDisplay::setSize(int width, int height)
{
	screen = SDL_SetVideoMode(width, height, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
}