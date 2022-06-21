/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <Events.h>
#include "LowPowerEntity.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void LowPowerEntity::constructor(const LowPowerEntitySpec* LowPowerEntitySpec, int16 internalId, const char* const name)
{
	// construct base object
	Base::constructor((AnimatedEntitySpec*)LowPowerEntitySpec, internalId, name);

	// init class variables
	this->lowPowerDuration = 0;

	// add event listeners
	Clock::addEventListener(Game::getClock(Game::getInstance()), ListenerObject::safeCast(this), (EventListener)LowPowerEntity::onSecondChange, kEventSecondChanged);
}

// class's destructor
void LowPowerEntity::destructor()
{
	// remove event listeners
	Clock::removeEventListener(Game::getClock(Game::getInstance()), ListenerObject::safeCast(this), (EventListener)LowPowerEntity::onSecondChange, kEventSecondChanged);

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void LowPowerEntity::onSecondChange(ListenerObject eventFirer __attribute__ ((unused)))
{
	// poll the user's input
	UserInput userInput = KeypadManager::getUserInput(KeypadManager::getInstance());

	// check low power flag
	if(userInput.powerFlag)
	{
		if(this->lowPowerDuration >= __LOW_POWER_ENTITY_FLASH_DELAY - 1)
		{
			AnimatedEntity::playAnimation(this, "Flash");
		}
		else
		{
			this->lowPowerDuration++;
			AnimatedEntity::playAnimation(this, "Hide");
		}
	}
	else
	{
		this->lowPowerDuration = 0;
		AnimatedEntity::playAnimation(this, "Hide");
	}
}
