/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Camera.h>
#include <CameraEffectManager.h>
#include <DirectDraw.h>
#include <LowPowerManager.h>
#include <SoundManager.h>
#include <VUEngine.h>

#include "AdjustmentScreenState.h"


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

extern StageROMSpec AdjustmentScreenStage;


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' MACROS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

#define __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE		-64


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————

static void AdjustmentScreenState::rhombusEmitterPostProcessingEffect(uint32 currentDrawingFrameBufferSet __attribute__ ((unused)), GameObject gameObject __attribute__ ((unused)))
{
	// runtime working variables
	// negative value to achieve an initial delay
	static int32 radius = __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE;

	// increase radius in each cycle
	radius += 2;

	if(radius < 68)
	{
		return;
	}
	else if(radius > 300)
	{
		// reset radius when reaching a certain length
		radius = __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE;
		return;
	}

	// draw rhombus around object with given radius

	// top left line
	DirectDraw::drawLine(
		(PixelVector) {(192 - radius),	(112),			0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 - radius),	0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED,
		0,
		false
	);

	// top right line
	DirectDraw::drawLine(
		(PixelVector) {(192 + radius),	(112),			0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 - radius),	0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED,
		0,
		false
	);

	// bottom right line
	DirectDraw::drawLine(
		(PixelVector) {(192 + radius),	(112),			0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 + radius),	0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED,
		0,
		false
	);

	// bottom left line
	DirectDraw::drawLine(
		(PixelVector) {(192 - radius),	(112),			0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 + radius),	0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED,
		0,
		false
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————

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

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::exit(void* owner)
{
	// reset low power indicator position
	AdjustmentScreenState::resetLowPowerIndicatorPosition(this);

	// call base
	Base::exit(this, owner);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::suspend(void* owner)
{
	// call base
	Base::suspend(this, owner);

	// set low power indicator position
	AdjustmentScreenState::resetLowPowerIndicatorPosition(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::resume(void* owner)
{
	// call base
	Base::resume(this, owner);

	AdjustmentScreenState::init(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::processUserInput(const UserInput* userInput)
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

//——————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	this->stageSpec = (StageSpec*)&AdjustmentScreenStage;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::destructor()
{
	// destroy base
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::init()
{
	// add rhombus effect
	VIPManager::pushBackPostProcessingEffect(VIPManager::getInstance(), AdjustmentScreenState::rhombusEmitterPostProcessingEffect, NULL);

	// set low power indicator position
	AdjustmentScreenState::setLowPowerIndicatorPosition(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::setLowPowerIndicatorPosition()
{
	LowPowerManager::setPosition(LowPowerManager::getInstance(), __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_LOW_POWER_INDICATOR_X_POSITION, __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_LOW_POWER_INDICATOR_Y_POSITION);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::resetLowPowerIndicatorPosition()
{
	LowPowerManager::setPosition(LowPowerManager::getInstance(), __PLUGIN_LOW_POWER_INDICATOR_X_POSITION, __PLUGIN_LOW_POWER_INDICATOR_Y_POSITION);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

