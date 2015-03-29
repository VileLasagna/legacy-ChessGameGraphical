
#include "CBMainState.h"


int CBMainState::Update()
{
	EventHandler::Update();
	if (activePiece)
	{
		

	}
	return ret;
}

CBMainState::CBMainState()
{
	pieceX = 0;
	pieceY = 0;
	BG.Load("Board1.png");
	self = 1;
	ret = 1;
	boardCorner.setX(270);
	boardCorner.setY(150);
	Mouse = Sprite("poker.AnimSheet");
	Mouse.playAnimation(1);
	Mouse.setDrawAlpha(255); //full transparent
	for (int i = 0; i < 64; i++)
	{
		if (i == 32)
		{
			i = 32; //toggle break
		}
		Vec2f sp(boardCorner.X(), boardCorner.Y());
		Vec2f sa( 60*(i%8), 60*(7-(i/8)));
		sp+= sa;
		GB[i] = new Sprite("Highlight.AnimSheet");
		GB[i]->setPos(sp);
		GB[i]->playAnimation(3);
		//GB[i]->setDrawAlpha(128); //not working, can't figure out why right now, but the squares do exist
		
	}
	
	sqSize = 60;
	GameOver = false;
	activePiece = false;
	command = "";
	makePieces();
}

void CBMainState::makePieces()
{
	if( !pieces.empty())
	{
		pieces.clear();
	}
	const BD& fd = bastard.getField();
	for (int i = 1; i <= 8; i++)
	{
		for(int j = 1; j <= 8; j++)
		{
			piece* p = (piece*) fd[i][j].getPiece();
			if(!p)
			{
				continue;
			}
			Sprite* s = new Sprite("Pieces.AnimSheet");
			s->playAnimation(p->getType()+1 + (6*(!p->getColour()))); //set the correct image
			Vec2f pos (boardCorner.X(), boardCorner.Y());
			Vec2f adjust (60*(p->getPos().getX()-1), 60*(8-p->getPos().getY()));
			pos += adjust;
			s->setPos(pos);
			pieces.push_back(s);
		}
	}
}

void CBMainState::Draw()
{
	BG.Blit();
	for(int i = 0; i < 64; i++)
	{
		GB[i]->Draw();
	}
	for(unsigned int i = 0; i < pieces.size(); i++)
	{
		pieces[i]->Draw();
	}

}

void CBMainState::OnMouseButtonEvent(const SDL_MouseButtonEvent& e)
{
	Vec2f p(e.x,e.y);
	Mouse.setPos(p);
	if(e.type == SDL_MOUSEBUTTONUP)
	{
		return;
	}
	if(!activePiece)
	{
		for(unsigned int i = 0; i < pieces.size(); i++)
		{
			if (Mouse.pixCollision(*pieces[i]))
			{
				if((pieces[i]->getAnimation().X()+1)<7)//the piece is white
				{
					if (!bastard.getTurn())
					{
						return;
					}
				}
				else
				{
					if(bastard.getTurn())
					{
						return;
					}
				}


				switch (pieces[i]->getAnimation().X()+1)
				{
				case 1:
				case 7: command.append("p");break;
				case 2:
				case 8:command.append("n");break;
				case 3:
				case 9:command.append("b");break;
				case 4:
				case 10:command.append("r");break;
				case 5:
				case 11:command.append("q");break;
				case 6:
				case 12:command.append("k");break;
				}
				for (int i = 0; i < 64; i++)
				{
					if (Mouse.getBox().intersects(GB[i]->getBox()))
					{
						pieceX = (i%8)+1;
						pieceY = (i/8)+1;
						switch(pieceX)
						{
						case 1: command.append("a");break;
						case 2: command.append("b");break;
						case 3: command.append("c");break;
						case 4: command.append("d");break;
						case 5: command.append("e");break;
						case 6: command.append("f");break;
						case 7: command.append("g");break;
						case 8: command.append("h");break;
						}
						switch(pieceY)
						{
						case 1: command.append("1");break;
						case 2: command.append("2");break;
						case 3: command.append("3");break;
						case 4: command.append("4");break;
						case 5: command.append("5");break;
						case 6: command.append("6");break;
						case 7: command.append("7");break;
						case 8: command.append("8");break;
						}
						GB[i]->playAnimation(4);
						break;
					}
				}
				activePiece = true;
				
				BD testboard = Square::BDClone(bastard.getField());
				for(Pos p(1,1); !p.endboard(); p++)
				{
					if(  ((piece*)bastard.getField()[pieceX][pieceY].getPiece())->canMove(p, testboard)) //if the selected piece can go to the square
					{
						piece* s = (piece*) testboard[p.getX()][p.getY()].getPiece();
						if(!s) //if there's no piece on the square
						{
							GB[((p.getY()-1)*8) + p.getX()-1]->playAnimation(1);
						}
						if(s)
						{
							GB[((p.getY()-1)*8) + p.getX()-1]->playAnimation(2);
						}
					}
				}
			}
		}
	}
	else //there's already an active piece
	{
		for (int i = 0; i < 64; i++)
		{
			if (Mouse.getBox().intersects(GB[i]->getBox()))
			{
				int x = (i%8)+1;
				int y = (i/8)+1;
				switch(x)
				{
				case 1: command.append("a");break;
				case 2: command.append("b");break;
				case 3: command.append("c");break;
				case 4: command.append("d");break;
				case 5: command.append("e");break;
				case 6: command.append("f");break;
				case 7: command.append("g");break;
				case 8: command.append("h");break;
				}
				switch(y)
				{
				case 1: command.append("1");break;
				case 2: command.append("2");break;
				case 3: command.append("3");break;
				case 4: command.append("4");break;
				case 5: command.append("5");break;
				case 6: command.append("6");break;
				case 7: command.append("7");break;
				case 8: command.append("8");break;
				}
				for (int i = 0; i < 64; i++)
				{
					GB[i]->playAnimation(3);
				}
				break;
			}
		}
		try
		{
			if (bastard.Command(command))
			{
				makePieces();
			}

		}
		catch(EndGameEvent e)
		{
			//Show some Splash Screen
		}
		command = "";
		activePiece = false;
	}
}