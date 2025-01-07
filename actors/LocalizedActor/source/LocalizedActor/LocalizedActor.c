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

#include <I18n.h>
#include <Utilities.h>
#include <VUEngine.h>

#include "LocalizedActor.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LocalizedActor::constructor(const LocalizedActorSpec* localizedActorSpec, int16 internalId, const char* const name)
{
	// Always explicitly call the base's constructor 
	Base::constructor((ActorSpec*)&localizedActorSpec->actorSpec, internalId, name);

	// Add event listeners
	GameState::addEventListener
	(
		VUEngine::getCurrentState(), ListenerObject::safeCast(this), 
		(EventListener)LocalizedActor::onLanguageChanged, kEventLanguageChanged
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LocalizedActor::destructor()
{
	// Remove event listeners
	GameState::removeEventListener
	(
		VUEngine::getCurrentState(), ListenerObject::safeCast(this), 
		(EventListener)LocalizedActor::onLanguageChanged, kEventLanguageChanged
	);

	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LocalizedActor::ready(bool recursive)
{
	Base::ready(this, recursive);

	LocalizedActor::localize(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LocalizedActor::localize()
{
	LocalizedActor::playAnimation(this, Utilities::itoa(I18n::getActiveLanguage(I18n::getInstance()), 10, 1));
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool LocalizedActor::onLanguageChanged(ListenerObject eventFirer __attribute__ ((unused)))
{
	LocalizedActor::localize(this);

	return true;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
