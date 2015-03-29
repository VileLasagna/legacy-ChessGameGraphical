
#ifndef CBMENUSTATE_H
#define CBMENUSTATE_H

#include "GameState.h"


class CBMenuState : public GameState
{

public:

	CBMenuState();
	int Update();
	void Draw();

private:
	int ret;
	SDLImage splash;
	virtual void OnMouseButtonEvent(const SDL_MouseButtonEvent& );

};


#endif //CBMENUSTATE_H