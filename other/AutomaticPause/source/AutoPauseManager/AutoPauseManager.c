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
