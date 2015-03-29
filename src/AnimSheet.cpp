
#include "AnimSheet.h"
#include <assert.h>




AnimSheet::AnimSheet(std::string filename)
{
	std::ifstream infile;
	infile.open(filename.c_str());
	assert(infile);
	std::string line;
	pass = -1;
	while (std::getline(infile, line))
	{
		if( StringProc::trim(&line) && (line.at(0) != '#') )
		{
			if(line.length() > 0)
			{
				loadseq(line);
			}
		}
	}

	infile.close();
}


void AnimSheet::loadseq(const std::string& s)
{
	if (pass == -1) {pass = 0;}

	switch (pass)
	{
	case 0:
		{
			Load(s);
			pass++;
			break;
		}
	case 1:
		{
			setNumCells( StringProc::parseVec2i(s));
			pass++;
			break;
		}
	case 2:
		{
			adjust = StringProc::parseVec2i(s);
			pass++;
			break;
		}
	case 3:
		{
			anims = StringProc::parseInt(s);
			lengths = new int[anims];
			//animations.reserve(anims);//cut away some of the overhead introduced by vector
			for(int i = 0; i < anims; i++)
			{
				std::vector<Vec2i> v;
				animations.push_back(v);
			}
			pass++;
			break;
		}
	default:
		{
			//starts happening when pass == 4;
			static bool isStart = true;
			static Vec2i startPos(0,0);
			if (isStart)
			{
				startPos = StringProc::parseVec2i(s);
			}
			else
			{
				int atAnim = ((pass-4)/2); //the current animation index
				Vec2i endPos = StringProc::parseVec2i(s);
				Vec2i current = startPos;
				lengths[atAnim] = (numCells.X() - startPos.X() + 1) + ((endPos.Y() - startPos.Y() - 1)*numCells.X()) + endPos.X();
				//animations[atAnim].reserve(lengths[atAnim]);//again, cutting overhead forced upon the program by C++'s clumsy array management
				for (int i = 0; i < lengths[atAnim]; i++)
				{
					animations[atAnim].push_back(Vec2i(0,0));
				}
				for(int i = 0; i < lengths[atAnim]; i++)
				{
					animations[atAnim][i] = current;
					current = nextSprite(current);
				}
			}
			isStart = !isStart;
			pass++;
			break;
		}
	}
}


Vec2i AnimSheet::nextSprite(Vec2i current) const
{
	if (current.X() != numCells.X())
	{
		current.setX(current.X()+1);
	}
	else
	{
		current.setX(0);
		if ( current.Y() != numCells.Y())
		{
			current.setY(current.Y()+1);
		}
		else
		{
			current.setY(0);
		}
	}
	return current;
}

std::vector<Vec2 <Vec2i> > AnimSheet::getAnims() const
{
	std::vector<Vec2<Vec2i> > ret;
	for(unsigned int i = 0; i < animations.size(); i++)
	{
		Vec2<Vec2i> v(animations[i][0],animations[i][animations[i].size()-1]);
		ret.push_back(v);
	}
	return ret;
}

int AnimSheet::getCellIndex(const Vec2i &cell) const
{
	int i = 0;
	Vec2i tc(1,1);
	while (tc != cell)
	{
		tc = nextSprite(tc);
		i++;
	}
	return i;
}

