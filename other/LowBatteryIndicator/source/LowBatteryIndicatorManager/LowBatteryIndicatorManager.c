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

#include <KeypadManager.h>
#include <MessageDispatcher.h>
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

	// start in active state
	LowBatteryIndicatorManager::setActive(this, true);
}

void LowBatteryIndicatorManager::destructor()
{
	// discard possibly still pending delayed messages
	MessageDispatcher::discardAllDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this));

	// destroy base
	Base::destructor();
}

bool LowBatteryIndicatorManager::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kLowBatteryIndicatorCheck:

			LowBatteryIndicatorManager::checkLowBattery(this);
			break;

		case kLowBatteryIndicatorBlink:

			LowBatteryIndicatorManager::printLowBatteryIndicator(this, Telegram::getExtraInfo(telegram) ? true : false);
			LowBatteryIndicatorManager::queueNextBlink(this, Telegram::getExtraInfo(telegram) ? true : false);
			break;
	}

	return true;
}

void LowBatteryIndicatorManager::setActive(bool active)
{
	// discard possibly still pending delayed messages
	MessageDispatcher::discardAllDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this));

	if(active)
	{
		// initiate regular checks for low battery
		LowBatteryIndicatorManager::queueNextCheck(this);
	}
	else
	{
		// stop showing indicator in case it's being shown
		LowBatteryIndicatorManager::stopShowingIndicator(this);
	}
}

void LowBatteryIndicatorManager::checkLowBattery()
{
	// poll the user's input
	UserInput userInput = KeypadManager::read(KeypadManager::getInstance());

	// check low battery flag
	if(userInput.powerFlag)
	{
		LowBatteryIndicatorManager::startShowingIndicator(this);
	}
	else
	{
		LowBatteryIndicatorManager::stopShowingIndicator(this);
	}

	// check again in a moment
	LowBatteryIndicatorManager::queueNextCheck(this);
}

void LowBatteryIndicatorManager::startShowingIndicator()
{
	if(!this->isShowingIndicator)
	{
		LowBatteryIndicatorManager::queueNextBlink(this, true);
		this->isShowingIndicator = true;
	}
}

void LowBatteryIndicatorManager::stopShowingIndicator()
{
	if(this->isShowingIndicator)
	{
		MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kLowBatteryIndicatorBlink);
		LowBatteryIndicatorManager::printLowBatteryIndicator(this, false);
		this->isShowingIndicator = false;
	}
}

void LowBatteryIndicatorManager::printLowBatteryIndicator(bool showIndicator)
{
	Printing::text(
		Printing::getInstance(),
		(showIndicator) ? __CHAR_BATTERY : "  ",
		__LOW_BATTERY_INDICATOR_POS_X,
		__LOW_BATTERY_INDICATOR_POS_Y,
		NULL
	);
}

void LowBatteryIndicatorManager::queueNextCheck()
{
	MessageDispatcher::dispatchMessage(
		__LOW_BATTERY_CHECK_INTERVAL,
		Object::safeCast(this),
		Object::safeCast(this),
		kLowBatteryIndicatorCheck,
		NULL
	);
}

void LowBatteryIndicatorManager::queueNextBlink(bool showIndicator)
{
	MessageDispatcher::dispatchMessage(
		__LOW_BATTERY_INDICATOR_BLINK_INTERVAL,
		Object::safeCast(this),
		Object::safeCast(this),
		kLowBatteryIndicatorBlink,
		(bool*)(!showIndicator)
	);
}
