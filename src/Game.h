#ifndef GAME_H
#define GAME_H

#include <Vector>
#include <String>
#include <fstream>
#include "StringProc.h"
#include "SDLDisplay.h"
#include "GameState.h"

class Game
{
private:	//This class is a singleton. And friend is not my friend.
	Game();
	Game operator= (const Game&);
	Game (const Game&);

public:

	static Game* instance();
	//void Load(std::string gameini);  //TODO: implement?
	void Run();
	void addState(GameState* g);
	static void Clear();



private:
	int Update();
	void Draw();
	void Flip();
	std::vector<GameState*> states; //Note: State 0 is ALWAYS the program starting point
	int currentState;



};

#endif //GAME_H