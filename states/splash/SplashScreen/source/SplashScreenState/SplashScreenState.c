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

#include <Camera.h>
#include <CameraEffectManager.h>
#include <VUEngine.h>

#include "SplashScreenState.h"


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void SplashScreenState::constructor()
{
	Base::constructor();

	// init class members
	this->stageSpec = NULL;
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

	if(NULL != this->stageSpec)
	{
		SplashScreenState::configureStage(this, this->stageSpec, NULL);
	}

	SplashScreenState::print(this);

	// start clocks to start animations
	SplashScreenState::startClocks(this);

	VUEngine::disableKeypad(VUEngine::getInstance());

	// start fade in effect
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(ListenerObject, ListenerObject))SplashScreenState::onFadeInComplete, // callback function
		ListenerObject::safeCast(this) // callback scope
	);
}

void SplashScreenState::exit(void* owner)
{
	// call base
	Base::exit(this, owner);

	// destroy the state
	delete this;
}

// state's suspend
void SplashScreenState::suspend(void* owner)
{
	// do a fade out effect
	Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);

	// call base
	Base::suspend(this, owner);
}

// state's resume
void SplashScreenState::resume(void* owner)
{
	Base::resume(this, owner);

	SplashScreenState::print(this);

	VUEngine::disableKeypad(VUEngine::getInstance());

	// start fade in effect
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(ListenerObject, ListenerObject))SplashScreenState::onFadeInComplete, // callback function
		ListenerObject::safeCast(this) // callback scope
	);
}

bool SplashScreenState::processMessage(void* owner __attribute__ ((unused)), Telegram telegram __attribute__ ((unused)))
{
	return false;
}

void SplashScreenState::processUserInput(const UserInput* userInput)
{
	if(userInput->pressedKey & (K_STA | K_SEL | K_A | K_B))
	{
		SplashScreenState::loadNextState(this);
	}
}

void SplashScreenState::print()
{
}

void SplashScreenState::initNextState()
{
}

void SplashScreenState::setNextState(GameState nextState)
{
	this->nextState = nextState;
}

void SplashScreenState::loadNextState()
{
	// disable user input
	VUEngine::disableKeypad(VUEngine::getInstance());

	// start fade out effect
	Brightness brightness = (Brightness){0, 0, 0};
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		&brightness, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(ListenerObject, ListenerObject))SplashScreenState::onFadeOutComplete, // callback function
		ListenerObject::safeCast(this) // callback scope
	);
}

// handle event
bool SplashScreenState::onFadeInComplete(ListenerObject eventFirer __attribute__ ((unused)))
{
	// enable user input
	VUEngine::enableKeypad(VUEngine::getInstance());

	return false;
}

// handle event
bool SplashScreenState::onFadeOutComplete(ListenerObject eventFirer __attribute__ ((unused)))
{
	if(this->nextState == NULL)
	{
		SplashScreenState::initNextState(this);
	}

	// switch to next stage
	VUEngine::changeState(VUEngine::getInstance(), this->nextState);

	return false;
}
