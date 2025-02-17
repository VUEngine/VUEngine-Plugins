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

#include <VUEngine.h>

#include <AlignmentCheckScreenState.h>
#include "AlignmentCheckBaseGameState.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AlignmentCheckBaseGameState::enter(void* owner)
{
	Base::enter(this, owner);

	// Reset last button inputs
	AlignmentCheckBaseGameState::resetLastInputs(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AlignmentCheckBaseGameState::resume(void* owner)
{
	Base::resume(this, owner);

	// Reset last button inputs
	AlignmentCheckBaseGameState::resetLastInputs(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AlignmentCheckBaseGameState::processUserInput(const UserInput* userInput)
{
	if(userInput->pressedKey & ~K_PWR)
	{
		AlignmentCheckBaseGameState::recordLastInput(this, userInput);
		AlignmentCheckBaseGameState::matchButtonCode(this);
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AlignmentCheckBaseGameState::constructor()
{
	// Always explicitly call the base's constructor
	Base::constructor();

	AlignmentCheckBaseGameState::resetLastInputs(this);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AlignmentCheckBaseGameState::destructor()
{
	// Always explicitly call the base's destructor
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AlignmentCheckBaseGameState::resetLastInputs()
{
	for(uint8 i = 0; i < __PLUGIN_ALIGNMENT_CHECK_BUTTON_SEQUENCE_LENGTH; i++)
	{
		this->lastInputs[i] = 0;
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AlignmentCheckBaseGameState::recordLastInput(const UserInput* userInput)
{
	for(uint8 i = 0; i < (__PLUGIN_ALIGNMENT_CHECK_BUTTON_SEQUENCE_LENGTH - 1); i++)
	{
		this->lastInputs[i] = this->lastInputs[i + 1];
	}

	this->lastInputs[__PLUGIN_ALIGNMENT_CHECK_BUTTON_SEQUENCE_LENGTH - 1] = userInput->pressedKey;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AlignmentCheckBaseGameState::matchButtonCode()
{
	uint8 numberOfMatchingButtons = 0;

	for(uint8 i = 0; i < __PLUGIN_ALIGNMENT_CHECK_BUTTON_SEQUENCE_LENGTH; i++)
	{
		numberOfMatchingButtons += (_alignmentCheckButtonSequence[i] == this->lastInputs[i]);
	}

	if(numberOfMatchingButtons == __PLUGIN_ALIGNMENT_CHECK_BUTTON_SEQUENCE_LENGTH)
	{
		VUEngine::pause(GameState::safeCast(AlignmentCheckScreenState::getInstance()));
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
