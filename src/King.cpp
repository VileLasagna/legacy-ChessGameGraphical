/*
 * King.cpp
 *
 *  Created on: 24-Nov-2008
 *      Author: Vile Lasagna
 */

#include "King.h"


King::King(Pos p)
{
	piece_ID = pieceID::pieceID(true);
	pointvalue = 0;
	at = p;
}

bool King::canGo(Pos& to, BD& vec) const 
{
	int difX = to.getX() - at.getX();
	int difY = to.getY() - at.getY();
	if ((difX > 1) || (difX < (-1)) || (difY > 1) || (difY < (-1)))
	{
		return false;
	}
	if ((difX == 0) && (difY == 0))
	{
		return false;
	}
	piece* p = (piece*) vec[to.getX()][to.getY()].getPiece();
	if (p)
	{
		if ((p->getColour())==(this->getColour()))
		{
			return false;
		}
	}
	return true;
}
bool King::canMove(Pos& to, BD& vec) const 
{
	if(canGo(to, vec))
	{
		King clone = *this;
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

std::vector<Pos> King::getMoves(BD& vec) const 
{
	std::vector<Pos> moves;
	int x = at.getX();
	int y = at.getY();
	int up = y+1;
	int down = y-1;
	int right = x+1;
	int left = x-1;
	moves.push_back(Pos(right, up));
	moves.push_back(Pos(right, y));
	moves.push_back(Pos(right, down));
	moves.push_back(Pos(x, down));
	moves.push_back(Pos(left,down));
	moves.push_back(Pos(left,y));
	moves.push_back(Pos(left,up));
	moves.push_back(Pos(x,up));
	for( int i = (moves.size()-1); i >= 0; i--)
	{
		if((moves[i].getX() > 8) || (moves[i].getX() < 1) || (moves[i].getY() > 8) || (moves[i].getY() < 1))
		{
			moves.erase(moves.begin()+i);
			continue;
		}
		if (!canMove(moves[i], vec))
		{
			moves.erase(moves.begin()+i);
		}
	}
	return moves;
}

bool King::castle(bool queenside, BD& vec)
{
	piece* rk = 0;
	int inc = 0;
	if (!queenside)
	{
		rk = (piece*) (vec[8][at.getY()].getPiece());
		inc = 1;
	}
	else
	{
		rk = (piece*) (vec[1][at.getY()].getPiece());
		inc = -1;
	}
	if ((!rk) || ((!this->first()) || (!rk->first()))) //if "the rook is a lie" or anyone has already moved
	{
		return false;
	}
	if (!queenside)
	{
		if((vec[6][at.getY()].getPiece()) || (vec[7][at.getY()].getPiece()))
		{
			return false;
		}
	}
	else
	{
		if((vec[4][at.getY()].getPiece()) || (vec[3][at.getY()].getPiece()) || (vec[2][at.getY()].getPiece()))
		{
			return false;
		}
	}
	BD testboard = Square::BDClone(vec);
	Pos op = at;
	at = Pos(op.getX()+inc, op.getY());
	setPos(at, testboard);
	if (getCheck(testboard))
	{
		at = op;
		return false;
	}
	else
	{
		at = Pos(op.getX()+inc+inc, op.getY());
		setPos(at,testboard);
		if (getCheck(testboard))
		{
			at = op; 
			return false;
		}
		else
		{
			setPos(at, vec);
			Pos r = Pos(op.getX()+inc, op.getY());
			Pos rp = rk->getPos();
			rk->setPos(r, vec);
			vec[op.getX()][op.getY()].setID(0);
			vec[rp.getX()][rp.getY()].setID(0);
			setMoved();
			rk->setMoved();
			return true;
		}
	}
}
