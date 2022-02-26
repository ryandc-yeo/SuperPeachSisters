#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(int imageID, int x, int y, StudentWorld* world, int dir = 0, int depth = 0, double size = 1.0)
		: m_alive(true), m_health(1), m_world(world), GraphObject(imageID, x, y, dir, depth, size) {}

	void dead() { m_alive = false; }
	virtual void doSomething() {};
	virtual void bonk(bool isPeachInvincible) {};
	virtual void damaged() {}
	virtual bool blocksMovement() { return false; }

	StudentWorld* getWorld() { return m_world; }
	void setDead() { m_alive = false; }
	void fallIfPossibel(int distance) {}
	void reverseDirection() {}

	bool isAlive() const { return m_alive; }

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

class Goal : public Actor
{
public:
	Goal(int imageID, int x, int y, StudentWorld* world)
		: Actor(imageID, x, y, world, 0, 1, 1.0) {}
};

/*
class Goodie : public Actor
{

};

class Projectile : public Actor
{

};

class Enemy : public Actor
{

};
*/

// Actor classes
class Peach : public Actor
{
public:
	Peach(int x, int y, StudentWorld* world)
		: Actor(IID_PEACH, x, y, world, 0, 0, 1.0), m_invincibleCount(0), m_rechargeTime(0), m_invincible(false), m_tempInvincible(false), m_shootP(false), m_jumpP(false) {}

	virtual void doSomething();
	virtual void bonk() { std::cerr << "bonk" << std::endl; }

	void setInvincibility(int ticks) { m_invincibleCount = ticks;  }
	void setHP(int hp) {}
	void shootPower() { m_shootP = true; }
	void jumpPower() { m_jumpP = true; }
	void losePower()
	{
		m_shootP = false;
		m_jumpP = false;
		setInvincibility(7);
	}

	bool isInvincible() const { return m_invincible; }
	bool isTempInvincible() const { return m_tempInvincible; }
	bool hasShootPower() const { return m_shootP; }
	bool hasJumpPower() const { return m_jumpP; }

private:
	int m_invincibleCount;
	int m_rechargeTime;
	bool m_invincible;
	bool m_tempInvincible;
	bool m_shootP;
	bool m_jumpP;
};

class Block : public Obstacle
{
public:
	Block(int x, int y, StudentWorld* world)
		: Obstacle(IID_BLOCK, x, y, world) {}

	virtual void bonk(bool isPeachInvincible) {}
};

class Pipe : public Obstacle
{
public:
	Pipe(int x, int y, StudentWorld* world)
		: Obstacle(IID_PIPE, x, y, world) {}
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

class PeachFireball : public Projectile
{

};

class PiranhaFireball : public Projectile
{

};

class Shell : public Projectile
{

};

class Star : public Item
{

};

class Flower : public Item
{

};

class Mushroom : public Item
{

};
*/

#endif // ACTOR_H_
