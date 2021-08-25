/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
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
