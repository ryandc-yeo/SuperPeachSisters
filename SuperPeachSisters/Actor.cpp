#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(int imageID, int x, int y, StudentWorld* world, int dir = 0, int depth = 0, double size = 1.0)
	: m_alive(true), m_health(1), m_world(world), GraphObject(imageID, x, y, dir, depth, size) {}

void Goal::doSomething()
{
	if (!isAlive())
		return;
	if (getWorld()->overlapsPeach(this))
	{
		getWorld()->increaseScore(1000);
		setDead();
		if (m_end)
			getWorld()->reachedMario();
		else
			getWorld()->reachedFlag();
	}
}

Peach::Peach(int x, int y, StudentWorld* world)
	: Actor(IID_PEACH, x, y, world, 0, 0, 1.0)
{
	m_invincibleCount = 0;
	m_rechargeTime = 0;
	m_jumpDistance = 0;
	m_starPowerTime = 0;
	m_invincible = false;
	m_tempInvincible = false;
	m_shootP = false;
	m_jumpP = false;
	m_canShoot = false;
}

bool Peach::isJumping()
{
	double x = getX();
	double y = getY();
	if (m_jumpDistance > 0)
	{
		y += 4;
		if (getWorld()->isPeachMovePossible(x, y))
		{
			moveTo(x, y);
			m_jumpDistance--;
			return true;
		}
		else
		{
			getWorld()->bonkObject(x, y);
			m_jumpDistance = 0;
		}
	}
	else
	{
		y -= 4;
		if (getWorld()->isPeachMovePossible(x, y))
			moveTo(x, y);	
		return false;
	}
}

void Peach::giveJumpPower()
{
	m_jumpP = true;
	// setJumpPower(12);
}

void Peach::setInvincibility(int ticks) 
{ 
	m_invincibleCount = ticks; 
	m_invincible = true;
}

void Peach::setTempInvincibility(int ticks)
{
	m_invincibleCount = ticks;
	m_tempInvincible = true;
}

void Peach::shoot()
{
	getWorld()->
}

void Peach::doSomething()
{
	if (!isAlive())		// Check if Peach is alive
		return;

	// Check if Peach is invincible (Star Power)
	if (isInvincible())
	{
		if (m_invincibleCount == 0)
			m_invincible = false;
		else
			m_invincibleCount--;
	}

	// Check if Peach is temporarily invincible
	if (isTempInvincible())
	{
		if (m_invincibleCount == 0)
			m_tempInvincible = false;
		else
			m_invincibleCount--;
	}

	// Check if Peach is in "recharge" mode
	if (m_shootP)
	{
		if (m_rechargeTime > 0)
			m_rechargeTime--;
		else
			m_canShoot = true;
	}

	getWorld()->bonkObject(getX(), getY());
	isJumping();

	// how to deal with immovable

	// Peach movement
	int ch;
	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{
		case KEY_PRESS_UP:
		{
			if (!getWorld()->isPeachMovePossible(getX(), getY() - 3))
			{
				getWorld()->playSound(SOUND_PLAYER_JUMP);
				if (hasJumpPower())
					m_jumpDistance = 12;
				else
					m_jumpDistance = 8;
			}
			break;
		}
		case KEY_PRESS_LEFT:
		{
			setDirection(180);
			if (getWorld()->isPeachMovePossible(getX() - 4, getY())) // not correct, need to include immovable
				moveTo(getX() - 4, getY());
			break;
		}
		case KEY_PRESS_RIGHT:
		{
			setDirection(0);
			if (getWorld()->isPeachMovePossible(getX() + 4, getY()))
				moveTo(getX() + 4, getY());
			break;
		}
		case KEY_PRESS_SPACE:
		{
			if (m_shootP && m_canShoot)
			{
				getWorld()->playSound(SOUND_PLAYER_FIRE);
				m_rechargeTime = 8;
				m_canShoot = false;
				//if (getDirection() == 0)
					// shoot fireball

			}
		}
		default:
			break;
		}
	}
}

void Block::bonk(bool isPeachInvincible)
{
	if (!m_goodieBlock)
		getWorld()->playSound(SOUND_PLAYER_BONK);
	else
	{
		getWorld()->playSound(SOUND_POWERUP_APPEARS);
		getWorld()->addGoodie(m_goodieNo, getX(), getY() + 8);
		m_goodieNo = -1;
		m_goodieBlock = false;
	}
}

void Goodie::doSomething()
{
	if (!isAlive())
		return;

	double x = getX();
	double y = getY();

	if (getWorld()->overlapsPeach(this))
	{
		setDead();
		getWorld()->playSound(SOUND_PLAYER_POWERUP);
	}
	else
	{
		if (getDirection() == 180)
		{
			if (getWorld()->isMovePossible(this, x - 2, y))
				moveTo(x - 2.0, y);
			else
				setDirection(0);
		}
		else if (getDirection() == 0)
		{
			if (getWorld()->isMovePossible(this, x + 2, y))
				moveTo(x + 2.0, y);
			else
				setDirection(180);
		}

		if (getWorld()->isMovePossible(this, x, y - 2))
		{
			moveTo(x, y - 2.0);
		}
	}
}

void Flower::doSomething()
{
	if (getWorld()->overlapsPeach(this))
	{
		getWorld()->increaseScore(50);
		getWorld()->grantShootPower();
		getWorld()->setPeachHP(2);
	}
	Goodie::doSomething();
}

void Mushroom::doSomething()
{
	if (getWorld()->overlapsPeach(this))
	{
		getWorld()->increaseScore(75);
		getWorld()->grantJumpPower();
		getWorld()->setPeachHP(2);
	}
	Goodie::doSomething();
}

void Star::doSomething()
{
	if (getWorld()->overlapsPeach(this))
	{
		getWorld()->increaseScore(100);
		getWorld()->grantInvincibility(150);
	}
	Goodie::doSomething();
}

void PiranhaFireball::doSomething()
{
	int x = getX();
	int y = getY();

	if (getWorld()->overlapsPeach(this))
	{
		getWorld()->damagePeach();
		setDead();
	}
	else
	{
		if (getDirection() == 180)
		{
			if (getWorld()->isMovePossible(this, x - 2, y))
				moveTo(x - 2.0, y);
			else
				setDead();
		}
		else if (getDirection() == 0)
		{
			if (getWorld()->isMovePossible(this, x + 2, y))
				moveTo(x + 2.0, y);
			else
				setDead();
		}

		if (getWorld()->isMovePossible(this, x, y - 2))
		{
			moveTo(x, y - 2.0);
		}
	}
}

void PeachFireball::doSomething()
{
	int x = getX();
	int y = getY();

	if (getWorld()->overlapsPeach(this))
	{
		getWorld()->damagePeach();
		setDead();
	}
	else
	{
		if (getDirection() == 180)
		{
			if (getWorld()->isMovePossible(this, x - 2, y))
				moveTo(x - 2.0, y);
			else
				setDead();
		}
		else if (getDirection() == 0)
		{
			if (getWorld()->isMovePossible(this, x + 2, y))
				moveTo(x + 2.0, y);
			else
				setDead();
		}

		if (getWorld()->isMovePossible(this, x, y - 2))
		{
			moveTo(x, y - 2.0);
		}
	}
}