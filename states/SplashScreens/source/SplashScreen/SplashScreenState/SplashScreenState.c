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
#include <Camera.h>
#include <SplashScreenState.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void SplashScreenState::constructor()
{
	Base::constructor();

	// init class members
	this->stageDefinition = NULL;
	this->nextState = NULL;
}

void SplashScreenState::destructor()
{
	// destroy the super object
	// must always be called at the end of the destructor
	Base::destructor();
}

void SplashScreenState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	if(this->stageDefinition)
	{
		GameState::loadStage(this, this->stageDefinition, NULL, true);
	}

	SplashScreenState::print(this);

	Game::disableKeypad(Game::getInstance());

	// start fade in effect
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))SplashScreenState::onFadeInComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

void SplashScreenState::exit(void* owner)
{
	// call base
	Base::exit(this, owner);

	// destroy the state
	delete this;
}

// state's resume
void SplashScreenState::resume(void* owner)
{
	Base::resume(this, owner);

	SplashScreenState::print(this);

#ifdef __DEBUG_TOOLS
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif
#ifdef __STAGE_EDITOR
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif
#ifdef __ANIMATION_INSPECTOR
	if(!Game::isExitingSpecialMode(Game::getInstance()))
	{
#endif

	// start a fade in effect
	Camera::startEffect(Camera::getInstance(), kFadeIn, __FADE_DELAY);

#ifdef __DEBUG_TOOLS
	}
#endif
#ifdef __STAGE_EDITOR
	}
#endif
#ifdef __ANIMATION_INSPECTOR
	}
#endif
}

bool SplashScreenState::processMessage(void* owner __attribute__ ((unused)), Telegram telegram __attribute__ ((unused)))
{
	return false;
}

void SplashScreenState::processUserInput(UserInput userInput)
{
	if(userInput.pressedKey & (K_STA | K_SEL | K_A | K_B))
	{
		SplashScreenState::loadNextState(this);
	}
}

void SplashScreenState::print()
{
}

void SplashScreenState::setNextState(GameState nextState)
{
	this->nextState = nextState;
}

void SplashScreenState::loadNextState()
{
	// disable user input
	Game::disableKeypad(Game::getInstance());

	// start fade out effect
	Brightness brightness = (Brightness){0, 0, 0};
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		&brightness, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(Object, Object))SplashScreenState::onFadeOutComplete, // callback function
		Object::safeCast(this) // callback scope
	);
}

// handle event
void SplashScreenState::onFadeInComplete(Object eventFirer __attribute__ ((unused)))
{
	// enable user input
	Game::enableKeypad(Game::getInstance());
}

// handle event
void SplashScreenState::onFadeOutComplete(Object eventFirer __attribute__ ((unused)))
{
	// switch to next stage
	Game::changeState(Game::getInstance(), this->nextState);
}
