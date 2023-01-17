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

#include <VUEngine.h>
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

	// add event listeners
	Clock::addEventListener(VUEngine::getClock(VUEngine::getInstance()), ListenerObject::safeCast(this), (EventListener)LowPowerEntity::onSecondChange, kEventSecondChanged);
}

// class's destructor
void LowPowerEntity::destructor()
{
	// remove event listeners
	Clock::removeEventListener(VUEngine::getClock(VUEngine::getInstance()), ListenerObject::safeCast(this), (EventListener)LowPowerEntity::onSecondChange, kEventSecondChanged);

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
		AnimatedEntity::playAnimation(this, "Flash");

		// There is no real need to do anything else once the power flag has been raise since
		// the batteries can not be recharged during usage
		Clock::removeEventListener(VUEngine::getClock(VUEngine::getInstance()), ListenerObject::safeCast(this), (EventListener)LowPowerEntity::onSecondChange, kEventSecondChanged);
	}
}
