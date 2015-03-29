#include <assert.h>
#include "EventHandler.h"

void EventHandler::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		HandleEvent(event);
	}
}

void EventHandler::HandleEvent(const SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		OnKeyboardEvent(e.key);
		break;

	case SDL_MOUSEMOTION:
		OnMouseMotionEvent(e.motion);
		break;

	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		OnMouseButtonEvent(e.button);
		break;

	case SDL_QUIT:
		OnQuitEvent();
		break;

	case SDL_JOYAXISMOTION:
		OnJoyAxisEvent(e.jaxis);
		break;

	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
		OnJoyButtonEvent(e.jbutton);
		break;

    case SDL_JOYHATMOTION:
        OnJoyHatEvent(e.jhat);
        break;

    case SDL_JOYBALLMOTION:
        OnJoyBallEvent(e.jball);
        break;
	case SDL_ACTIVEEVENT:
		OnActiveEvent (e.active);
		break;
	case SDL_VIDEOEXPOSE:
		OnExposeEvent (e.expose);
		break;
	case SDL_VIDEORESIZE:
		OnResizeEvent(e.resize);
		break;

	default:
        // Unexpected event type!
		assert(0);
		break;
	}
}

void EventHandler::OnQuitEvent()
{
    exit(0);
}