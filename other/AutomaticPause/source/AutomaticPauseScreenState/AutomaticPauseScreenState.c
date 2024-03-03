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

#include <string.h>

#include <Camera.h>
#include <CameraEffectManager.h>
#include <I18n.h>
#include <Languages.h>
#include <MessageDispatcher.h>
#include <Printing.h>
#include <PhysicalWorld.h>
#include <VUEngine.h>

#include "AutomaticPauseScreenState.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec AutomaticPauseScreenStage;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void AutomaticPauseScreenState::constructor()
{
	Base::constructor();
}

// class's destructor
void AutomaticPauseScreenState::destructor()
{
	// destroy base
	Base::destructor();
}

// state's enter
void AutomaticPauseScreenState::enter(void* owner __attribute__ ((unused)))
{
	// call base
	Base::enter(this, owner);

	// load stage
	GameState::loadStage(this, (StageSpec*)&AutomaticPauseScreenStage, NULL, true, false);

	// print text
	const char* strTitle = I18n::getText(I18n::getInstance(), kStringAutomaticPauseTitle);
	const char* strBody = I18n::getText(I18n::getInstance(), kStringAutomaticPauseBody);

	FontSize strAutomaticPauseSize = Printing::getTextSize(
		Printing::getInstance(),
		strTitle,
		__PLUGIN_AUTOMATIC_PAUSE_TITLE_TEXT_FONT
	);
	FontSize strAutomaticPauseTextSize = Printing::getTextSize(
		Printing::getInstance(),
		strBody,
		__PLUGIN_AUTOMATIC_PAUSE_BODY_TEXT_FONT
	);

	uint8 strHeaderXPos = ((__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseSize.x >> 1));
	Printing::text(
		Printing::getInstance(),
		strTitle,
		strHeaderXPos,
		18,
		__PLUGIN_AUTOMATIC_PAUSE_TITLE_TEXT_FONT
	);

	uint8 strTextXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseTextSize.x >> 1);
	Printing::text(
		Printing::getInstance(),
		strBody,
		strTextXPos,
		19 + strAutomaticPauseSize.y,
		__PLUGIN_AUTOMATIC_PAUSE_BODY_TEXT_FONT
	);

	// disable user input
	VUEngine::disableKeypad(VUEngine::getInstance());

	// start clocks to start animations
	GameState::startClocks(this);

	// fade in screen
	Camera::startEffect(Camera::getInstance(), kHide);
	Camera::startEffect(Camera::getInstance(),
		kFadeTo, // effect type
		0, // initial delay (in ms)
		NULL, // target brightness
		__FADE_DELAY, // delay between fading steps (in ms)
		(void (*)(ListenerObject, ListenerObject))AutomaticPauseScreenState::onFadeInComplete, // callback function
		ListenerObject::safeCast(this) // callback scope
	);
}

// state's exit
void AutomaticPauseScreenState::exit(void* owner __attribute__ ((unused)))
{
	// call base
	Base::exit(this, owner);
}

void AutomaticPauseScreenState::processUserInput(const UserInput*  userInput)
{
	if(K_STA & userInput->pressedKey)
	{
		// disable user input
		VUEngine::disableKeypad(VUEngine::getInstance());

		// fade out screen
		Brightness brightness = (Brightness){0, 0, 0};
		Camera::startEffect(Camera::getInstance(),
			kFadeTo, // effect type
			0, // initial delay (in ms)
			&brightness, // target brightness
			__FADE_DELAY, // delay between fading steps (in ms)
			(void (*)(ListenerObject, ListenerObject))AutomaticPauseScreenState::onFadeOutComplete, // callback function
			ListenerObject::safeCast(this) // callback scope
		);
	}
}

// handle event
bool AutomaticPauseScreenState::onFadeInComplete(ListenerObject eventFirer __attribute__ ((unused)))
{
	// re-enable user input
	VUEngine::enableKeypad(VUEngine::getInstance());

	return false;
}

// handle event
bool AutomaticPauseScreenState::onFadeOutComplete(ListenerObject eventFirer __attribute__ ((unused)))
{
	// re-enable user input
	VUEngine::enableKeypad(VUEngine::getInstance());

	// resume game
	VUEngine::unpause(VUEngine::getInstance(), GameState::safeCast(this));

	return false;
}
