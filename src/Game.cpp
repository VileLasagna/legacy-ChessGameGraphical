
#include "Game.h"

Game::Game()
{
	SDLDisplay::instance(); //to grant that call to SDLInit_Everything
	currentState = 0;
}

void Game::Run()
{
	int i = 0;
	while(currentState != -1)
	{
		i = Update();
		Draw();
		Flip();
		currentState = i;
	}
	SDLDisplay::clear();
}

int Game::Update()
{
	return states[currentState]->Update();
}

void Game::Draw()
{
	states[currentState]->Draw();
}

void Game::Flip()
{
	SDLDisplay::instance()->Flip();
}

void Game::addState(GameState *g)
{
	states.push_back(g);
}

Game* Game::instance()
{	
	static Game* inst = 0;
	if (!inst)
	{
		inst = new Game;
	}
	return inst;
}


void Game::Clear()
{
	delete instance();
}
