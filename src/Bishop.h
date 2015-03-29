/*
 * Bishop.h
 *
 *  Created on: 19-Nov-2008
 *      Author: Vile Lasagna
 */


#include "piece.h"

#ifndef BISHOP_H_
#define BISHOP_H_

typedef std::vector<Square> column;
typedef std::vector<column> BD;

class Bishop: public piece
{
public:
	bool canGo(Pos& to, BD& vec) const;
	bool canMove(Pos& to, BD& vec) const;
	std::vector<Pos> getMoves(BD& vec) const;
	Bishop (Pos p);
	Bishop::Bishop(Pos p, bool c);

};

#endif /* BISHOP_H_ */
