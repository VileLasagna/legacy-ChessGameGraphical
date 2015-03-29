#ifndef SDL_DISPLAY_H
#define SDL_DISPLAY_H

struct SDL_Surface;

class SDLDisplay
{
private:
	    SDLDisplay();
		SDLDisplay(const SDLDisplay& ref) {}
		SDLDisplay operator= (const SDLDisplay& ref) {}
public:

	static SDLDisplay* instance();
	static void clear();

    ~SDLDisplay();

    void Flip();
	void setMaxDT(float mdt) {maxDT = mdt;}
	void setSize (int width, int height);

    SDL_Surface* getScreen() const;

    void Update();

    float getDtSecs() const;
	float getMaxDT() const {return maxDT;}

private:
    SDL_Surface* screen;
    float dt;
	float maxDT;
};

#endif
