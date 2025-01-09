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

#include "AlignmentCheckScreenState.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

extern StageROMSpec AlignmentCheckScreenStage;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' ATTRIBUTES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const uint32 AlignmentCheckButtonSequence[__PLUGIN_ALIGNMENT_CHECK_BUTTON_SEQUENCE_LENGTH] =
{
	K_RL, K_B, K_RD, K_A, K_RU
};

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AlignmentCheckScreenState::enter(void* owner)
{
	Base::enter(this, owner);

	this->stream = false;
	this->transform = false;
	this->updatePhysics = false;
	this->processCollisions = false;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AlignmentCheckScreenState::processUserInput(const UserInput* userInput)
{
	// Any button quits the screen
	if(userInput->pressedKey & ~K_PWR)
	{
		if(VUEngine::isPaused())
		{
			Camera::startEffect(kFadeOut, __FADE_DELAY);
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

void AlignmentCheckScreenState::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	this->stageSpec = (StageSpec*)&AlignmentCheckScreenStage;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AlignmentCheckScreenState::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
