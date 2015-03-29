/*
 * piece.h
 *
 *  Created on: 27-Oct-2008
 *      Author: Vile Lasagna
 */


#include <Vector>
#include "Pos.h"
#include "Square.h"
#include "FatalErrorException.h"
#include "pieceID.h"
#include <iostream>



#ifndef PIECE_H_
#define PIECE_H_

typedef std::string String;
typedef std::vector<Square> column;
typedef std::vector<column> BD;
class piece
{
public:

	void kill();
	virtual bool move (Pos to, BD& vec);
	bool canMove(BD& vec) const;//returns true if the piece can move at all. Used to check for mates.
	virtual bool canMove(Pos& to, BD& vec) const = 0;
	virtual bool canGo (Pos& to, BD& vec) const = 0; // canGo is like canMove, but doesn't check for leaving your king in check. This is to avoid infinite loops
	virtual std::vector<Pos> getMoves(BD& vec) const = 0;
	void setPos(Pos& to, BD& vec);//setPos is just to use for move checking on temporary copied boards. WARNING: it alters piece::at, so be sure to revert it after testing
	piece(); //constructor that sets firstmove (used to do s'more stuff but was pwned due to technicalities)
	pieceID::Type getType()const;
	pieceID getID() const;
	virtual ~piece();
	void clearPassant(BD& vec); //removes all enPassant flags from the board. MUST be called after each successful move!!
	bool getCheck(BD& vec) const; //returns true if the owner of this piece is in check. Why not board -> Check for move
	bool getColour() const;
	Pos getPos() const;
	bool first() const;
	int getValue() const;
	void printMe() const;
	void setMoved(); // for castling purposes
	bool isLocked(BD& vec) const; //this is to check Stale and checkmate. That what getmoves was for (for nor), but it's not working properly so I'm gonna do a dirty, ugly but sure way and leave getMoves to be fixed some other time.

protected:
	int pointvalue;
	Pos at;
	pieceID piece_ID;
	bool firstMove;

};

class deadPieceEvent
/*
 * When a piece dies it throws this exception with a reference to itself so that
 * the container (GameState) can update all necessary data
 */
{
public:
	deadPieceEvent(piece* id);
	piece* id;

};

class FiftyResetEvent
{

};

#endif /* PIECE_H_ */
