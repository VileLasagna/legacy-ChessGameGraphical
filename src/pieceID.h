/*
 * pieceID.h
 *
 *  Created on: 23-Nov-2008
 *      Author: Vile Lasagna
 */

#ifndef PIECEFACE_H_
#define PIECEFACE_H_

#include "FatalErrorException.h"

class pieceID
{
public:

	enum Type {Pawn, Knight, Bishop, Rook, Queen, King, UNDEFINED};
	bool getColour() const;
	Type getType() const;
	int getID() const;
	pieceID(bool AUTO = false);//constructor that is used by board::newGame()
	pieceID(bool c, Type t);


private:

	pieceID::Type type;
	int ID;
	bool colour;
	static int S_ID;
	static int S_AUTO;


};

#endif /* PIECEFACE_H_ */
