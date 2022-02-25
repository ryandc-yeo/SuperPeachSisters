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
					actor.push_back(new Pipe(i * SPRITE_WIDTH, j * SPRITE_HEIGHT - 1, this));
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

bool StudentWorld::isObject(int x, int y)
{
	int size = actor.size();

	for (int i = 0; i < size; i++)
	{
		if (x > actor[i]->getX() && x < (actor[i]->getX() + SPRITE_WIDTH - 1))
		{
			if (y >= actor[i]->getY() && y < (actor[i]->getY() + SPRITE_HEIGHT - 1))
				return true;
		}
	}

	return false;
}