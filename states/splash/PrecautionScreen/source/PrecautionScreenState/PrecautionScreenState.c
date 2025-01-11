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

#include <I18n.h>
#include <Languages.h>
#include <MessageDispatcher.h>
#include <SoundManager.h>
#include <Telegram.h>
#include <VUEngine.h>

#include "PrecautionScreenState.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

extern StageROMSpec PrecautionScreenStage;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

enum SplashScreenMessageTypes
{
	kMessageAllowUserInput = kMessageLastEngine + 1
};

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PrecautionScreenState::enter(void* owner)
{
	Base::enter(this, owner);

	// Play start-up sound
	extern SoundSpec PrecautionScreenIntroSoundSpec;
	SoundManager::playSound(&PrecautionScreenIntroSoundSpec, NULL, kSoundPlaybackNormal, NULL, NULL);

	// Show this screen for at least 2 seconds
	// As defined by Nintendo in the official development manual (Appendix 1)
	VUEngine::disableKeypad();
	VUEngine::receieveMessage(2000, ListenerObject::safeCast(this), kMessageAllowUserInput, NULL);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

bool PrecautionScreenState::processMessage(void* owner __attribute__ ((unused)), Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageAllowUserInput:
			VUEngine::enableKeypad();
			break;
	}

	return false;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PrecautionScreenState::print()
{
	const char* strBody = I18n::getText(I18n::getInstance(NULL), kStringPrecautionScreenBody);
	FontSize textSize = Printing::getTextSize
	(
		
		strBody,
		__PLUGIN_PRECAUTION_SCREEN_TEXT_FONT
	);

	Printing::text
	(
		
		strBody,
		(__HALF_SCREEN_WIDTH_IN_CHARS) - (textSize.x >> 1),
		(__HALF_SCREEN_HEIGHT_IN_CHARS) - (textSize.y >> 1),
		__PLUGIN_PRECAUTION_SCREEN_TEXT_FONT
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PrecautionScreenState::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	this->stageSpec = (StageSpec*)&PrecautionScreenStage;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void PrecautionScreenState::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
