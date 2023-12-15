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

#include <LowPowerEntity.h>

#include <Events.h>
#include <KeypadManager.h>
#include <VUEngine.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void LowPowerEntity::constructor(const LowPowerEntitySpec* LowPowerEntitySpec, int16 internalId, const char* const name)
{
	// construct base object
	Base::constructor((AnimatedEntitySpec*)LowPowerEntitySpec, internalId, name);

	// add event listeners
	KeypadManager::addEventListener(KeypadManager::getInstance(), ListenerObject::safeCast(this), (EventListener)LowPowerEntity::onKeypadManagerRaisedPowerFlag, kEventKeypadManagerRaisedPowerFlag);
}

// class's destructor
void LowPowerEntity::destructor()
{
	// remove event listeners
	KeypadManager::removeEventListener(KeypadManager::getInstance(), ListenerObject::safeCast(this), (EventListener)LowPowerEntity::onKeypadManagerRaisedPowerFlag, kEventKeypadManagerRaisedPowerFlag);

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void LowPowerEntity::onKeypadManagerRaisedPowerFlag(ListenerObject eventFirer __attribute__ ((unused)))
{
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Flash");
	KeypadManager::removeEventListener(KeypadManager::getInstance(), ListenerObject::safeCast(this), (EventListener)LowPowerEntity::onKeypadManagerRaisedPowerFlag, kEventKeypadManagerRaisedPowerFlag);
}

