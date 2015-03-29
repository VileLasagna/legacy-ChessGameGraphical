/*
 * Pos.h
 *
 *  Created on: 09-Nov-2008
 *      Author: Vile Lasagna
 */

#ifndef POS_H_
#define POS_H_

class Pos
{
	/*
	 * In the board Pos should go from 1 to 8
	 * the reason behind this is to keep
	 * 0 as a special position.
	 * (0,X) should be a special column to
	 * store dead pieces and such
	 *
	 * Y has to go from 0 to 7 because of
	 * board.
	 *
	 * To simplify checking this condition
	 * endBoard returns true if x = 8 and y=7.
	 * this should avoid some silly mistakes.
	 */
public:
	int getX() const; 
	int getY() const;
	bool endboard();
	Pos operator++(int);
	Pos (int h = 0, int v = 0);
	bool UpRight();
	bool DownRight();
	bool DownLeft();
	bool UpLeft();
	bool operator == (Pos comp);
	bool operator != (Pos comp);
	void reset() {x = 1; y = 1;}

private:
	int x;
	int y;
};

#endif /* POS_H_ */
