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

#include <Camera.h>
#include <CameraEffectManager.h>
#include <VUEngine.h>

#include "SplashScreenState.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void SplashScreenState::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	// Init class members
	this->stageSpec = NULL;
	this->nextState = NULL;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void SplashScreenState::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void SplashScreenState::enter(void* owner)
{
	Base::enter(this, owner);

	if(NULL != this->stageSpec)
	{
		SplashScreenState::configureStage(this, this->stageSpec, NULL);
	}

	SplashScreenState::print(this);

	// Start clocks to start animations
	SplashScreenState::startClocks(this);

	KeypadManager::disable();

	// Start fade in effect
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect
	(
		Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(ListenerObject, ListenerObject))SplashScreenState::onFadeInComplete, // callback function
		ListenerObject::safeCast(this) // callback scope
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void SplashScreenState::exit(void* owner)
{
	Base::exit(this, owner);

	// Destroy the state
	delete this;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void SplashScreenState::suspend(void* owner)
{
	// Do a fade out effect
	Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);

	Base::suspend(this, owner);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void SplashScreenState::resume(void* owner)
{
	Base::resume(this, owner);

	SplashScreenState::print(this);

	KeypadManager::disable();

	// Start fade in effect
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect
	(
		Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(ListenerObject, ListenerObject))SplashScreenState::onFadeInComplete, // callback function
		ListenerObject::safeCast(this) // callback scope
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void SplashScreenState::processUserInput(const UserInput* userInput)
{
	if(userInput->pressedKey & (K_STA | K_SEL | K_A | K_B))
	{
		SplashScreenState::loadNextState(this);
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool SplashScreenState::processMessage(void* owner __attribute__ ((unused)), Telegram telegram __attribute__ ((unused)))
{
	return false;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void SplashScreenState::setNextState(GameState nextState)
{
	this->nextState = nextState;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void SplashScreenState::loadNextState()
{
	// Disable user input
	KeypadManager::disable();

	// Start fade out effect
	Brightness brightness = (Brightness){0, 0, 0};
	Camera::startEffect
	(
		Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		&brightness, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(ListenerObject, ListenerObject))SplashScreenState::onFadeOutComplete, // callback function
		ListenerObject::safeCast(this) // callback scope
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void SplashScreenState::print()
{}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool SplashScreenState::onFadeInComplete(ListenerObject eventFirer __attribute__ ((unused)))
{
	// Enable user input
	KeypadManager::enable();

	return false;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool SplashScreenState::onFadeOutComplete(ListenerObject eventFirer __attribute__ ((unused)))
{
	// Switch to next stage
	VUEngine::changeState(this->nextState);

	return false;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
