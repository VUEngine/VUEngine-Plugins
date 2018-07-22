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
#include <KeypadManager.h>
#include <LowBatteryIndicatorManager.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void LowBatteryIndicatorManager::constructor()
{
	// construct base object
	Base::constructor();

	// init class variables
	this->isShowingIndicator = false;
	this->isActive = false;
	this->lowBatteryDuration = 0;
	this->indicatorXPos = __LOW_BATTERY_INDICATOR_X_POSITION;
	this->indicatorYPos = __LOW_BATTERY_INDICATOR_Y_POSITION;

	// add event listeners
	Object::addEventListener(Object::safeCast(Game::getClock(Game::getInstance())), Object::safeCast(this), (EventListener)LowBatteryIndicatorManager::onSecondChange, kEventSecondChanged);
}

void LowBatteryIndicatorManager::destructor()
{
	// remove event listeners
	Object::removeEventListener(Object::safeCast(Game::getClock(Game::getInstance())), Object::safeCast(this), (EventListener)LowBatteryIndicatorManager::onSecondChange, kEventSecondChanged);

	// destroy base
	Base::destructor();
}

void LowBatteryIndicatorManager::setActive(bool active)
{
	this->isActive = active;
}

void LowBatteryIndicatorManager::setPosition(u8 x, u8 y)
{
	this->indicatorXPos = x;
	this->indicatorYPos = y;
}

void LowBatteryIndicatorManager::onSecondChange(Object eventFirer __attribute__ ((unused)))
{
	// poll the user's input
	UserInput userInput = KeypadManager::read(KeypadManager::getInstance());

	// check low battery flag
	if(userInput.powerFlag & this->isActive)
	{
		if(this->lowBatteryDuration >= __LOW_BATTERY_INDICATOR_BLINK_DELAY - 1)
		{
			LowBatteryIndicatorManager::printLowBatteryIndicator(this, !this->isShowingIndicator);
		}
		else
		{
			this->lowBatteryDuration++;
			LowBatteryIndicatorManager::printLowBatteryIndicator(this, false);
		}
	}
	else if(this->isShowingIndicator)
	{
		this->lowBatteryDuration = 0;
		LowBatteryIndicatorManager::printLowBatteryIndicator(this, false);
	}
}

void LowBatteryIndicatorManager::printLowBatteryIndicator(bool showIndicator)
{
	Printing::text(
		Printing::getInstance(),
		(showIndicator) ? __CHAR_BATTERY : "  ",
		this->indicatorXPos,
		this->indicatorYPos,
		NULL
	);

	this->isShowingIndicator = showIndicator;
}
