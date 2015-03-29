
#ifndef CBMAINSTATE_H
#define CBMAINSTATE_H


#include "GameState.h"
#include "ChessState.h"
#include "StringProc.h"
#include "Rect.h"
#include "Vec2.h"
#include <Vector>


class CBMainState : public GameState
{

public:

	CBMainState();
	int Update();
	void Draw();




private:

	void OnMouseButtonEvent(const SDL_MouseButtonEvent& e);
	int ret;
	ChessState bastard;
	Sprite Mouse;
	Sprite* GB[64];		 // Pos.X() + Pos.Y()*8
	bool activePiece;
	std::vector<Sprite*> pieces;
	SDLImage BG;
	Vec2i boardCorner;	//graphical top-left of the board
	int sqSize;			//graphical size of each quare onthe board
	void makePieces();	//looks at the board and creates all the pieces. Intensive and wasteful but don't have time to try and "hardwire" the sprites to the pieces
	bool GameOver;
	std::string command;
	int pieceX;
	int pieceY;


};


#endif //CBMAINSTATE_H