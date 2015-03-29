/*
 * Board.cpp
 *
 *  Created on: 19-Nov-2008
 *      Author: Vile Lasagna
 */


#include "Board.h"


int Board::S_GRAVE = 1;

Board::Board()//new game
{
	std::cout<<"board is being created!"<<std::endl;
	Pos bdpos(1,1);
	for(int i = 0; i < 33; i++)
	{
		column c;
		field.push_back(c);
//		field[0].push_back(Square::Square(Pos::Pos(0,i)));
	}
	for (int i = 1; i <= 8; i++)
	{
		field[i].push_back(Square::Square(Pos::Pos(0,i)));
	}
	while(true)
	{

		field[bdpos.getX()].push_back(Square::Square());
		if(bdpos.endboard())
		{
			break;
		}
		bdpos++;
	}
	bdpos = Pos(1,1);
	pieces.push_back(new Rook(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Knight(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Bishop(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Queen(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new King(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	WhiteKing = (King*) field[bdpos.getX()][bdpos.getY()].getPiece();
	bdpos++;
	pieces.push_back(new Bishop(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Knight(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Rook(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos = Pos(1,7);
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Pawn(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Rook(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Knight(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Bishop(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Queen(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new King(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	BlackKing = (King*) field[bdpos.getX()][bdpos.getY()].getPiece();
	bdpos++;
	pieces.push_back(new Bishop(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Knight(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	bdpos++;
	pieces.push_back(new Rook(bdpos));
	field[bdpos.getX()][bdpos.getY()].setID(pieces[(pieces.size()-1)]);
	/*
	for (unsigned int pt = 0; pt < pieces.size(); pt++)
	{
		pieces[pt]->printMe();
	}
	*/
	
}


bool Board::movePiece(Pos from, Pos to, bool colour)
{


	piece* p = (piece*) field[from.getX()][from.getY()].getPiece();
	if (!p || (p->getColour() != colour))
	{
		return false;
	}
	else
	{
		if (p->getType() == pieceID::King) //gotta know if he's trying to castle
		{
			int moveX = to.getX() - from.getX();
			if ( (moveX > 1) || (moveX < (-1)))
			{
				King* k = (King*)p;
				bool qside = (moveX<0);
				return(k->castle(qside, field));
			}
		}
		return(p->move(to, field));
	}
	return false;
}

bool Board::movePiece(pieceID::Type t, bool colour, Pos to)
{
	Pos from;
	std::vector<piece*> prospect;
	Pos p(1,1);
	while (true)
	{
		piece* pc = (piece*) field[p.getX()][p.getY()].getPiece();
		if (pc)
		{
			if((((pc->getColour())== colour)) && ( (pc->getType()) == t))
			{
				prospect.push_back(pc);
			}
		}
		if (p.endboard())
		{
			break;
		}
		else
		{
			p++;
		}

	}
	if (prospect.empty())
	{
		return false;
	}
	else
	{
		for (int i = (prospect.size() -1); i >=0; i--)
		{
			if (!(prospect[i]->canMove(to, field)))
			{
				prospect.erase((prospect.begin()+i));
			}
		}
		if (prospect.size() != 1)
		{
			return false;
		}
		else
		{
			return movePiece (prospect[0]->getPos(), to, colour);
		}
	}
}

bool Board::movePiece(pieceID::Type t, bool colour, int locale, bool localetype, Pos to)
{
	std::vector<piece*> prospect;
	for (int i = 1; i <= 8; i ++)
	{
		piece* p;
		if (localetype)
		{
			p = (piece*) field[i][locale].getPiece();
		}
		else
		{
			p = (piece*) field[locale][i].getPiece();
		}
		if (p)
		{
			if ( (p->getType() == t) && (p->getColour() == colour))
			{
				prospect.push_back(p);
			}
		}
	}
	if (prospect.size() != 1)
	{
		return false;
	}
	else
	{
		return movePiece(prospect[0]->getPos(),to, colour);
	}
}

const bool Board::getStale(bool c)
{
	King* k = 0;
	if (c)
	{
		k = WhiteKing;
	}
	else
	{
		k = BlackKing;
	}
	Pos p(1,1);
	std::vector<piece*> inboard;
	while(!p.endboard())
	{
		Square s = field[p.getX()][p.getY()];
		piece* pc = (piece*) s.getPiece();
		if (pc)
		{
			if ((pc->getColour()) == c)
			{
				inboard.push_back(pc);
			}
		}
		p++;
	}
	for(unsigned int i = 0; i < inboard.size(); i++)
	{
		if(!(inboard[i]->isLocked(field)))
		{
			return false;
		}
	}
	return true;
}

const bool Board::getMate(bool c)
{
	King* k = 0;
	if (c)
	{
		k = WhiteKing;
	}
	else
	{
		k = BlackKing;
	}
	return ((k->getCheck(field))&&getStale(c));
}

BD& Board::getField()
{
	BD& fd = field;
	return fd;
}

King* Board::getKing(bool c)
{
	if (c)
	{
		return WhiteKing;
	}
	else
	{
		return BlackKing;
	}
}