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
#include <LowPowerManager.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void LowPowerManager::constructor()
{
	// construct base object
	Base::constructor();

	// init class variables
	this->isShowingIndicator = false;
	this->isActive = false;
	this->lowPowerDuration = 0;
	this->indicatorXPos = __LOW_POWER_INDICATOR_X_POSITION;
	this->indicatorYPos = __LOW_POWER_INDICATOR_Y_POSITION;

	// add event listeners
	Clock::addEventListener(Game::getClock(Game::getInstance()), Object::safeCast(this), (EventListener)LowPowerManager::onSecondChange, kEventSecondChanged);
}

void LowPowerManager::destructor()
{
	// remove event listeners
	Clock::removeEventListener(Game::getClock(Game::getInstance()), Object::safeCast(this), (EventListener)LowPowerManager::onSecondChange, kEventSecondChanged);

	// destroy base
	Base::destructor();
}

void LowPowerManager::setActive(bool active)
{
	this->isActive = active;
}

void LowPowerManager::setPosition(u8 x, u8 y)
{
	this->indicatorXPos = x;
	this->indicatorYPos = y;
}

void LowPowerManager::onSecondChange(Object eventFirer __attribute__ ((unused)))
{
	// poll the user's input
	UserInput userInput = KeypadManager::getUserInput(KeypadManager::getInstance());

	// check low power flag
	if(userInput.powerFlag & this->isActive)
	{
		if(this->lowPowerDuration >= __LOW_POWER_INDICATOR_FLASH_DELAY - 1)
		{
			LowPowerManager::printLowPowerIndicator(this, !this->isShowingIndicator);
		}
		else
		{
			this->lowPowerDuration++;
			LowPowerManager::printLowPowerIndicator(this, false);
		}
	}
	else if(this->isShowingIndicator)
	{
		this->lowPowerDuration = 0;
		LowPowerManager::printLowPowerIndicator(this, false);
	}
}

void LowPowerManager::printLowPowerIndicator(bool showIndicator)
{
	Printing::text(
		Printing::getInstance(),
		(showIndicator) ? __LOW_POWER_INDICATOR_ON_TEXT : __LOW_POWER_INDICATOR_OFF_TEXT,
		this->indicatorXPos,
		this->indicatorYPos,
		__LOW_POWER_INDICATOR_FONT
	);

	this->isShowingIndicator = showIndicator;
}
