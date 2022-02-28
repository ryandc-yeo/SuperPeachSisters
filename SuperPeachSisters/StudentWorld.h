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

	void gameStat();

	void addActor(Level::GridEntry ge, int i, int j);
	void addObject(int object, int x, int y, int dir);
	bool moveOrBonk(Actor* a, int x, int y);
	void bonkObject(double x, double y);

	bool overlapsPeach(Actor* a) const;
	bool overlapsAt(Actor* a, double x, double y) const;

	void reachedFlag() { m_nextLevel = true; }
	void reachedMario() { m_win = true; }
	void grantShootPower() const;
	void grantJumpPower() const;
	void grantInvincibility(int ticks) const;
	void setPeachHP(int hp) const;
	void damagePeach();
	void damageObject(Actor* a);

	bool isPeachMovePossible(int x, int y);
	bool isMovePossible(Actor* a, int x, int y);
	bool damageIfPossible(Actor* a, int x, int y);
private:
	Peach* m_peach;
	std::vector<Actor*> m_actor;
	bool m_nextLevel;
	bool m_win;
};

#endif // STUDENTWORLD_H_