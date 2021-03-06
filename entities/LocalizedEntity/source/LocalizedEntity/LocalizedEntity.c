/* VUEngine - Virtual Utopia Engine <https://www.vuengine.dev>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>, 2007-2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Game.h>
#include <I18n.h>
#include <Utilities.h>
#include <GameEvents.h>
#include "LocalizedEntity.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void LocalizedEntity::constructor(const LocalizedEntitySpec* localizedEntitySpec, s16 internalId, const char* const name)
{
	// construct base object
	Base::constructor((AnimatedEntitySpec*)localizedEntitySpec, internalId, name);

	// add event listeners
	GameState::addEventListener(Game::getCurrentState(Game::getInstance()), Object::safeCast(this), (EventListener)LocalizedEntity::onLanguageChanged, kEventLanguageChanged);
}

void LocalizedEntity::destructor()
{
	// remove event listeners
	GameState::removeEventListener(Game::getCurrentState(Game::getInstance()), Object::safeCast(this), (EventListener)LocalizedEntity::onLanguageChanged, kEventLanguageChanged);

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void LocalizedEntity::ready(bool recursive)
{
	// call base
	Base::ready(this, recursive);

	// translate entity
	LocalizedEntity::localize(this);
}

void LocalizedEntity::localize()
{
	char* language = Utilities::itoa(I18n::getActiveLanguage(I18n::getInstance()), 10, 1);
	AnimatedEntity::playAnimation(AnimatedEntity::safeCast(this), language);
}

// handle event
void LocalizedEntity::onLanguageChanged(Object eventFirer __attribute__ ((unused)))
{
	// translate entity
	LocalizedEntity::localize(this);
}
