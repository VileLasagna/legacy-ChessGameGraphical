/*
 * Players.cpp
 *
 *  Created on: 19-Nov-2008
 *      Author: Vile Lasagna
 */


#include "Player.h"

Player::Player (bool colour)
{
	Colour = colour;
	Points = 0;

}

const int Player::getPoints()
{
	return Points;
}

const bool Player::getColour()
{
	return Colour;
}

void Player::resign()
{
	throw resignEvent(Colour);
}

void Player::offerDraw()
{
	throw drawOfferEvent(Colour);
}

void Player::addPoints(int i)
{
	Points += i;
}

resignEvent::resignEvent(bool pl)
{
	p = pl;
}

drawOfferEvent::drawOfferEvent (bool c)
{
	colour = c;
	accepted = false;
}
