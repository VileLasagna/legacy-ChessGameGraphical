/*
 * GameState.h
 *
 *  Created on: 10-Nov-2008
 *      Author: Vile Lasagna
 */

#ifndef CHESSTATE_H_
#define CHESSTATE_H_

#include <string>
#include "Board.h"
#include "Player.h"
#include <iostream>


typedef std::string String;
typedef std::vector<Square> column;
typedef std::vector<column> BD;

class ChessState
{
public:

	bool Command(String s); //true if the command was executed (i.e: it's now the other player's turn)
	const bool getTurn();
	ChessState();
	std::vector<int> getScore();
	const BD& getField(); //this is needed for the drawing method, however there is not much getting away from violating data protection because of getPiece(). I fail at neatness T_T
	Player getPlayer(bool c);
	void getWin();
	int getCheck(); // 0 -> Normal; 1 -> White is in check; 2 -> Black is in check; This is used by ChessText::paint();

private:

	bool isNumber(char c);
	void trim(std::vector<char>& c);
	std::vector<char> three_moves [4];
	bool turn;
	int fifty_move;
	int threefold;
	Board GameBoard;
	std::vector<String> history;
	Player players[2];
	const bool CompareCMD(std::vector<char> c1, std::vector<char> c2);



};

class EndGameEvent
{
public:
	//I never got around to implement checking for insufficient material
	enum result {WHITE, BLACK, DRAW};
	enum reason {MATE, RESIGN, AGREE, FIFTY_MOVE, THREEFOLD, STALE, INSUFFICIENT};
	EndGameEvent(EndGameEvent::result w, EndGameEvent::reason r);
	EndGameEvent::reason getReason();
	EndGameEvent::result getResult();


private:

	EndGameEvent::reason how;
	EndGameEvent::result who;
};


#endif /* CHESSTATE_H_ */
