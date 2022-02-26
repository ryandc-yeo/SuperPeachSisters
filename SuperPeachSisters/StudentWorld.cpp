#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
	// initialize the data structures used to keep track of your game's world.

	// Allocate and insert a Peach object into the game world. Everytime a level starts/restarts, 
	// Peach starts out fully initialized (with the no special powers active, etc.) in her initial
	// location as specified by the current level data file.

	// Allocate and insert all of the blocks, pipes, flags, enemies and Mario into the game world as
	// described below.
	Level lev(assetPath());
	string level_file = "level01.txt";
	Level::LoadResult result = lev.loadLevel(level_file);
	if (result == Level::load_fail_file_not_found)
		cerr << "Could not find level01.txt data file" << endl;
	else if (result == Level::load_fail_bad_format)
		cerr << "level01.txt is improperly formatted" << endl;
	else if (result == Level::load_success)
	{
		cerr << "Successfully loaded level" << endl;
		for (int i = 0; i < GRID_WIDTH; i++)
		{
			for (int j = 0; j < GRID_HEIGHT; j++)
			{
				Level::GridEntry ge;
				ge = lev.getContentsOf(i, j);
				switch (ge)
				{
				case Level::empty:
					break;
				case Level::peach:
				{
					peach = new Peach(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
					break;
				}
				case Level::block:
				{
					actor.push_back(new Block(i* SPRITE_WIDTH, j* SPRITE_HEIGHT, this));
					break;
				}
				case Level::pipe:
				{
					actor.push_back(new Pipe(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
					break;
				}
				case Level::flag:
				{
					actor.push_back(new Goal(IID_FLAG, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
					break;
				}
				case Level::mario:
				{
					actor.push_back(new Goal(IID_MARIO, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
					break;
				}
				}
			}
		}
	}

	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	if (peach->isAlive())
	{
		peach->doSomething();

		if (!peach->isAlive())
		{
			// play dying sound
			playSound(SOUND_PLAYER_DIE); // check if works
			return GWSTATUS_PLAYER_DIED;
		}
	}

	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	delete peach;

	for (int i = 0; i < actor.size(); i++)
		delete actor[i];

	actor.clear();
}

// If a can move to (destx,destx), return true (but don't move it); otherwise (it would be blocked), return false
bool StudentWorld::isMovePossible(Actor* a, int x, int y)
{
	return true;
}



// If Peach overlaps bonker, bonk 'er and return true; otherwise, return false
bool StudentWorld::bonkOverlappingPeach(Actor* bonker) const
{
	if (overlapsPeach(bonker))
	{
		peach->bonk();
		return true;
	}
	else
		return false;
}

// Return true if a overlaps Peach; otherwise, return false
bool StudentWorld::overlapsPeach(Actor* a) const
{
	double distanceX = a->getX() - peach->getX();
	double distanceY = a->getY() - peach->getY();

	if (distanceX < (SPRITE_WIDTH - 1) && distanceX > -(SPRITE_WIDTH + 1))
	{
		if (distanceY < (SPRITE_HEIGHT - 1) && distanceY > -(SPRITE_HEIGHT + 1))
		{
			return true;
		}
	}

	return false;
}

// Return false if Peach's intended position is occupied 
bool StudentWorld::isPeachMovePossible(int x, int y)
{
	for (int i = 0; i < actor.size(); i++)
	{
		/**/
		double distanceX = actor[i]->getX() - x;
		double distanceY = actor[i]->getY() - y;

		if (-(SPRITE_WIDTH - 1) <= distanceX && distanceX <= (SPRITE_WIDTH - 1) && -(SPRITE_HEIGHT - 1) <= distanceY && distanceY <= (SPRITE_HEIGHT - 1))
		{
			return false;	// might have to do another check if the object is passable or not
		}

		//if (moveOrBonk(actor[i], x, y))
			//return true;
	}

	return true;
}

// If a can move to (destx,desty), move it and return true; otherwise bonk the object that's blocking it and return false
bool StudentWorld::moveOrBonk(Actor* a, int x, int y)
{
	double distanceX = a->getX() - x;
	double distanceY = a->getY() - y;

	if (distanceX <= (SPRITE_WIDTH - 1) && -(SPRITE_WIDTH + 4) <= distanceX && distanceY <= (SPRITE_HEIGHT - 1) && -(SPRITE_HEIGHT + 1) <= distanceY)
		return true;

	return false;
}