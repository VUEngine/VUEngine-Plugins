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

	// add event listeners
	GameState::addEventListener
	(
		VUEngine::getCurrentState(VUEngine::getInstance()), ListenerObject::safeCast(this), 
		(EventListener)LocalizedActor::onLanguageChanged, kEventLanguageChanged
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LocalizedActor::destructor()
{
	// remove event listeners
	GameState::removeEventListener
	(
		VUEngine::getCurrentState(VUEngine::getInstance()), ListenerObject::safeCast(this), 
		(EventListener)LocalizedActor::onLanguageChanged, kEventLanguageChanged
	);

	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LocalizedActor::ready(bool recursive)
{
	Base::ready(this, recursive);

	// translate actor
	LocalizedActor::localize(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LocalizedActor::localize()
{
	char* language = Utilities::itoa(I18n::getActiveLanguage(I18n::getInstance()), 10, 1);
	LocalizedActor::playAnimation(Actor::safeCast(this), language);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool LocalizedActor::onLanguageChanged(ListenerObject eventFirer __attribute__ ((unused)))
{
	// translate actor
	LocalizedActor::localize(this);

	return true;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
