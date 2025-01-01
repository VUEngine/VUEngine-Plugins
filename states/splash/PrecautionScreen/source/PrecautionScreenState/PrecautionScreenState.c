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

#include <I18n.h>
#include <Languages.h>
#include <MessageDispatcher.h>
#include <SoundManager.h>
#include <Telegram.h>
#include <VUEngine.h>

#include "PrecautionScreenState.h"


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

extern StageROMSpec PrecautionScreenStage;


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

enum SplashScreenMessageTypes
{
	kMessageAllowUserInput = kMessageLastEngine + 1
};


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void PrecautionScreenState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	// play start-up sound
	extern SoundSpec PrecautionScreenIntroSoundSpec;
	SoundManager::playSound(SoundManager::getInstance(), &PrecautionScreenIntroSoundSpec, NULL, kSoundPlaybackNormal, NULL, NULL);

	// show this screen for at least 2 seconds
	// as defined by Nintendo in the official development manual (Appendix 1)
	VUEngine::disableKeypad(VUEngine::getInstance());
	MessageDispatcher::dispatchMessage(2000, ListenerObject::safeCast(this), ListenerObject::safeCast(VUEngine::getInstance()), kMessageAllowUserInput, NULL);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

bool PrecautionScreenState::processMessage(void* owner __attribute__ ((unused)), Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageAllowUserInput:
			VUEngine::enableKeypad(VUEngine::getInstance());
			break;
	}

	return false;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void PrecautionScreenState::print()
{
	const char* strBody = I18n::getText(I18n::getInstance(), kStringPrecautionScreenBody);
	FontSize textSize = Printing::getTextSize(
		Printing::getInstance(),
		strBody,
		__PLUGIN_PRECAUTION_SCREEN_TEXT_FONT
	);

	Printing::text(
		Printing::getInstance(),
		strBody,
		(__HALF_SCREEN_WIDTH_IN_CHARS) - (textSize.x >> 1),
		(__HALF_SCREEN_HEIGHT_IN_CHARS) - (textSize.y >> 1),
		__PLUGIN_PRECAUTION_SCREEN_TEXT_FONT
	);
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————


//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void PrecautionScreenState::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	this->stageSpec = (StageSpec*)&PrecautionScreenStage;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

void PrecautionScreenState::destructor()
{
	// destroy base
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————

