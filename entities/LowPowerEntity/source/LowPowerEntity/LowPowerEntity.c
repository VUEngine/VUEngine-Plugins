/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <Events.h>
#include <KeypadManager.h>

#include "LowPowerEntity.h"


//=========================================================================================================
// CLASS' PUBLIC METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
void LowPowerEntity::constructor(const LowPowerEntitySpec* lowPowerEntitySpec, int16 internalId, const char* const name)
{
	Base::constructor((AnimatedEntitySpec*)&lowPowerEntitySpec->animatedEntitySpec, internalId, name);

	// Add event listeners
	KeypadManager::addEventListener(KeypadManager::getInstance(), ListenerObject::safeCast(this), (EventListener)LowPowerEntity::onKeypadManagerRaisedPowerFlag, kEventKeypadManagerRaisedPowerFlag);
}
//---------------------------------------------------------------------------------------------------------
void LowPowerEntity::destructor()
{
	// remove event listeners
	KeypadManager::removeEventListener(KeypadManager::getInstance(), ListenerObject::safeCast(this), (EventListener)LowPowerEntity::onKeypadManagerRaisedPowerFlag, kEventKeypadManagerRaisedPowerFlag);

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}
//---------------------------------------------------------------------------------------------------------

//=========================================================================================================
// CLASS' PRIVATE METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
bool LowPowerEntity::onKeypadManagerRaisedPowerFlag(ListenerObject eventFirer __attribute__ ((unused)))
{
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), "Flash");

	return false;
}
//---------------------------------------------------------------------------------------------------------
