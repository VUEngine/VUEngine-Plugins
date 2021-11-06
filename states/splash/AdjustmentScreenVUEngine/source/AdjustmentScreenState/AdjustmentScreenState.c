/**
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
#include <Camera.h>
#include <MessageDispatcher.h>
#include <AdjustmentScreenState.h>
#include <DirectDraw.h>
#include <LowPowerManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec AdjustmentScreenStage;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void AdjustmentScreenState::constructor()
{
	Base::constructor();

	this->stageSpec = (StageSpec*)&AdjustmentScreenStage;
}

// class's destructor
void AdjustmentScreenState::destructor()
{
	// destroy base
	Base::destructor();
}

// state's enter
void AdjustmentScreenState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	this->stream = false;
	this->transform = false;
	this->synchronizeGraphics = false;
	this->updatePhysics = false;
	this->processCollisions = false;

	AdjustmentScreenState::init(this);
}

// state's exit
void AdjustmentScreenState::exit(void* owner)
{
	// reset low power indicator position
	AdjustmentScreenState::resetLowPowerIndicatorPosition(this);

	// call base
	Base::exit(this, owner);
}

void AdjustmentScreenState::init()
{
	// add rhombus effect
	VIPManager::pushBackPostProcessingEffect(VIPManager::getInstance(), AdjustmentScreenState::rhombusEmitterPostProcessingEffect, NULL);

	// set low power indicator position
	AdjustmentScreenState::setLowPowerIndicatorPosition(this);
}

void AdjustmentScreenState::suspend(void* owner)
{
	// call base
	Base::suspend(this, owner);

	// set low power indicator position
	AdjustmentScreenState::resetLowPowerIndicatorPosition(this);
}

void AdjustmentScreenState::resume(void* owner)
{
	// call base
	Base::resume(this, owner);

	AdjustmentScreenState::init(this);
}

void AdjustmentScreenState::processUserInput(UserInput userInput __attribute__ ((unused)))
{
	if(userInput.pressedKey & (K_STA | K_SEL | K_A | K_B))
	{
		if(Game::isPaused(Game::getInstance()))
		{
			Camera::startEffect(Camera::getInstance(), kFadeOut, __FADE_DELAY);
			Game::unpause(Game::getInstance(), GameState::safeCast(this));
		}
		else
		{
			SplashScreenState::loadNextState(this);
		}
	}
}

void AdjustmentScreenState::setLowPowerIndicatorPosition()
{
	LowPowerManager::setPosition(LowPowerManager::getInstance(), __ADJUSTMENT_SCREEN_LOW_POWER_INDICATOR_X_POSITION, __ADJUSTMENT_SCREEN_LOW_POWER_INDICATOR_Y_POSITION);
}

void AdjustmentScreenState::resetLowPowerIndicatorPosition()
{
	LowPowerManager::setPosition(LowPowerManager::getInstance(), __LOW_POWER_INDICATOR_X_POSITION, __LOW_POWER_INDICATOR_Y_POSITION);
}

static void AdjustmentScreenState::rhombusEmitterPostProcessingEffect(uint32 currentDrawingFrameBufferSet __attribute__ ((unused)), SpatialObject spatialObject __attribute__ ((unused)))
{
	// runtime working variables
	// negative value to achieve an initial delay
	static int32 radius = __ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE;

	// increase radius in each cycle
	radius += 2;

	if(radius < 68)
	{
		return;
	}
	else if(radius > 300)
	{
		// reset radius when reaching a certain length
		radius = __ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE;
		return;
	}

	// draw rhombus around object with given radius
	DirectDraw directDraw = DirectDraw::getInstance();

	// top left line
	DirectDraw::drawLine(
		directDraw,
		(PixelVector) {(192 - radius),	(112),			0, -((radius + __ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 - radius),	0, -((radius + __ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED
	);

	// top right line
	DirectDraw::drawLine(
		directDraw,
		(PixelVector) {(192 + radius),	(112),			0, -((radius + __ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 - radius),	0, -((radius + __ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED
	);

	// bottom right line
	DirectDraw::drawLine(
		directDraw,
		(PixelVector) {(192 + radius),	(112),			0, -((radius + __ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 + radius),	0, -((radius + __ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED
	);

	// bottom left line
	DirectDraw::drawLine(
		directDraw,
		(PixelVector) {(192 - radius),	(112),			0, -((radius + __ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		(PixelVector) {(192),			(112 + radius),	0, -((radius + __ADJUSTMENT_SCREEN_RHOMBUS_INITIAL_VALUE)>>5)},
		__COLOR_BRIGHT_RED
	);
}
