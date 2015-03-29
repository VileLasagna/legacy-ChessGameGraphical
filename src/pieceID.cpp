/*
 * pieceID.cpp
 *
 *  Created on: 23-Nov-2008
 *      Author: Vile Lasagna
 */

#include "pieceID.h"

	int pieceID::S_ID = 1;
	int pieceID::S_AUTO = 1;

bool pieceID::getColour() const
{
	return colour;
}

pieceID::Type pieceID::getType() const
{
	return type;
}

int pieceID::getID() const
{
	return ID;
}

pieceID::pieceID(bool c, pieceID::Type t)
{
	static int S_ID = 1;
	colour = c;
	type = t;
	ID = S_ID;
	S_ID++;
}

pieceID::pieceID(bool AUTO)
{

	if (AUTO)
	{
		pieceID::Type typeCycle[] = {pieceID::Rook, pieceID::Knight, pieceID:: Bishop, pieceID::Queen, pieceID::King, pieceID::Bishop, pieceID::Knight, pieceID::Rook};
		if (pieceID::S_AUTO < 9)
		{
			colour = true;
			type = typeCycle[(pieceID::S_AUTO-1)];
			ID = S_ID;
			pieceID::S_AUTO++;
			pieceID::S_ID++;
		}
		else
		{
			if (pieceID::S_AUTO < 17)
			{
				colour = true;
				type = pieceID::Pawn;
				ID = pieceID::S_ID;
				pieceID::S_AUTO++;
				pieceID::S_ID++;
			}
			else
			{
				if (pieceID::S_AUTO < 25)
				{
					colour = false;
					type = pieceID::Pawn;
					ID = pieceID::S_ID;
					pieceID::S_AUTO++;
					pieceID::S_ID++;
				}
				else
				{
					if (pieceID::S_AUTO < 33)
					{
						colour = false;
						type = typeCycle[(pieceID::S_AUTO-25)];
						ID = pieceID::S_ID;
						pieceID::S_AUTO++;
						pieceID::S_ID++;
					}
					else
					{
						throw FatalErrorException("Bad piece auto-creation. Board should already be full");
					}
				}
			}
		}
	}
	else
	{
		type = pieceID::UNDEFINED;
		ID = 0;
		colour = true; //why not, whatever
	}
}

