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

	// set automatic pause state to default if it is not set yet
	if(this->automaticPauseState == NULL)
	{
		AutomaticPauseManager::setAutomaticPauseState(this, GameState::safeCast(AutomaticPauseScreenState::getInstance()));
	}

	if(this->isActive)
	{
		// add event listeners
		Clock::addEventListener(VUEngine::getClock(VUEngine::getInstance()), ListenerObject::safeCast(this), (EventListener)AutomaticPauseManager::onMinuteChange, kEventMinuteChanged);
	}
	else
	{
		// remove event listeners
		Clock::removeEventListener(VUEngine::getClock(VUEngine::getInstance()), ListenerObject::safeCast(this), (EventListener)AutomaticPauseManager::onMinuteChange, kEventMinuteChanged);
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

	// init members
	this->automaticPauseState = NULL;
	this->isActive = false;
	this->elapsedTime = 0;
	this->autoPauseDelay = 30;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseManager::destructor()
{
	// remove event listeners
	Clock::removeEventListener(VUEngine::getClock(VUEngine::getInstance()), ListenerObject::safeCast(this), (EventListener)AutomaticPauseManager::onMinuteChange, kEventMinuteChanged);

	// destroy base
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool AutomaticPauseManager::onMinuteChange(ListenerObject eventFirer __attribute__ ((unused)))
{
	if(this->automaticPauseState && this->isActive && !VUEngine::isPaused(VUEngine::getInstance()))
	{
		this->elapsedTime++;

		// only pause if no more than one state is active
		if((this->elapsedTime >= this->autoPauseDelay) &&
			(1 == StateMachine::getStackSize(VUEngine::getStateMachine(VUEngine::getInstance()))))
		{
			VUEngine::pause(VUEngine::getInstance(), this->automaticPauseState);
			this->elapsedTime = 0;
		}
	}

	return true;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

