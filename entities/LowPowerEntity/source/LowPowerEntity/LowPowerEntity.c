/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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
#include <Events.h>
#include "LowPowerEntity.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void LowPowerEntity::constructor(const LowPowerEntityDefinition* LowPowerEntityDefinition, s16 id, s16 internalId, const char* const name)
{
	// construct base object
	Base::constructor((AnimatedEntityDefinition*)LowPowerEntityDefinition, id, internalId, name);

	// init class variables
	this->lowPowerDuration = 0;

	// add event listeners
	Object::addEventListener(Object::safeCast(Game::getClock(Game::getInstance())), Object::safeCast(this), (EventListener)LowPowerEntity::onSecondChange, kEventSecondChanged);
}

// class's destructor
void LowPowerEntity::destructor()
{
	// remove event listeners
	Object::removeEventListener(Object::safeCast(Game::getClock(Game::getInstance())), Object::safeCast(this), (EventListener)LowPowerEntity::onSecondChange, kEventSecondChanged);

	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void LowPowerEntity::onSecondChange(Object eventFirer __attribute__ ((unused)))
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
