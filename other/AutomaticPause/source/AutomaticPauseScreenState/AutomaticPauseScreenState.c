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

#include <string.h>

#include <Camera.h>
#include <CameraEffectManager.h>
#include <I18n.h>
#include <Languages.h>
#include <MessageDispatcher.h>
#include <Printing.h>
#include <BodyManager.h>
#include <VUEngine.h>

#include "AutomaticPauseScreenState.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

extern StageROMSpec AutomaticPauseScreenStage;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool AutomaticPauseScreenState::onEvent(ListenerObject eventFirer __attribute__((unused)), uint32 eventCode)
{
	switch(eventCode)
	{
		case kEventEffectFadeInComplete:
		{
			// Re-enable user input
			KeypadManager::enable();

			return false;
		}

		case kEventEffectFadeOutComplete:
		{
			// Re-enable user input
			KeypadManager::enable();

			// Resume game
			VUEngine::unpause(GameState::safeCast(this));

			return false;
		}
	}

	return Base::onEvent(this, eventFirer, eventCode);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseScreenState::enter(void* owner __attribute__ ((unused)))
{
	Base::enter(this, owner);

	// Load stage
	GameState::configureStage(this, (StageSpec*)&AutomaticPauseScreenStage, NULL);

	// Print text
	const char* strTitle = I18n::getText(I18n::getInstance(), kStringAutomaticPauseTitle);
	const char* strBody = I18n::getText(I18n::getInstance(), kStringAutomaticPauseBody);

	FontSize strAutomaticPauseSize = Printing::getTextSize
	(
		strTitle,
		__PLUGIN_AUTOMATIC_PAUSE_TITLE_TEXT_FONT
	);

	FontSize strAutomaticPauseTextSize = Printing::getTextSize
	(
		strBody,
		__PLUGIN_AUTOMATIC_PAUSE_BODY_TEXT_FONT
	);

	uint8 strHeaderXPos = ((__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseSize.x >> 1));
	
	Printing::text
	(
		strTitle,
		strHeaderXPos,
		18,
		__PLUGIN_AUTOMATIC_PAUSE_TITLE_TEXT_FONT
	);

	uint8 strTextXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseTextSize.x >> 1);
	
	Printing::text
	(
		strBody,
		strTextXPos,
		19 + strAutomaticPauseSize.y,
		__PLUGIN_AUTOMATIC_PAUSE_BODY_TEXT_FONT
	);

	// Disable user input
	KeypadManager::disable();

	// Start clocks to start animations
	GameState::startClocks(this);

	// Fade in screen
	Camera::startEffect(Camera::getInstance(), kHide);
	
	Camera::startEffect
	(
		Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		ListenerObject::safeCast(this) // callback scope
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseScreenState::exit(void* owner __attribute__ ((unused)))
{
	Base::exit(this, owner);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseScreenState::processUserInput(const UserInput*  userInput)
{
	if(K_STA & userInput->pressedKey)
	{
		// Disable user input
		KeypadManager::disable();

		// Fade out screen
		Brightness brightness = (Brightness){0, 0, 0};
		Camera::startEffect
		(
			Camera::getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			ListenerObject::safeCast(this) // callback scope
		);
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseScreenState::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void AutomaticPauseScreenState::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
