#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL.h>

class EventHandler
{
public:
    virtual ~EventHandler() {}

    void Update();
    void HandleEvent(const SDL_Event& event);

protected:
    virtual void OnKeyboardEvent(const SDL_KeyboardEvent& ) {}
    virtual void OnMouseMotionEvent(const SDL_MouseMotionEvent& ) {}
    virtual void OnMouseButtonEvent(const SDL_MouseButtonEvent& ) {}
    virtual void OnJoyAxisEvent(const SDL_JoyAxisEvent& ) {}
    virtual void OnJoyBallEvent(const SDL_JoyBallEvent& ) {}
    virtual void OnJoyHatEvent(const SDL_JoyHatEvent& ) {}
    virtual void OnJoyButtonEvent(const SDL_JoyButtonEvent& ) {}
	virtual void OnActiveEvent (const SDL_ActiveEvent& ) {}
	virtual void OnExposeEvent (const SDL_ExposeEvent& ) {}
	virtual void OnResizeEvent (const SDL_ResizeEvent& ) {}
    virtual void OnQuitEvent();
};

#endif //EVENT_HANDLER_H