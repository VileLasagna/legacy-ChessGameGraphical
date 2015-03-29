#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "EventHandler.h"
#include "Sprite.h"
#include <Vector>
#include <String>
#include <fstream>
#include "StringProc.h"

class GameState: public EventHandler
{
public:
	GameState(){}
	virtual~ GameState(){}
	virtual int Update() = 0;	 //The return value is the Game State to be run on the following update
								// Return -1 to terminate the program
	virtual void Draw() = 0; //Blit everything.

protected:
	int self; //The index of this state.

};



#endif //GAMESTATE_H