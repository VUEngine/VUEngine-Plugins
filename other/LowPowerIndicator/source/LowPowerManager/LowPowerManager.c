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

#include <KeypadManager.h>
#include <Printer.h>
#include <Singleton.h>
#include <VirtualList.h>
#include <VirtualNode.h>
#include <VUEngine.h>

#include "LowPowerManager.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS'S METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LowPowerManager::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	// Init class variables
	this->clock = NULL;
	this->isShowingIndicator = false;
	this->isActive = false;
	this->lowPowerDuration = 0;
	this->indicatorXPos = __PLUGIN_LOW_POWER_INDICATOR_X_POSITION;
	this->indicatorYPos = __PLUGIN_LOW_POWER_INDICATOR_Y_POSITION;

	// Add event listeners
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LowPowerManager::destructor()
{
	if(!isDeleted(this->clock))
	{
		delete this->clock;
		this->clock = NULL;
	}

	// Remove event listeners
	KeypadManager::removeEventListener(KeypadManager::getInstance(), ListenerObject::safeCast(this), kEventKeypadManagerRaisedPowerFlag);

	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool LowPowerManager::onEvent(ListenerObject eventFirer, uint16 eventCode)
{
	switch(eventCode)
	{
		case kEventKeypadManagerRaisedPowerFlag:
		{
			if(isDeleted(this->clock))
			{
				this->clock = new Clock();
				Clock::start(this->clock);
			}

			Clock::addEventListener(this->clock, ListenerObject::safeCast(this), kEventSecondChanged);
			return false;
		}

		case kEventSecondChanged:
		{
			// Check low power flag
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
	}

	return Base::onEvent(this, eventFirer, eventCode);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LowPowerManager::setActive(bool active)
{
	this->isActive = active;

	if(this->isActive)
	{
		KeypadManager::addEventListener(KeypadManager::getInstance(), ListenerObject::safeCast(this), kEventKeypadManagerRaisedPowerFlag);
	}
	else
	{
		KeypadManager::removeEventListener
		(
			KeypadManager::getInstance(), ListenerObject::safeCast(this), kEventKeypadManagerRaisedPowerFlag
		);
		
		if(!isDeleted(this->clock))
		{
			delete this->clock;
			this->clock = NULL;
		}
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LowPowerManager::setPosition(uint8 x, uint8 y)
{
	this->indicatorXPos = x;
	this->indicatorYPos = y;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void LowPowerManager::printLowPowerIndicator(bool showIndicator)
{
	Printer::text
	(
		
		(showIndicator) ? __PLUGIN_LOW_POWER_INDICATOR_ON_TEXT : __PLUGIN_LOW_POWER_INDICATOR_OFF_TEXT,
		this->indicatorXPos,
		this->indicatorYPos,
		__PLUGIN_LOW_POWER_INDICATOR_FONT
	);

	this->isShowingIndicator = showIndicator;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
