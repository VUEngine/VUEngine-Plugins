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

#include <AutomaticPauseManager.h>
#include <Singleton.h>
#include <StateMachine.h>
#include <VUEngine.h>

#include "AutomaticPauseScreenState.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseManager::setAutomaticPauseState(GameState automaticPauseState)
{
	this->automaticPauseState = automaticPauseState;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

GameState AutomaticPauseManager::getAutomaticPauseState()
{
	return this->automaticPauseState;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseManager::setAutomaticPauseDelay(uint8 automaticPauseDelay)
{
	this->autoPauseDelay = automaticPauseDelay;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseManager::setActive(bool active)
{
	this->isActive = active;
	this->elapsedTime = 0;

	// Set automatic pause state to default if it is not set yet
	if(this->automaticPauseState == NULL)
	{
		AutomaticPauseManager::setAutomaticPauseState(this, GameState::safeCast(AutomaticPauseScreenState::getInstance()));
	}

	if(this->isActive)
	{
		// Add event listeners
		Clock::addEventListener(VUEngine::getClock(), ListenerObject::safeCast(this), kEventMinuteChanged);
	}
	else
	{
		// Remove event listeners
		Clock::removeEventListener(VUEngine::getClock(), ListenerObject::safeCast(this), kEventMinuteChanged);
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool AutomaticPauseManager::isActive()
{
	return this->isActive;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseManager::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	// Init members
	this->automaticPauseState = NULL;
	this->isActive = false;
	this->elapsedTime = 0;
	this->autoPauseDelay = 30;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseManager::destructor()
{
	// Remove event listeners
	Clock::removeEventListener(VUEngine::getClock(), ListenerObject::safeCast(this), kEventMinuteChanged);

	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool AutomaticPauseManager::onEvent(ListenerObject eventFirer __attribute__((unused)), uint16 eventCode)
{
	switch(eventCode)
	{
		case kEventMinuteChanged:
		{
			if(this->automaticPauseState && this->isActive && !VUEngine::isPaused())
			{
				this->elapsedTime++;

				// Only pause if no more than one state is active
				if((this->elapsedTime >= this->autoPauseDelay) && !VUEngine::isPaused())
				{
					VUEngine::pause(this->automaticPauseState);
					this->elapsedTime = 0;
				}
			}

			return true;
		}
	}

	return Base::onEvent(this, eventFirer, eventCode);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
