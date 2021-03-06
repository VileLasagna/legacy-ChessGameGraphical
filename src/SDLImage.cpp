#include "SDLImage.h"
#include <SDL_Image.h>
#include <assert.h>

SDLImage::SDLImage()
{
    image = 0;
	setAlphaT();
}

bool SDLImage::Load(const std::string& filename)
{
    image = IMG_Load(filename.c_str());

    return (image != 0);
}

void SDLImage::setColourKey(const SDLRGBColour& tc)
{
	SDL_SetColorKey(
        image, 
        SDL_SRCCOLORKEY | SDL_RLEACCEL, 
		SDL_MapRGB(image->format, tc.R(), tc.G(), tc.B()));
}

SDLImage::~SDLImage()
{
	
    SDL_FreeSurface(image);
	
}

void SDLImage::Blit(int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
	SDL_BlitSurface(image, 0, SDLDisplay::instance()->getScreen(), &dest);
}

void SDLImage::setDrawAlpha(int i)
{
	SDL_SetAlpha(image, SDL_SRCALPHA | SDL_RLEACCEL , i);
}

unsigned int SDLImage::getPixelColour(int x, int y) const
{
	unsigned char* c = 
        (unsigned char*) image->pixels + 
        (y * image->pitch) +
        (x * image->format->BytesPerPixel);

	unsigned int r = 0;
    if (image->format->BytesPerPixel == 3)
    {
        r = c[0] + (c[1] << 8) + (c[2] << 16);
    }
    else if (image->format->BytesPerPixel == 4)
    {
        r = c[0] + (c[1] << 8) + (c[2] << 16) + (c[3] << 24);
    }

    return r;
}

bool SDLImage::isPixTransparent(int x, int y) const
{
    unsigned int r = getPixelColour(x, y);

    if (image->format->BytesPerPixel == 3)
    {
        // No alpha channel - check if colour is same as colour key
        return (r == image->format->colorkey);
    }

    // Image has alpha channel, so pixel is transparent if alpha is lesser than the set threshold
    return ((r & 0xff000000) <= alphaT);
}