/* VUEngine - Virtual Utopia Engine <https://www.vuengine.dev>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>, 2007-2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
#include <PrecautionScreenState.h>
#include <AdjustmentScreenState.h>
#include <Languages.h>
#include <I18n.h>


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
	extern Sound SPLASH_SCREENS_INTRO_SND;
	Vector3D position = Vector3D::getFromPixelVector((PixelVector){192, 112, 0, 0});
	SoundManager::playSound(SoundManager::getInstance(), &SPLASH_SCREENS_INTRO_SND, kPlayAll, (const Vector3D*)&position, kSoundWrapperPlaybackNormal, NULL, NULL);

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

void PrecautionScreenState::initNextState()
{
	this->nextState = GameState::safeCast(AdjustmentScreenState::getInstance());
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
