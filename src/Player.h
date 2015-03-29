/*
 * player.h
 *
 *  Created on: 27-Oct-2008
 *      Author: Vile Lasagna
 */

#ifndef PLAYER_H_
#define PLAYER_H_

class Player
{
public:

	const bool getColour ();
	const int getPoints();
	//time was scrapped for now
	void resign();
	Player (bool colour = true);
	void offerDraw();
	void addPoints(int i);

private:

	bool Colour;
	int Points;




};

class resignEvent
{
public:
	resignEvent (bool colour);
	bool p;
};

class drawOfferEvent
{
public:

	drawOfferEvent(bool c);
	bool colour;
	bool accepted;

};

#endif /* PLAYER_H_ */
