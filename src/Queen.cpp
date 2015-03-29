/*
 * Queen.cpp
 *
 *  Created on: 24-Nov-2008
 *      Author: Vile Lasagna
 */

#include "Queen.h"

Queen::Queen(Pos p)
{
	piece_ID = pieceID::pieceID(true);
	at = p;
	pointvalue = 9;
}

Queen::Queen(Pos p, bool c)
{
	piece_ID = pieceID::pieceID(c, pieceID::Queen);
	at = p;
	pointvalue = 9;
}


bool Queen::BishopMove(Pos& to, BD& vec) const
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
		throw FatalErrorException ("Queen::Bishop::canGo has crashed yo face!");
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
		default: throw FatalErrorException ("Queen::Bishop::canGo has crashed yo face!");
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

bool Queen::RookMove (Pos& to, BD& vec) const
{
	int difX = to.getX() - at.getX();
	int difY = to.getY() - at.getY();
	if ((difX !=0)&&(difY != 0))
	{
		return false;
	}
	piece* p = (piece*) (vec[to.getX()][to.getY()].getPiece());
	if(p)
	{
		if (p->getColour() == this->getColour())
		{
			return false;
		}
	}
	if (difX == 0)
	{
		if(difY > 0)
		{
			for(int i = (at.getY()+1); i < to.getY(); i++)
			{
				if(vec[at.getX()][i].getPiece())
				{
					return false;
				}
			}

		}
		else
		{
			for(int i = (at.getY()-1); i > to.getY(); i--)
			{
				if(vec[at.getX()][i].getPiece())
				{
					return false;
				}
			}
		}
	}
	else
	{
		if (difX > 0)
		{
			for(int i = (at.getX()+1); i < to.getX(); i++)
			{
				if(vec[i][at.getY()].getPiece())
				{
					return false;
				}
			}
		}
		else
		{
			for(int i = (at.getX()-1); i > to.getX(); i--)
			{
				if(vec[i][at.getY()].getPiece())
				{
					return false;
				}
			}
		}
	}
	return true;
}


bool Queen::canGo (Pos& to, BD& vec) const
{
	if (BishopMove(to, vec)||RookMove(to,vec))
	{
		return true;
	}
	return false;
}

bool Queen::canMove(Pos& to, BD& vec) const
{
	if (canGo(to, vec))
	{
		Queen clone = *this;
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

std::vector<Pos> Queen::getRook(BD& vec) const
{
	std::vector<Pos> moves;
	int x;
	int y;
	if(at.getY()!= 8)
	{
		y = at.getY();
		while (true)
		{
			y++;
			moves.push_back(Pos(at.getX(), y));
			if (y == 8)
			{
				break;
			}
		}
	}
	if (at.getY() != 1)
	{
		y = at.getY();
		while(true)
		{
			y--;
			moves.push_back(Pos(at.getX(),y));
			if(y == 1)
			{
				break;
			}
		}
	}
	if (at.getX() != 8)
	{
		x = at.getX();
		while (true)
		{
			x++;
			moves.push_back(Pos(x, at.getY()));
			if (x == 8)
			{
				break;
			}
		}
	}
	if (at.getX() != 1)
	{
		x = at.getX();
		while(true)
		{
			x--;
			moves.push_back(Pos(x, at.getY()));
			if (x == 1)
			{
				break;
			}
		}
	}
	for (int i = (moves.size()-1); i >= 0; i--)
	{
		if (!RookMove(moves[i], vec))
		{
			moves.erase(moves.begin()+i);
		}
	}
	return moves;
}

std::vector<Pos> Queen::getBishop(BD& vec) const
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
	for(unsigned int i = (moves.size()-1); i>0;i--)
	{
		if(!BishopMove(moves[i], vec))
		{
			moves.erase(moves.begin()+i);
		}
	}
	return moves;
}


std::vector<Pos> Queen::getMoves(BD& vec) const
{
	std::vector<Pos> movesB = getBishop(vec);
	std::vector<Pos> movesR = getRook(vec);
	for(unsigned int i = 0; i < movesR.size(); i++)
	{
		movesB.push_back(movesR[i]);
	}
	return movesB;
}
