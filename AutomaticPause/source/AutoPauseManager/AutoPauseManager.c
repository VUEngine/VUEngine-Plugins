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
#include <MessageDispatcher.h>
#include <AutoPauseScreenState.h>
#include <AutoPauseManager.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void AutoPauseManager::constructor()
{
	// construct base object
	Base::constructor();

	// register start time for auto pause check
	this->lastAutoPauseCheckTime = Clock::getTime(Game::getClock(Game::getInstance()));

	// set default automatic pause state
	AutoPauseManager::setAutomaticPauseState(AutoPauseManager::getInstance(), GameState::safeCast(AutoPauseScreenState::getInstance()));

	// add event listeners
	Object::addEventListener(this, Object::safeCast(Game::getInstance()), (EventListener)AutoPauseManager::onGamePaused, kEventGamePaused);
	Object::addEventListener(this, Object::safeCast(Game::getInstance()), (EventListener)AutoPauseManager::onGameUnpaused, kEventGameUnpaused);

	// start
	AutoPauseManager::startCheckDelay(this, __AUTO_PAUSE_DELAY);
}

void AutoPauseManager::destructor()
{
	// remove event listeners
	Object::removeEventListener(this, Object::safeCast(Game::getInstance()), (EventListener)AutoPauseManager::onGamePaused, kEventGamePaused);
	Object::removeEventListener(this, Object::safeCast(Game::getInstance()), (EventListener)AutoPauseManager::onGameUnpaused, kEventGameUnpaused);

	// destroy base
	Base::destructor();
}

// process a telegram
bool AutoPauseManager::handleMessage(Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kAutoPause:

			AutoPauseManager::autoPause(this);
			break;
	}

	return true;
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

// show auto pause screen
void AutoPauseManager::autoPause()
{
	if(this->automaticPauseState)
	{
		// only pause if no more than one state is active, otherwise wait a moment to check again
		if(1 == StateMachine::getStackSize(Game::getStateMachine(Game::getInstance())))
		{
			Game::pause(Game::getInstance(), this->automaticPauseState);
		}
		else
		{
			MessageDispatcher::dispatchMessage(__AUTO_PAUSE_RECHECK_DELAY, Object::safeCast(this), Object::safeCast(this), kAutoPause, NULL);
		}
	}
}

void AutoPauseManager::startCheckDelay(u32 checkDelay)
{
	MessageDispatcher::discardDelayedMessagesFromSender(MessageDispatcher::getInstance(), Object::safeCast(this), kAutoPause);
	MessageDispatcher::dispatchMessage(checkDelay, Object::safeCast(this), Object::safeCast(this), kAutoPause, NULL);
	this->lastAutoPauseCheckTime = Clock::getTime(Game::getClock(Game::getInstance()));
}

void AutoPauseManager::onGamePaused(Object eventFirer __attribute__ ((unused)))
{
}

void AutoPauseManager::onGameUnpaused(Object eventFirer __attribute__ ((unused)))
{
	// restart auto pause check after auto pause screen has been exited
	if(Game::getCurrentState(Game::getInstance()) == this->automaticPauseState)
	{
		AutoPauseManager::startCheckDelay(this, __AUTO_PAUSE_DELAY);
	}
}

/*
void AutoPauseManager::onNextGameStateSet(Object eventFirer __attribute__ ((unused)))
{
	// on next state set
	if(this->automaticPauseState)
	{
		int automaticPauseCheckDelay = __AUTO_PAUSE_DELAY - (Clock::getTime(Game::getClock(Game::getInstance())) - this->lastAutoPauseCheckTime);
		if(automaticPauseCheckDelay < 0)
		{
			automaticPauseCheckDelay = 0;
		}

		AutoPauseManager::startCheckDelay(this, (u32)automaticPauseCheckDelay);
	}
}
*/