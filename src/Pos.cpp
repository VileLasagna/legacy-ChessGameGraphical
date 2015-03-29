/*
 * Pos.cpp
 *
 *  Created on: 09-Nov-2008
 *      Author: Vile Lasagna
 */

#include "Pos.h"

Pos::Pos (int h, int v)
{
	x = h;
	y = v;

}

int Pos::getX() const 
{
	return x;
}

int Pos::getY() const 
{
	return y;
}

Pos Pos::operator++ (int)
{
	if (x == 0)
	{
		y++;
	}
	else
	{
		if (x != 8)
		{
			x++;
		}
		else
		{
			if (y != 8)
			{
				x = 1;
				y++;
			}
			else
			{

			}
		}
	}
	return *this;
}

bool Pos::endboard()
{
	if (x == 8 && y == 8)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Pos::UpRight()
{
	if (x == 8 || y == 8)
	{
		return false;
	}
	else
	{
		x++;
		y++;
		return true;
	}
}

bool Pos::DownRight()
{
	if (x == 8 || y == 1)
	{
		return false;
	}
	else
	{
		x++;
		y--;
		return true;
	}
}

bool Pos::DownLeft()
{
	if (x == 1 || y == 1)
	{
		return false;
	}
	else
	{
		x--;
		y--;
		return true;
	}
}

bool Pos::UpLeft()
{
	if (x == 1 || y == 8)
	{
		return false;
	}
	else
	{
		x--;
		y++;
		return true;
	}
}

bool Pos::operator ==(Pos comp)
{
	if (x != comp.getX())
	{
		return false;
	}
	if (y != comp.getY())
	{
		return false;
	}
	return true;
}

bool Pos::operator != (Pos comp)
{
	bool r = !(*this == comp);
	return r;
}