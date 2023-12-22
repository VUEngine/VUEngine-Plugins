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

#include <Camera.h>
#include <I18n.h>
#include <KeypadManager.h>
#include <Languages.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <SaveDataManager.h>
#include <SoundManager.h>
#include <Telegram.h>
#include <VUEngine.h>

#include "PrecautionScreenState.h"


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec PrecautionScreenStage;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

// class's constructor
void PrecautionScreenState::constructor()
{
	Base::constructor();

	this->stageSpec = (StageSpec*)&PrecautionScreenStage;
}

// class's destructor
void PrecautionScreenState::destructor()
{
	// destroy base
	Base::destructor();
}

void PrecautionScreenState::enter(void* owner)
{
	// call base
	Base::enter(this, owner);

	// play start-up sound
	extern SoundSpec PrecautionScreenIntroSoundSpec;
	SoundManager::playSound(SoundManager::getInstance(), &PrecautionScreenIntroSoundSpec, kPlayAll, NULL, kSoundPlaybackNormal, NULL, NULL);

	// show this screen for at least 2 seconds
	// as defined by Nintendo in the official development manual (Appendix 1)
	VUEngine::disableKeypad(VUEngine::getInstance());
	MessageDispatcher::dispatchMessage(2000, ListenerObject::safeCast(this), ListenerObject::safeCast(VUEngine::getInstance()), kMessageAllowUserInput, NULL);
}

// state's handle message
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

void PrecautionScreenState::print()
{
	const char* strBody = I18n::getText(I18n::getInstance(), kStringPrecautionScreenBody);
	FontSize textSize = Printing::getTextSize(
		Printing::getInstance(),
		strBody,
		__PRECAUTION_SCREEN_TEXT_FONT
	);

	Printing::text(
		Printing::getInstance(),
		strBody,
		(__HALF_SCREEN_WIDTH_IN_CHARS) - (textSize.x >> 1),
		(__HALF_SCREEN_HEIGHT_IN_CHARS) - (textSize.y >> 1),
		__PRECAUTION_SCREEN_TEXT_FONT
	);
}
