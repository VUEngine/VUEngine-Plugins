/*
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
#include <AutoPauseScreenState.h>
#include <AutoPauseManager.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void AutoPauseManager::constructor()
{
	// construct base object
	Base::constructor();

	// init members
	this->automaticPauseState = NULL;
	this->isActive = false;
	this->elapsedTime = 0;
	this->autoPauseDelay = 30;
}

void AutoPauseManager::destructor()
{
	// remove event listeners
	Clock::removeEventListener(Game::getClock(Game::getInstance()), Object::safeCast(this), (EventListener)AutoPauseManager::onMinuteChange, kEventMinuteChanged);

	// destroy base
	Base::destructor();
}

// set auto pause state
void AutoPauseManager::setAutomaticPauseState(GameState automaticPauseState)
{
	this->automaticPauseState = automaticPauseState;
}

// get auto pause state
GameState AutoPauseManager::getAutomaticPauseState()
{
	return this->automaticPauseState;
}

// set auto pause delay
void AutoPauseManager::setAutomaticPauseDelay(u8 automaticPauseDelay)
{
	this->autoPauseDelay = automaticPauseDelay;
}

bool AutoPauseManager::isActive()
{
	return this->isActive;
}

void AutoPauseManager::setActive(bool active)
{
	this->isActive = active;
	this->elapsedTime = 0;

	// set automatic pause state to default if it is not set yet
	if(this->automaticPauseState == NULL)
	{
		AutoPauseManager::setAutomaticPauseState(this, GameState::safeCast(AutoPauseScreenState::getInstance()));
	}

	if(this->isActive)
	{
		// add event listeners
		Clock::addEventListener(Game::getClock(Game::getInstance()), Object::safeCast(this), (EventListener)AutoPauseManager::onMinuteChange, kEventMinuteChanged);
	}
	else
	{
		// remove event listeners
		Clock::removeEventListener(Game::getClock(Game::getInstance()), Object::safeCast(this), (EventListener)AutoPauseManager::onMinuteChange, kEventMinuteChanged);
	}
}

void AutoPauseManager::onMinuteChange(Object eventFirer __attribute__ ((unused)))
{
	if(this->automaticPauseState && this->isActive && !Game::isPaused(Game::getInstance()))
	{
		this->elapsedTime++;

		// only pause if no more than one state is active
		if((this->elapsedTime >= this->autoPauseDelay) &&
			(1 == StateMachine::getStackSize(Game::getStateMachine(Game::getInstance()))))
		{
			Game::pause(Game::getInstance(), this->automaticPauseState);
			this->elapsedTime = 0;
		}
	}
}
