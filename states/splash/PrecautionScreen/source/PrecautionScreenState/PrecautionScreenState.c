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
#include <Printing.h>
#include <MessageDispatcher.h>
#include <KeypadManager.h>
#include <SoundManager.h>
#include <I18n.h>
#include <Languages.h>
#include <PrecautionScreenState.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec PRECAUTION_SCREEN_STAGE;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DEFINITION
//---------------------------------------------------------------------------------------------------------

// class's constructor
void PrecautionScreenState::constructor()
{
	Base::constructor();

	this->stageSpec = (StageSpec*)&PRECAUTION_SCREEN_STAGE;
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
	extern Sound PRECAUTION_SCREEN_INTRO_SND;
	Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
	SoundManager::playSound(SoundManager::getInstance(), &PRECAUTION_SCREEN_INTRO_SND, kPlayAll, (const Vector3D*)&position, kSoundWrapperPlaybackNormal, NULL, NULL);

	// show this screen for at least 2 seconds
	// as defined by Nintendo in the official development manual (Appendix 1)
	MessageDispatcher::dispatchMessage(2000, Object::safeCast(this), Object::safeCast(Game::getInstance()), kMessageAllowUserInput, NULL);
}

// state's handle message
bool PrecautionScreenState::processMessage(void* owner __attribute__ ((unused)), Telegram telegram)
{
	switch(Telegram::getMessage(telegram))
	{
		case kMessageAllowUserInput:
			Game::enableKeypad(Game::getInstance());
			break;
	}

	return false;
}

void PrecautionScreenState::print()
{
	FontSize textSize = Printing::getTextSize(
		Printing::getInstance(),
		__PRECAUTION_SCREEN_TEXT,
		__PRECAUTION_SCREEN_TEXT_FONT
	);

	Printing::text(
		Printing::getInstance(),
		__PRECAUTION_SCREEN_TEXT,
		(__HALF_SCREEN_WIDTH_IN_CHARS) - (textSize.x >> 1),
		(__HALF_SCREEN_HEIGHT_IN_CHARS) - (textSize.y >> 1),
		__PRECAUTION_SCREEN_TEXT_FONT
	);
}