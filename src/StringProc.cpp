
#include "StringProc.h"


bool StringProc::trim(std::string *s)
//A pointer is used here instead of a reference just so that the
//user is reminded every time that he writes a call to this funcion:
// "Hey, I AM going to mess up this string you're giving me!"
{
	std::string::iterator it = s->begin();
	while( !s->empty() && it != s->end())
	{
		if (*it == ' ')
		{
			it = s->erase(it);
		}
		else
		{
			it++;
		}
	}
	return !s->empty();
}

int StringProc::parseInt(const std::string& s)
{
	const char* c = s.c_str();
	int res = 0;
	while (*c)
	{
		res *=10;
		switch (*c)
		{
		case '1': {res += 1; break;}
		case '2': {res += 2; break;}
		case '3': {res += 3; break;}
		case '4': {res += 4; break;}
		case '5': {res += 5; break;}
		case '6': {res += 6; break;}
		case '7': {res += 7; break;}
		case '8': {res += 8; break;}
		case '9': {res += 9; break;}
		case '0': {break;}
		default: {assert (0);break;}//bad format!
		}
		c++;
	}
	return res;
}

Vec2i StringProc::parseVec2i(const std::string& s)
{
	int pos = s.find(",");
	int vx = parseInt(s.substr(0,pos));
	int vy = parseInt(s.substr(pos + 1)); 
	Vec2i ret(vx,vy);
	return ret;
}

void StringProc::lowerCase(std::string *s)
{
	const char* a = s->c_str();
	char* c = new char[s->length()+1];
	for(unsigned int i = 0; i < s->length(); i++)
	{
		c[i] = a[i];
	}
	c[s->length()] = 0;
	int j = 0;
	while(c[j])
	{
		switch (c[j])
		{
		case('A'): {c[j] = 'a';break;}
		case('B'): {c[j] = 'b';break;}
		case('C'): {c[j] = 'c';break;}
		case('D'): {c[j] = 'd';break;}
		case('E'): {c[j] = 'e';break;}
		case('F'): {c[j] = 'f';break;}
		case('G'): {c[j] = 'g';break;}
		case('H'): {c[j] = 'h';break;}
		case('I'): {c[j] = 'i';break;}
		case('J'): {c[j] = 'j';break;}
		case('K'): {c[j] = 'k';break;}
		case('L'): {c[j] = 'l';break;}
		case('M'): {c[j] = 'm';break;}
		case('N'): {c[j] = 'n';break;}
		case('O'): {c[j] = 'o';break;}
		case('P'): {c[j] = 'p';break;}
		case('Q'): {c[j] = 'q';break;}
		case('R'): {c[j] = 'r';break;}
		case('S'): {c[j] = 's';break;}
		case('T'): {c[j] = 't';break;}
		case('U'): {c[j] = 'u';break;}
		case('V'): {c[j] = 'v';break;}
		case('X'): {c[j] = 'x';break;}
		case('W'): {c[j] = 'w';break;}
		case('Y'): {c[j] = 'y';break;}
		case('Z'): {c[j] = 'z';break;}
		default: {break;}
		}
		j++;
	}
	*s = std::string(c);
	return;
}

void StringProc::upperCase(std::string *s)
{
	const char* a = s->c_str();
	char* c = new char[s->length()+1];
	for(unsigned int i = 0; i < s->length(); i++)
	{
		c[i] = a[i];
	}
	c[s->length()] = 0;
	int j = 0;
	while(c[j])
	{
		switch (c[j])
		{
		case('a'): {c[j] = 'A';break;}
		case('b'): {c[j] = 'B';break;}
		case('c'): {c[j] = 'C';break;}
		case('d'): {c[j] = 'D';break;}
		case('e'): {c[j] = 'E';break;}
		case('f'): {c[j] = 'F';break;}
		case('g'): {c[j] = 'G';break;}
		case('h'): {c[j] = 'H';break;}
		case('i'): {c[j] = 'I';break;}
		case('j'): {c[j] = 'J';break;}
		case('k'): {c[j] = 'K';break;}
		case('l'): {c[j] = 'L';break;}
		case('m'): {c[j] = 'M';break;}
		case('n'): {c[j] = 'N';break;}
		case('o'): {c[j] = 'O';break;}
		case('p'): {c[j] = 'P';break;}
		case('q'): {c[j] = 'Q';break;}
		case('r'): {c[j] = 'R';break;}
		case('s'): {c[j] = 'S';break;}
		case('t'): {c[j] = 'T';break;}
		case('u'): {c[j] = 'U';break;}
		case('v'): {c[j] = 'V';break;}
		case('x'): {c[j] = 'X';break;}
		case('w'): {c[j] = 'W';break;}
		case('y'): {c[j] = 'Y';break;}
		case('z'): {c[j] = 'Z';break;}
		default: {break;}
		}
		j++;
	}
	*s = std::string(c);
	return;
}

std::string StringProc::lowerCopy(const std::string &s)
{
	std::string ret = s;
	StringProc::lowerCase(&ret);
	return ret;
}

std::string StringProc::upperCopy(const std::string &s)
{
	std::string ret = s;
	StringProc::upperCase(&ret);
	return ret;
}

bool StringProc::equalsIgnoreCase(const std::string &a, const std::string &b)
{
	if( a.length() != b.length()) {return false;}
	std::string A = StringProc::lowerCopy(a);
	std::string B = StringProc::upperCopy(b);
	return (!a.compare(b));
}
