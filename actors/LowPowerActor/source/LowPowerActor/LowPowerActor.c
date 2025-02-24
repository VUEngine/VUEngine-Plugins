/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Events.h>
#include <KeypadManager.h>

#include "LowPowerActor.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LowPowerActor::constructor(const LowPowerActorSpec* lowPowerActorSpec, int16 internalId, const char* const name)
{
	// Always explicitly call the base's constructor 
	Base::constructor((ActorSpec*)&lowPowerActorSpec->actorSpec, internalId, name);

	// Add event listeners
	KeypadManager::addEventListener(KeypadManager::getInstance(), ListenerObject::safeCast(this), kEventKeypadManagerRaisedPowerFlag);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LowPowerActor::destructor()
{
	// Remove event listeners
	KeypadManager::removeEventListener(KeypadManager::getInstance(), ListenerObject::safeCast(this), kEventKeypadManagerRaisedPowerFlag);

	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool LowPowerActor::onEvent(ListenerObject eventFirer, uint16 eventCode)
{
	switch(eventCode)
	{
		case kEventKeypadManagerRaisedPowerFlag:
		{
			LowPowerActor::playAnimation(this, "Flash");

			return false;
		}
	}

	return Base::onEvent(this, eventFirer, eventCode);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
