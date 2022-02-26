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

	bool isMovePossible(Actor* a, int x, int y);
	bool moveIfPossible(Actor* a, int x, int y) {}
	void addActor(Actor* a) {}
	void endLevel(bool isGameWon) {}
	bool moveOrBonk(Actor* a, int x, int y);
	bool bonkOverlappingPeach(Actor* bonker) const;
	void bonkOverlappingActor(Actor* bonker) const {}
	bool damageOverlappingPeach(Actor* damager) const {}
	bool damageOverlappingActor(Actor* damager) const {}
	bool overlapsPeach(Actor* a) const;
	bool getPeachTargetingInfo(Actor* a, int yDetlaLimit, int& xDeltaFromActor) const {}
	void setPeachHP(int hp) const {}
	void grantInvincibility(int ticks) const {}
	void grantShootPower() const {}
	void grantJumpPower() const {}

	bool isPeachMovePossible(int x, int y);
private:
	Peach* peach;
	std::vector<Actor*> actor;
};

#endif // STUDENTWORLD_H_