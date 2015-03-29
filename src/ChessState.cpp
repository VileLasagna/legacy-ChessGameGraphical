/*
 * GameState.cpp
 *
 *  Created on: 25-Nov-2008
 *      Author: Vile Lasagna
 */


#include "ChessState.h"




EndGameEvent::EndGameEvent (EndGameEvent::result w, EndGameEvent::reason r)
{
	who = w;
	how = r;
}

EndGameEvent::reason EndGameEvent::getReason()
{
	return how;
}

EndGameEvent::result EndGameEvent::getResult()
{
	return who;
}

ChessState::ChessState()
{
	//std::cout<<"GameStateConstructor START!"<<std::endl;
	turn = true;
	fifty_move = 0;
	threefold = 0;
	players[0] = Player(true);
	players[1] = Player(false);
	//std::cout<<"GameStateConstructor END!"<<std::endl;
}

Player ChessState::getPlayer(bool c)
{
	return players[!c];
}

const BD& ChessState::getField()
{
	return GameBoard.getField();
}

const bool ChessState::CompareCMD(std::vector<char> c1, std::vector<char> c2)
{
	if (c1.size() != c2.size())
	{
		return false;
	}
	else
	{
		for (unsigned int i = 0; i < c1.size(); i++)
		{
			if (c1[i] != c2[i])
			{
				return false;
			}
		}
	}
	return true;
}

const bool ChessState::getTurn()
{
	return turn;
}

void ChessState::getWin()
{
	BD& fd = GameBoard.getField();
	if (GameBoard.getStale(true))
	{
		if (GameBoard.getKing(true)->getCheck(fd))
		{
			throw EndGameEvent(EndGameEvent::BLACK, EndGameEvent::MATE);
		}
		else
		{
			throw EndGameEvent(EndGameEvent::DRAW, EndGameEvent::STALE);
		}
	}
	else
	{
		if (GameBoard.getStale(false))
		{
			if (GameBoard.getKing(false)->getCheck(fd))
			{
				throw EndGameEvent(EndGameEvent::WHITE, EndGameEvent::MATE);
			}
			else
			{
				throw EndGameEvent(EndGameEvent::DRAW, EndGameEvent::STALE);
			}
		}
	}
}

int ChessState::getCheck()
{
	BD& fd = GameBoard.getField();
	try 
	{
		getWin();
	}
	catch (EndGameEvent e)
	{
		return 0; //information is redundant;
	}
	if (GameBoard.getKing(true)->getCheck(fd))
	{
		return 1;
	}
	if (GameBoard.getKing(false)->getCheck(fd))
	{
		return 2;
	}
	return 0;
}
		

bool ChessState::Command(String s)
{
	std::vector<char> cmd;
	Pos from;
	Pos to;
	char c;
	int i = 0;
	while(true)
	{
		c = s[i];
		i++;
		if (c)
		{
			cmd.push_back(c);
		}
		else
		{
			break;
		}
	}
	if ((s == "resign") || (s == "Resign") || (s == "RESIGN"))
	{
		if (turn)
		{
			throw EndGameEvent(EndGameEvent::BLACK, EndGameEvent::RESIGN);
		}
		else
		{
			throw EndGameEvent(EndGameEvent::WHITE, EndGameEvent::RESIGN);
		}
		return true;
	}
	if ((s == "draw") || (s == "Draw") || (s == "DRAW"))
	{
		String players[] = {"White", "Black"};
		std::cout<< std:: endl << std::endl;
		std::cout<< players[!turn] << ", your opponent offers a draw. Do you accept? (Yes/No)" << std::endl;
		String s;
		while ((s.length() < 1) || ((s[0] != 'y') && (s[0] != 'Y') && (s[0] != 'n') && (s[0] != 'N')))
		{
			std::cin>> s;
		}
		if ((s[0] == 'y') || (s[0] == 'Y'))
		{
			throw EndGameEvent (EndGameEvent::DRAW, EndGameEvent::AGREE);
		}
		else
		{
			return false;
		}
	}
	if ((s == "O-O-O")|| (s == "o-o-o")||(s == "0-0-0"))
	{
		int y = 1;
		if (!turn)
		{
			y = 8;
		}
		from = Pos(5,y);
		to = Pos(3,y);
		bool result = GameBoard.movePiece(from,to, turn);
		if (result)
		{
			turn = !turn;
			history.push_back(s);
			fifty_move++;
			threefold = 0; //you can't castle multiple times...
		}
		return result;
	}
	if ((s == "O-O")|| (s == "o-o") || (s == "0-0"))
	{
		int y = 1;
		if (!turn)
		{
			y = 8;
		}
		from = Pos(5,y);
		to = Pos(7,y);
		bool result = GameBoard.movePiece(from, to, turn);
		if (result)
		{
			turn = !turn;
			history.push_back(s);
			fifty_move++;
			threefold = 0; //you can't castle multiple times...
		}
		return result;
	}
	trim(cmd);
	if (cmd.size() < 3)
	{
		return false;
	}
	pieceID::Type t = pieceID::UNDEFINED;
	//let's see WHAT we're moving...
	int cmditerator = 0;
	switch (cmd[cmditerator])
	{
	case 'b': t = pieceID::Bishop; break;
	case 'p': t = pieceID::Pawn; break;
	case 'n': t = pieceID::Knight; break;
	case 'k': t = pieceID::King; break;
	case 'r': t = pieceID::Rook; break;
	case 'q': t = pieceID::Queen; break;
	default: return false;
	}
	cmditerator++;
	int locale = 0;
	bool localeType = false;
	if (cmd.size() >= 4)
	{
		switch (cmd[cmditerator])
		{
		case 'a': locale = 1; break;
		case 'b': locale = 2; break;
		case 'c': locale = 3; break;
		case 'd': locale = 4; break;
		case 'e': locale = 5; break;
		case 'f': locale = 6; break;
		case 'g': locale = 7; break;
		case 'h': locale = 8; break;
		case '1': locale = 1; localeType = true; break;
		case '2': locale = 2; localeType = true; break;
		case '3': locale = 3; localeType = true; break;
		case '4': locale = 4; localeType = true; break;
		case '5': locale = 5; localeType = true; break;
		case '6': locale = 6; localeType = true; break;
		case '7': locale = 7; localeType = true; break;
		case '8': locale = 8; localeType = true; break;
		default: return false;
		}
		cmditerator++;
	}
	if(cmd.size() == 5)
	{
		switch (cmd[cmditerator])
		{
		case '1': from = Pos (locale, 1); break;
		case '2': from = Pos (locale, 2); break;
		case '3': from = Pos (locale, 3); break;
		case '4': from = Pos (locale, 4); break;
		case '5': from = Pos (locale, 5); break;
		case '6': from = Pos (locale, 6); break;
		case '7': from = Pos (locale, 7); break;
		case '8': from = Pos (locale, 8); break;
		default: return false;
		}
		cmditerator++;
	}
	int toX = 0;
	int toY = 0;
	switch (cmd[cmditerator])
	{
	case 'a': toX = 1; break;
	case 'b': toX = 2; break;
	case 'c': toX = 3; break;
	case 'd': toX = 4; break;
	case 'e': toX = 5; break;
	case 'f': toX = 6; break;
	case 'g': toX = 7; break;
	case 'h': toX = 8; break;
	default: return false;
	}
	cmditerator++;
	switch (cmd[cmditerator])
	{
	case '1': toY = 1; break;
	case '2': toY = 2; break;
	case '3': toY = 3; break;
	case '4': toY = 4; break;
	case '5': toY = 5; break;
	case '6': toY = 6; break;
	case '7': toY = 7; break;
	case '8': toY = 8; break;
	default: return false;
	}
	to = Pos(toX, toY);
	bool ret = false;
	try
	{
		switch (cmd.size())
		{
		case 3: ret = GameBoard.movePiece(t, turn, to);break;
		case 4: ret = GameBoard.movePiece(t, turn, locale, localeType, to);break;
		case 5: ret = GameBoard.movePiece(from, to, turn);break;
		default: return false;
		}
	}
	catch (FiftyResetEvent e)
	{
		fifty_move = 0;
	}
	catch (deadPieceEvent e)
	{
		fifty_move = 0;
		players[(!(e.id->getColour()))].addPoints(e.id->getValue());
	}
	if (ret)
	{
		if (threefold < 1)
		{
			three_moves[!turn] = cmd;
		}
		else
		{
			if( CompareCMD( cmd, three_moves[(threefold%4)]))
			{
				threefold++;
			}
			else
			{
				threefold = 0;
				three_moves[!turn] = cmd;
			}
		}
		if(threefold > 11)
		{
			throw EndGameEvent(EndGameEvent::DRAW, EndGameEvent::THREEFOLD);
		}
		turn = !turn;
	}
	return ret;
}


bool ChessState::isNumber(char c)
{
	switch (c)
	{
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8': return true;
	default: return false;
	}

}

void ChessState::trim(std::vector<char>& c)
{
	for (int i = (c.size()-1); i >=0; i--)
	{
		switch (c[i])
		{
			case 'a':
			case 'A': c[i] = 'a'; continue;
			case 'b':
			case 'B': c[i] = 'b'; continue;
			case 'c':
			case 'C': c[i] = 'c'; continue;
			case 'd':
			case 'D': c[i] = 'd'; continue;
			case 'e':
			case 'E': c[i] = 'e'; continue;
			case 'f':
			case 'F': c[i] = 'f'; continue;
			case 'g':
			case 'G': c[i] = 'g'; continue;
			case 'h':
			case 'H': c[i] = 'h'; continue;
			case 'p':
			case 'P': c[i] = 'p'; continue;
			case 'n':
			case 'N': c[i] = 'n'; continue;
			case 'k':
			case 'K': c[i] = 'k'; continue;
			case 'r':
			case 'R': c[i] = 'r'; continue;
			case 'q':
			case 'Q': c[i] = 'q'; continue;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8': continue;
			default: c.erase((c.begin()+i)); continue;
		}
	}
}

std::vector<int> ChessState::getScore()
{
	std::vector<int> score;
	score.push_back(players[0].getPoints());
	score.push_back(players[1].getPoints());
	return score;
}
