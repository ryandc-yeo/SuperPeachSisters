#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

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
	if (m_rechargeTime > 0)
		m_rechargeTime--;

	// if recharge == 0 and shootPower, Peach may shoot a fireball

	// Check if Peach overlaps with any other game objects
	/*
	if (!getWorld()->isPeachMovePossible())
	{
		bonk();
	}
	*/

	// how to deal with immovable

	// Peach movement
	int ch;
	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{
		case KEY_PRESS_UP:
		{
			if (getWorld()->isPeachMovePossible(getX(), getY() + 4))
				moveTo(getX(), getY() + 4);
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
		default:
			break;
		}
	}
}
