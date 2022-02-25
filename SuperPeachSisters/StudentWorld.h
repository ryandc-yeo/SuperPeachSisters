#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <vector>

class Actor;
class Peach;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetPath);
	~StudentWorld() { cleanUp(); }

	virtual int init();
	virtual int move();
	virtual void cleanUp();

	bool isObject(int x, int y);
private:
	Peach* peach;
	std::vector<Actor*> actor;
};

#endif // STUDENTWORLD_H_