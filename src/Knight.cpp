/*
 * Knight.cpp
 *
 *  Created on: 24-Nov-2008
 *      Author: Vile Lasagna
 */

#include "Knight.h"


Knight::Knight(Pos p)
{
	piece_ID = pieceID::pieceID(true);
	pointvalue = 3;
	at = p;
}
Knight::Knight(Pos p, bool c)
{
	piece_ID = pieceID::pieceID(c, pieceID::Knight);
	at = p;
	pointvalue = 3;
}

bool Knight::canGo(Pos& to, BD& vec) const 
{
	int difX = to.getX() - at.getX();
	int difY = to.getY() - at.getY();

	if ((difX != 2) && (difX != (-2)) && (difY != 2) && (difY != (-2)))
	{
		return false;
	}
	if ((difX != 1) && (difX != (-1)) && (difY != 1) && (difY != (-1)))
	{
		return false;
	}

	if (((difX == 2) || (difX == (-2))) && ((difY == 2) || (difY == (-2))))
	{
		return false;
	}
	if (((difX == 1) || (difX == (-1))) && ((difY == 1) || (difY == (-1))))
	{
		return false;
	}
	
	if ((to.getX() > 8) || (to.getX() < 1) || (to.getY() > 8) || (to.getY() < 1))
	{
		return false;
	}
	piece* p = (piece*) vec[to.getX()][to.getY()].getPiece();
	if (p)
	{
		if ((p->getColour()) == (this->getColour()))
		{
			return false;
		}
	}
	return true;
}

bool Knight::canMove(Pos& to, BD& vec) const 
{
	if (canGo(to, vec))
	{
		Knight clone = *this;
		BD testBoard = Square::BDClone(vec);
		clone.setPos(to,testBoard);
		testBoard[at.getX()][at.getY()].setID(0);
		if(!getCheck(testBoard))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

std::vector<Pos> Knight::getMoves(BD& vec) const 
{
	std::vector<Pos> moves;
	int x = at.getX();
	int y = at.getY();
	if (x < 7)
	{
		if (y < 8)
		{
			moves.push_back(Pos((x+2),(y+1)));
		}
		if (y > 1)
		{
			moves.push_back(Pos((x+2),(y-1)));
		}
	}
	if (x > 2)
	{
		if (y < 8)
		{
			moves.push_back(Pos((x-2),(y+1)));
		}
		if (y > 1)
		{
			moves.push_back(Pos((x-2),(y-1)));
		}
	}
	if (y < 7)
	{
		if (x < 8)
		{
			moves.push_back(Pos((x+1),(y+2)));
		}
		if (x > 1)
		{
			moves.push_back(Pos((x-1),(y+2)));
		}
	}
	if (y > 2)
	{
		if (x < 8)
		{
			moves.push_back(Pos((x+1),(y-2)));
		}
		if (x > 1)
		{
			moves.push_back(Pos((x-1),(y-2)));
		}
	}
	for (int i = (moves.size()-1); i >= 0; i--)
	{
		if (!canMove(moves[i], vec))
		{
			moves.erase(moves.begin()+i);
		}
	}
	return moves;
}
