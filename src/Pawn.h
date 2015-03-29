/*
 * Pawn.h
 *
 *  Created on: 19-Nov-2008
 *      Author: Vile Lasagna
 */

#include "piece.h"
#include <iostream>
#include <String>
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"


#ifndef PAWN_H_
#define PAWN_H_

typedef std::vector<Square> column;
typedef std::vector<column> BD;

class Pawn: public piece
{
public:

	void promote(BD& vec);
	bool canGo(Pos& to, BD& vec) const;
	bool canMove(Pos& to, BD& vec) const;
	std::vector<Pos> getMoves(BD& vec) const;
	Pawn(Pos p);
	Pawn(Pos p, bool c);
	bool move(Pos to, BD& vec);

};


class PawnPromotionEvent
{
public:
	Pawn* getPawn();
	pieceID::Type getNew();
	PawnPromotionEvent(Pawn* p);
	void setNew(pieceID::Type t);

private:
	Pawn* promoted;
	pieceID::Type type;
};


#endif /* PAWN_H_ */
