/*
 * Bishop.cpp
 *
 *  Created on: 24-Nov-2008
 *      Author: Vile Lasagna
 */

#include "Bishop.h"

Bishop::Bishop(Pos p)
{
	piece_ID = pieceID::pieceID(true);
	at = p;
	pointvalue = 3;
}

Bishop::Bishop(Pos p, bool c)
{
	piece_ID = pieceID::pieceID(c, pieceID::Bishop);
	at = p;
	pointvalue = 3;
}

bool Bishop::canGo(Pos&to, BD& vec) const
{
	int difX = to.getX() - at.getX();
	int difY = to.getY() - at.getY();
	if (!((difX == difY)||(difX == (-difY))))
	{
		return false;
	}
	if(difX ==0)
	{
		return false;
	}
	
	int direc = 0;
	if (difX > 0 && difY > 0)
	{
		direc = 1;
	}
	if (difX > 0 && difY < 0)
	{
		direc = 2;
	}
	if (difX < 0 && difY < 0)
	{
		direc = 3;
	}
	if (difX < 0 && difY > 0)
	{
		direc = 4;
	}
	if (direc == 0)
	{
		throw FatalErrorException ("Bishop::canGo has crashed yo face!");
	}
	Pos p = at;
	while (true)
	{
		switch (direc)
		{
		case 1: if (!p.UpRight()) {return false;} break;
		case 2: if (!p.DownRight()) {return false;} break;
		case 3: if (!p.DownLeft()){return false;} break;
		case 4: if (!p.UpLeft()) {return false;} break;
		default: throw FatalErrorException ("Bishop::canGo has crashed yo face!");
		}
		if (p == to)
		{
			break;
		}
		else
		{
			if (vec[p.getX()][p.getY()].getPiece()) 
			{
				return false;
			}
		}

	}
	piece* pc = (piece*) vec[p.getX()][p.getY()].getPiece();
	if (pc)
	{
		if (pc->getColour() == getColour())
		{
			return false;
		}
	}
	return true;
}

bool Bishop::canMove(Pos& to, BD& vec) const 
{
	
	if(canGo(to, vec))
	{
		Bishop clone = *this;
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

std::vector<Pos> Bishop::getMoves(BD& vec) const 
{
	std::vector<Pos> moves;
	Pos p = at;
	int x;
	int y;
	if ((at.getX() != 8)&&(at.getY()!=8))
	{
		x = p.getX();
		y = p.getY();
		while (true)
		{
			x++; y++;
			moves.push_back(Pos(x,y));
			if((x==8)||(y==8))
			{
				break;
			}
		}
	}
	if((at.getX() != 8)&&(at.getY()!=1))
	{
		x = p.getX();
		y = p.getY();
		while (true)
		{
			x++; y--;
			moves.push_back(Pos(x,y));
			if ((x==8)|| (y == 1))
			{
				break;
			}
		}
	}
	if((at.getX() != 1)&&(at.getY()!=1))
	{
		x = p.getX();
		y = p.getY();
		while (true)
		{
			x--; y--;
			moves.push_back(Pos(x,y));
			if ((x==1)|| (y == 1))
			{
				break;
			}
		}
	}
	if((at.getX() != 1)&&(at.getY()!=8))
	{
		x = p.getX();
		y = p.getY();
		while (true)
		{
			x--; y++;
			moves.push_back(Pos(x,y));
			if ((x==1)|| (y == 8))
			{
				break;
			}
		}
	}
	for(int i = (moves.size()-1); i>=0;i--)
	{
		if(!canMove(moves[i], vec))
		{
			moves.erase(moves.begin()+i);
		}
	}
	return moves;
}
