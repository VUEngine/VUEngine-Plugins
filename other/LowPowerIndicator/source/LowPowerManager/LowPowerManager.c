/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <KeypadManager.h>
#include <Printing.h>
#include <VirtualList.h>
#include <VirtualNode.h>
#include <VUEngine.h>

#include "LowPowerManager.h"


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
	this->indicatorXPos = __PLUGIN_LOW_POWER_INDICATOR_X_POSITION;
	this->indicatorYPos = __PLUGIN_LOW_POWER_INDICATOR_Y_POSITION;

	// add event listeners
}

void LowPowerManager::destructor()
{
	// remove event listeners
	KeypadManager::removeEventListener(KeypadManager::getInstance(), ListenerObject::safeCast(this), (EventListener)LowPowerManager::onKeypadManagerRaisedPowerFlag, kEventKeypadManagerRaisedPowerFlag);
	Clock::removeEventListener(VUEngine::getClock(VUEngine::getInstance()), ListenerObject::safeCast(this), (EventListener)LowPowerManager::onSecondChange, kEventSecondChanged);

	// destroy base
	Base::destructor();
}

void LowPowerManager::setActive(bool active)
{
	this->isActive = active;

	if(this->isActive)
	{
		KeypadManager::addEventListener(KeypadManager::getInstance(), ListenerObject::safeCast(this), (EventListener)LowPowerManager::onKeypadManagerRaisedPowerFlag, kEventKeypadManagerRaisedPowerFlag);
	}
	else
	{
		KeypadManager::removeEventListener(KeypadManager::getInstance(), ListenerObject::safeCast(this), (EventListener)LowPowerManager::onKeypadManagerRaisedPowerFlag, kEventKeypadManagerRaisedPowerFlag);
		Clock::removeEventListener(VUEngine::getClock(VUEngine::getInstance()), ListenerObject::safeCast(this), (EventListener)LowPowerManager::onSecondChange, kEventSecondChanged);
	}
}

bool LowPowerManager::onKeypadManagerRaisedPowerFlag(ListenerObject eventFirer __attribute__ ((unused)))
{
	Clock::addEventListener(VUEngine::getClock(VUEngine::getInstance()), ListenerObject::safeCast(this), (EventListener)LowPowerManager::onSecondChange, kEventSecondChanged);

	return false;
}

void LowPowerManager::setPosition(uint8 x, uint8 y)
{
	this->indicatorXPos = x;
	this->indicatorYPos = y;
}

bool LowPowerManager::onSecondChange(ListenerObject eventFirer __attribute__ ((unused)))
{
	// check low power flag
	if(this->isActive)
	{
		if(this->lowPowerDuration >= __PLUGIN_LOW_POWER_INDICATOR_FLASH_DELAY - 1)
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

	return true;
}

void LowPowerManager::printLowPowerIndicator(bool showIndicator)
{
	Printing::text(
		Printing::getInstance(),
		(showIndicator) ? __PLUGIN_LOW_POWER_INDICATOR_ON_TEXT : __PLUGIN_LOW_POWER_INDICATOR_OFF_TEXT,
		this->indicatorXPos,
		this->indicatorYPos,
		__PLUGIN_LOW_POWER_INDICATOR_FONT
	);

	this->isShowingIndicator = showIndicator;
}
