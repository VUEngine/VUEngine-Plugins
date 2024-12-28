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

#include <I18n.h>
#include <Utilities.h>
#include <VUEngine.h>

#include "LocalizedEntity.h"


//=========================================================================================================
// CLASS' PUBLIC METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
void LocalizedEntity::constructor(const LocalizedEntitySpec* localizedEntitySpec, int16 internalId, const char* const name)
{
	// Always explicitly call the base's constructor 
	Base::constructor((AnimatedEntitySpec*)&localizedEntitySpec->animatedEntitySpec, internalId, name);

	// add event listeners
	GameState::addEventListener(VUEngine::getCurrentState(VUEngine::getInstance()), ListenerObject::safeCast(this), (EventListener)LocalizedEntity::onLanguageChanged, kEventLanguageChanged);
}
//---------------------------------------------------------------------------------------------------------
void LocalizedEntity::destructor()
{
	// remove event listeners
	GameState::removeEventListener(VUEngine::getCurrentState(VUEngine::getInstance()), ListenerObject::safeCast(this), (EventListener)LocalizedEntity::onLanguageChanged, kEventLanguageChanged);

	// Always explicitly call the base's destructor 
	Base::destructor();
}
//---------------------------------------------------------------------------------------------------------
void LocalizedEntity::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// translate entity
	LocalizedEntity::localize(this);
}
//---------------------------------------------------------------------------------------------------------

//=========================================================================================================
// CLASS' PRIVATE METHODS
//=========================================================================================================

//---------------------------------------------------------------------------------------------------------
void LocalizedEntity::localize()
{
	char* language = Utilities::itoa(I18n::getActiveLanguage(I18n::getInstance()), 10, 1);
	LocalizedEntity::playAnimation(AnimatedEntity::safeCast(this), language);
}
//---------------------------------------------------------------------------------------------------------
bool LocalizedEntity::onLanguageChanged(ListenerObject eventFirer __attribute__ ((unused)))
{
	// translate entity
	LocalizedEntity::localize(this);

	return true;
}
//---------------------------------------------------------------------------------------------------------
