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
#include <LowPowerManager.h>
#include <VUEngine.h>

#include "AdjustmentScreenState.h"


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	this->stream = false;
	this->transform = false;
	this->updatePhysics = false;
	this->processCollisions = false;

	AdjustmentScreenState::init(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::exit(void* owner)
{
	// reset low power indicator position
	AdjustmentScreenState::resetLowPowerIndicatorPosition(this);

	// call base
	Base::exit(this, owner);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::suspend(void* owner)
{
	// call base
	Base::suspend(this, owner);

	// set low power indicator position
	AdjustmentScreenState::resetLowPowerIndicatorPosition(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::resume(void* owner)
{
	// call base
	Base::resume(this, owner);

	AdjustmentScreenState::init(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::processUserInput(const UserInput*  userInput)
{
	if(userInput->pressedKey & (K_STA | K_SEL | K_A | K_B))
	{
		if(VUEngine::isPaused(VUEngine::getInstance()))
		{
			Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);
			VUEngine::unpause(VUEngine::getInstance(), GameState::safeCast(this));
		}
		else
		{
			SplashScreenState::loadNextState(this);
		}
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	extern StageROMSpec AdjustmentScreenStage;

	this->stageSpec = (StageSpec*)&AdjustmentScreenStage;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::destructor()
{
	// destroy base
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::init()
{
	// set low power indicator position
	AdjustmentScreenState::setLowPowerIndicatorPosition(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::setLowPowerIndicatorPosition()
{
	LowPowerManager::setPosition
	(
		LowPowerManager::getInstance(), __PLUGIN_ADJUSTMENT_SCREEN_NINTENDO_LOW_POWER_INDICATOR_X_POSITION, 
		__PLUGIN_ADJUSTMENT_SCREEN_NINTENDO_LOW_POWER_INDICATOR_Y_POSITION
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::resetLowPowerIndicatorPosition()
{
	LowPowerManager::setPosition
	(
		LowPowerManager::getInstance(), __PLUGIN_LOW_POWER_INDICATOR_X_POSITION, __PLUGIN_LOW_POWER_INDICATOR_Y_POSITION
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

