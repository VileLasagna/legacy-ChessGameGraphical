/*
 * Board.h
 *
 *  Created on: 09-Nov-2008
 *      Author: Vile Lasagna
 */

#include "Square.h"
#include <String>
#include <Vector>
#include <iostream>
#include "Pos.h"
#include "piece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

#ifndef BOARD_H_
#define BOARD_H_

typedef std::vector<Square> column;
typedef std::vector<column> BD;

class Board
{
public:
	Board();//newGame
	bool movePiece(Pos from, Pos to, bool colour);
	bool movePiece(pieceID::Type t, bool colour, Pos to);
	bool movePiece(pieceID::Type t, bool colour, int locale, bool localetype, Pos to);
	const bool getStale(bool c);
	const bool getMate(bool c);
	BD& getField();
	King* getKing(bool c);


private:

	static int S_GRAVE;
	BD field;
	std::vector<piece*> pieces;
	King* BlackKing;
	King* WhiteKing; //these two are just to ease player-level checks, they're always in the board, anyway...
};

#endif /* BOARD_H_ */
