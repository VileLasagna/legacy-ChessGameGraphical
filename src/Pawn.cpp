/*
 * Pawn.cpp
 *
 *  Created on: 23-Nov-2008
 *      Author: Vile Lasagna
 */

#include "Pawn.h"


PawnPromotionEvent::PawnPromotionEvent(Pawn* p)
{
	type = pieceID::UNDEFINED;
	promoted = p;
}


Pawn* PawnPromotionEvent::getPawn()
{
	return promoted;
}

pieceID::Type PawnPromotionEvent::getNew()
{
	return type;
}

void PawnPromotionEvent::setNew(pieceID::Type t)
{
	type = t;
}

void Pawn::promote(BD& vec)
{

		std::cout << "Please, choose the piece to promote your pawn into:\nB -> Bishop\n"<<
				"N -> Knight\nR -> Rook\nQ -> Queen\n\nEnter your choice (B,N,R,Q):"<<std::endl;
		piece* t = 0;
		while(true)
		{
			std::string input;
			std::cin >> input;
			char c = (input.c_str())[0];
			bool bk = false;
			switch (c)
			{
			case 'b':
			case 'B': t = new Bishop(at, getColour());bk = true;break;
			case 'n':
			case 'N': t = new Knight(at, getColour());bk = true;break;
			case 'r':
			case 'R': t = new Rook(at, getColour());bk = true;break;
			case 'q':
			case 'Q': t = new Queen(at, getColour());bk = true;break;
			}
			if(bk){break;}
			std::cout << "Please, choose the piece to promote your pawn into:\nB -> Bishop\n"<<
					"N -> Knight\nR -> Rook\nQ -> Queen\n\nEnter your choice (B,N,R,Q):"<<std::endl;
		}

		vec[getPos().getX()][getPos().getY()].setID(t); //OMG! H4X!
		/*
		*	I thought that after an exception was treated, control returned to the throwing code, but
		*	I've found out the hard way that it doesn't. Lots of stuff won't work because of this
		*	(or, at least, won't work the way I though they should);
		*/
		//throw PawnPromotionEvent::PawnPromotionEvent(this);
}

Pawn::Pawn (Pos p)
{
	piece_ID = pieceID::pieceID(true);
	at = p;
	pointvalue = 1;
}

Pawn::Pawn(Pos p, bool c)
{
	piece_ID = pieceID::pieceID(c, pieceID::Pawn);
	at = p;
	pointvalue = 1;
}

bool Pawn::canGo(Pos& to, BD& vec) const 
{
	int difX = to.getX() - at.getX();
	int difY = to.getY() - at.getY();
	if (difX == 0)
	{
		if(this->getColour())
		{

			if (difY<=2 && difY > 0)
			{
				if(!(vec[at.getX()][(at.getY()+1)].getPiece()))
				{
					if (difY == 1)
					{
						return true;
					}
					else
					{
						if(first() && (!vec[at.getX()][(at.getY()+2)].getPiece()))
						{
							return true;
						}
					}
				}
			}
		}
		else
		{
			if (difY >= -2 && difY < 0)
			{
				if(!(vec[at.getX()][(at.getY()-1)].getPiece()))
				{
					if (difY == -1)
					{
						return true;
					}
					else
					{
						if(first() && (!vec[at.getX()][(at.getY()-2)].getPiece()))
						{
							return true;
						}
					}
				}
			}
		}
	}

	if(difX == (-1) || difX == 1)
	{
		if(this->getColour())
		{
			if(difY != 1)
			{
				return false;
			}
		}
		else
		{
			if(difY != (-1))
			{
				return false;
			}
		}
		piece* p = (piece*) (vec[to.getX()][to.getY()].getPiece());
		if (!p)
		{
			p = (piece*) (vec[to.getX()][to.getY()].getPassant());
		}
		if (!p)
		{
			return false;
		}
		else
		{
			if (p->getColour() == getColour())
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	return false;
}

bool Pawn::canMove(Pos& to, BD& vec) const 
{

	if(canGo(to, vec))
	{
		Pawn clone = *this;
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

	return false;
}

std::vector<Pos> Pawn::getMoves(BD& vec) const 
{
	std::vector<Pos> moves;
	int x = at.getX();
	int y = at.getY();
	if (this->getColour())
	{
		if ( y < 8)
		{
			moves.push_back(Pos(x,y+1));
		}
		if ( y < 7)
		{
			moves.push_back(Pos(x,y+2));
		}
		if ( (y < 8) && (x < 8))
		{
			moves.push_back(Pos(x+1,y+1));
		}
		if ( (y < 8) && (x > 1))
		{
			moves.push_back(Pos(x-1,y+1));
		}
	}
	else
	{
		if ( y > 1)
		{
			moves.push_back(Pos(x,y-1));
		}
		if ( y > 2)
		{
			moves.push_back(Pos(x,y-2));
		}
		if ( (y > 1) && (x < 8))
		{
			moves.push_back(Pos(x+1,y-1));
		}
		if ( (y > 1) && (x > 1))
		{
			moves.push_back(Pos(x-1,y-1));
		}
	}
	for (int i = (moves.size()-1); i >= 0; i--)
	{
		if(!this->canMove(moves[i], vec))
		{
			moves.erase(moves.begin()+i);
		}
	}

	return moves;
}

bool Pawn::move(Pos to, BD& vec )
{
	if (canMove(to, vec))
	{
		bool passant = false;
		if (((at.getY() - to.getY())==2)||((at.getY() - to.getY()) == (-2)))
		{
			passant = true;
		}
		Pos from = at;
		int x = to.getX(); int y = to.getY();
		piece* id = ((piece*) vec[x][y].getPiece());
		at = to;
		vec[x][y].setID(this);
		vec[from.getX()][from.getY()].setID(0);
		id = ((piece*) vec[x][y].getPassant());
		if (id)
		{
			Pos PasPos = id->getPos();
			vec[PasPos.getX()][PasPos.getY()].setID(0);
		}
		if (firstMove)
		{
			firstMove = false;
		}
		if( (this->getColour()&&(at.getY() == 8) || (!this->getColour())&&(at.getY() == 1)))
		{
			promote(vec);
		}
		clearPassant(vec);
		if (passant)
		{
			vec[from.getX()][((from.getY()+to.getY())/2)].setPassant(this);
		}
		//throw FiftyResetEvent();
		return true;
	}
	return false;
}
