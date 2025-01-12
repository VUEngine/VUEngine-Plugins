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
#include <DirectDraw.h>
#include <LowPowerManager.h>
#include <SoundManager.h>
#include <VUEngine.h>

#include "AdjustmentScreenState.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

extern StageROMSpec AdjustmentScreenStage;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' MACROS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#define __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE		-64

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE STATIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

static void AdjustmentScreenState::rhombusEmitterPostProcessingEffect
(
	uint32 currentDrawingFrameBufferSet __attribute__ ((unused)), Entity entity __attribute__ ((unused))
)
{
	// Runtime working variables
	// Negative value to achieve an initial delay
	static int32 radius = __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE;

	// Increase radius in each cycle
	radius += 2;

	if(radius < 68)
	{
		return;
	}
	else if(radius > 300)
	{
		// Reset radius when reaching a certain length
		radius = __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE;
		return;
	}

	// Draw rhombus around object with given radius

	// Top left line
	DirectDraw::drawLine
	(
		(PixelVector) {(192 - radius),	(112),			0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 - radius),	0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED,
		0,
		false
	);

	// Top right line
	DirectDraw::drawLine
	(
		(PixelVector) {(192 + radius),	(112),			0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 - radius),	0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED,
		0,
		false
	);

	// Bottom right line
	DirectDraw::drawLine
	(
		(PixelVector) {(192 + radius),	(112),			0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 + radius),	0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED,
		0,
		false
	);

	// Bottom left line
	DirectDraw::drawLine
	(
		(PixelVector) {(192 - radius),	(112),			0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 + radius),	0, -((radius + __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED,
		0,
		false
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::enter(void* owner)
{
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
	// Reset low power indicator position
	AdjustmentScreenState::resetLowPowerIndicatorPosition(this);

	Base::exit(this, owner);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::suspend(void* owner)
{
	Base::suspend(this, owner);

	// Set low power indicator position
	AdjustmentScreenState::resetLowPowerIndicatorPosition(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::resume(void* owner)
{
	Base::resume(this, owner);

	AdjustmentScreenState::init(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::processUserInput(const UserInput* userInput)
{
	if(userInput->pressedKey & (K_STA | K_SEL | K_A | K_B))
	{
		if(VUEngine::isPaused())
		{
			Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);
			VUEngine::unpause(GameState::safeCast(this));
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

	this->stageSpec = (StageSpec*)&AdjustmentScreenStage;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::init()
{
	// Add rhombus effect
	VUEngine::pushBackPostProcessingEffect(AdjustmentScreenState::rhombusEmitterPostProcessingEffect, NULL);

	// Set low power indicator position
	AdjustmentScreenState::setLowPowerIndicatorPosition(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AdjustmentScreenState::setLowPowerIndicatorPosition()
{
	LowPowerManager::setPosition
	(
		LowPowerManager::getInstance(), __PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_LOW_POWER_INDICATOR_X_POSITION, 
		__PLUGIN_ADJUSTMENT_SCREEN_VUENGINE_LOW_POWER_INDICATOR_Y_POSITION
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
