#include "Game.h"
#include "CBMenuState.h"
#include "CBMainState.h"


int main(int, char**)
{

	Game::instance()->addState( new CBMenuState() );
	Game::instance()->addState( new CBMainState() );
	Game::instance()->Run();
	Game::Clear();


	return (0);
};