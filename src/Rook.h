/*
 * Rook.h
 *
 *  Created on: 19-Nov-2008
 *      Author: Vile Lasagna
 */


#include "piece.h"

#ifndef ROOK_H_
#define ROOK_H_

typedef std::vector<Square> column;
typedef std::vector<column> BD;

class Rook: public piece
{
public:

	bool canGo(Pos& to, BD& vec) const;
	bool canMove(Pos& to, BD& vec) const;
	std::vector<Pos> getMoves(BD& vec) const;
	Rook(Pos p);
	Rook(Pos p, bool c);

};


#endif /* ROOK_H_ */
