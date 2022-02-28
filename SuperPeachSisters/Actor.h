#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(int imageID, int x, int y, StudentWorld* world, int dir, int depth, double size);

	virtual void doSomething() {};
	virtual void bonk(bool isPeachInvincible) {};
	virtual void damaged() { m_health--; }
	virtual bool blocksMovement() const { return false; }

	StudentWorld* getWorld() { return m_world; }
	void setDead() { m_alive = false; }
	void fallIfPossibel(int distance) {}
	void reverseDirection() {}

	bool isAlive() const { return m_alive; }
	void setHealth(int hp) { m_health = hp; }

private:
	bool m_alive;
	int m_health;
	StudentWorld* m_world;
};

// Separate Actor classes into categories except Peach
class Obstacle : public Actor
{
public:
	Obstacle(int imageID, int x, int y, StudentWorld* world)
		: Actor(imageID, x, y, world, 0, 2, 1.0) {}
	virtual bool blocksMovement() const { return true; }
};

class Goal : public Actor	// includes Flag and Mario
{
public:
	Goal(int imageID, int x, int y, StudentWorld* world, bool end)
		: Actor(imageID, x, y, world, 0, 1, 1.0), m_end(end) {}

	virtual void doSomething();
private:
	bool m_end;
};

class Goodie : public Actor
{
public:
	Goodie(int imageID, int x, int y, StudentWorld* world)
		: Actor(imageID, x, y, world, 0, 1, 1.0) {}

	virtual void doSomething();
};

class Projectile : public Actor
{
public:
	Projectile(int imageID, int x, int y, StudentWorld* world, int dir)
		: Actor(imageID, x, y, world, dir, 1, 1.0) {}
};
/*
class Enemy : public Actor
{

};
*/

// Actor classes
class Peach : public Actor
{
public:
	Peach(int x, int y, StudentWorld* world);

	virtual void doSomething();
	virtual void bonk() { std::cerr << "bonk" << std::endl; }

	void setInvincibility(int ticks);
	void setTempInvincibility(int ticks);
	void setHP(int hp) {}
	void giveShootPower() { m_shootP = true; }
	void giveJumpPower();
	void losePower()
	{
		m_shootP = false;
		m_jumpP = false;
		setInvincibility(7);
		// setJumpPower(8);
	}
	
	void shoot();

	bool isJumping();
	bool isInvincible() const { return (m_invincible || m_tempInvincible); }
	bool isTempInvincible() const { return m_tempInvincible; }
	bool hasShootPower() const { return m_shootP; }
	bool hasJumpPower() const { return m_jumpP; }

private:
	int m_invincibleCount;
	int m_rechargeTime;
	int m_jumpDistance;
	int m_starPowerTime;
	bool m_invincible;
	bool m_tempInvincible;
	bool m_shootP;
	bool m_jumpP;
	bool m_canShoot;
};

class Block : public Obstacle
{
public:
	Block(int x, int y, StudentWorld* world)
		: Obstacle(IID_BLOCK, x, y, world), m_goodieNo(-1), m_goodieBlock(false) {}

	Block(int x, int y, StudentWorld* world, int goodieNo)
		: Obstacle(IID_BLOCK, x, y, world), m_goodieNo(goodieNo), m_goodieBlock(true) {}

	virtual void bonk(bool isPeachInvincible);
private:
	int m_goodieNo;
	bool m_goodieBlock;
};

class Pipe : public Obstacle
{
public:
	Pipe(int x, int y, StudentWorld* world)
		: Obstacle(IID_PIPE, x, y, world) {}
};

class Flower : public Goodie
{
public:
	Flower(int x, int y, StudentWorld* world)
		: Goodie(IID_FLOWER, x, y, world) {}

	virtual void doSomething();
};

class Mushroom : public Goodie
{
public:
	Mushroom(int x, int y, StudentWorld* world)
		: Goodie(IID_MUSHROOM, x, y, world) {}

	virtual void doSomething();
};

class Star : public Goodie
{
public:
	Star(int x, int y, StudentWorld* world)
		: Goodie(IID_STAR, x, y, world) {}

	virtual void doSomething();
};

class PiranhaFireball : public Projectile
{
	PiranhaFireball(int x, int y, StudentWorld* world, int dir)
		: Projectile(IID_PIRANHA_FIRE, x, y, world, dir) {}

	virtual void doSomething();
};

class PeachFireball : public Projectile
{
	PeachFireball(int x, int y, StudentWorld* world, int dir)
		: Projectile(IID_PEACH_FIRE, x, y, world, dir) {}

	virtual void doSomething();
};

/*
class Goomba : public Character
{

};

class Koopa : public Character
{

};

class Piranha : public Character
{

};

class Shell : public Projectile
{

};
*/

#endif // ACTOR_H_
