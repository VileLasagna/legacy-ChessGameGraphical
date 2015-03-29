
#include "CBMenuState.h"


CBMenuState::CBMenuState()
{
	SDLDisplay::instance()->setSize(1024,768);
	splash.Load("ChessBastard-Splash.png");
	self = 0;
	ret = 0;
}

void CBMenuState::Draw()
{
	splash.Blit();
}

void CBMenuState::OnMouseButtonEvent(const SDL_MouseButtonEvent &)
{
	ret = 1;
}

int CBMenuState::Update()
{
	EventHandler::Update();
	return ret;
}

