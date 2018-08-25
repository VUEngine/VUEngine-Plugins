/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
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

#include <string.h>

#include <Game.h>
#include <Camera.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <I18n.h>
#include <AutoPauseSelectScreenState.h>
#include <LangSelectScreenState.h>
#include <Languages.h>
#include <KeyPadManager.h>
#include <AutoPauseManager.h>
#include <SaveDataManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef AUTO_PAUSE_SELECTION_SCREEN_STAGE_ST;


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

// class's constructor
void AutoPauseSelectScreenState::constructor()
{
	Base::constructor();

	this->stageDefinition = (StageDefinition*)&AUTO_PAUSE_SELECTION_SCREEN_STAGE_ST;
	this->selection = true;
}

// class's destructor
void AutoPauseSelectScreenState::destructor()
{
	// destroy base
	Base::destructor();
}

void AutoPauseSelectScreenState::initNextState()
{
	this->nextState = GameState::safeCast(LangSelectScreenState::getInstance());
}

void AutoPauseSelectScreenState::print()
{
	this->selection = SaveDataManager::getAutomaticPauseStatus(SaveDataManager::getInstance());

	const char* strAutomaticPauseTitle = __AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT;
	FontSize strAutomaticPauseSize = Printing::getTextSize(Printing::getInstance(), strAutomaticPauseTitle, __AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT_FONT);

	const char* strAutomaticPauseExplanation = __AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT;
	FontSize strAutomaticPauseExplanationSize = Printing::getTextSize(Printing::getInstance(), strAutomaticPauseExplanation, __AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT_FONT);

	u8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseSize.x >> 1);
	Printing::text(
		Printing::getInstance(),
		strAutomaticPauseTitle,
		strHeaderXPos,
		8,
		__AUTOMATIC_PAUSE_SELECTION_SCREEN_TITLE_TEXT_FONT
	);

	u8 strExplanationXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strAutomaticPauseExplanationSize.x >> 1);
	Printing::text(Printing::getInstance(), strAutomaticPauseExplanation, strExplanationXPos, 9 + strAutomaticPauseSize.y, __AUTOMATIC_PAUSE_SELECTION_SCREEN_BODY_TEXT_FONT);

	AutoPauseSelectScreenState::renderSelection(this);
}

void AutoPauseSelectScreenState::renderSelection()
{
	// get strings and determine sizes
	FontSize strOnSize = Printing::getTextSize(Printing::getInstance(), __AUTOMATIC_PAUSE_SELECTION_SCREEN_ON_TEXT, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT);
	FontSize strOffSize = Printing::getTextSize(Printing::getInstance(), __AUTOMATIC_PAUSE_SELECTION_SCREEN_OFF_TEXT, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT);
	u8 selectionStart = (48 - (strOnSize.x + __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_GAP + strOffSize.x)) >> 1;

	// clear options area
	Printing::text(Printing::getInstance(), "                                                ", 0, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS, NULL);
	Printing::text(Printing::getInstance(), "                                                ", 0, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, NULL);
	Printing::text(Printing::getInstance(), "                                                ", 0, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 2, NULL);
	if(strOnSize.y > 1) {
		Printing::text(Printing::getInstance(), "                                                ", 0, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 3, NULL);
		if(strOnSize.y > 2) {
			Printing::text(Printing::getInstance(), "                                                ", 0, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 4, NULL);
			if(strOnSize.y > 3) {
				Printing::text(Printing::getInstance(), "                                                ", 0, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 5, NULL);
			}
		}
	}

	// print options
	Printing::text(Printing::getInstance(), __AUTOMATIC_PAUSE_SELECTION_SCREEN_ON_TEXT, selectionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT);
	Printing::text(Printing::getInstance(), __AUTOMATIC_PAUSE_SELECTION_SCREEN_OFF_TEXT, selectionStart + 3 + strOnSize.x, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_TEXT_FONT);

	// print selector
	u8 optionStart = this->selection ? selectionStart : selectionStart + __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_GAP + strOnSize.x;
	u8 optionEnd = this->selection ? optionStart + strOnSize.x : optionStart + strOffSize.x;
	optionStart--;
	Printing::text(Printing::getInstance(), "\x03\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", optionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS, NULL);
	Printing::text(Printing::getInstance(), "\x04               ", optionEnd, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS, NULL);
	Printing::text(Printing::getInstance(), "\x07", optionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, NULL);
	Printing::text(Printing::getInstance(), "\x07", optionEnd, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1, NULL);
	if(strOnSize.y > 1) {
		Printing::text(Printing::getInstance(), "\x07", optionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 2, NULL);
		Printing::text(Printing::getInstance(), "\x07", optionEnd, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 2, NULL);
		if(strOnSize.y > 2) {
			Printing::text(Printing::getInstance(), "\x07", optionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 3, NULL);
			Printing::text(Printing::getInstance(), "\x07", optionEnd, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 3, NULL);
			if(strOnSize.y > 3) {
				Printing::text(Printing::getInstance(), "\x07", optionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 4, NULL);
				Printing::text(Printing::getInstance(), "\x07", optionEnd, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 4, NULL);
			}
		}
	}
	Printing::text(Printing::getInstance(), "\x05\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08", optionStart, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1 + strOnSize.y, NULL);
	Printing::text(Printing::getInstance(), "\x06               ", optionEnd, __AUTOMATIC_PAUSE_SELECTION_SCREEN_OPTIONS_Y_POS + 1 + strOnSize.y, NULL);
}

void AutoPauseSelectScreenState::processUserInput(UserInput userInput)
{
	if(userInput.pressedKey & (K_LL | K_LR))
	{
		this->selection = !this->selection;
		AutoPauseSelectScreenState::renderSelection(this);
	}
	else if(userInput.pressedKey & (K_A | K_STA))
	{
		AutoPauseManager::setActive(AutoPauseManager::getInstance(), this->selection);
		SaveDataManager::setAutomaticPauseStatus(SaveDataManager::getInstance(), this->selection);
		SplashScreenState::loadNextState(SplashScreenState::safeCast(this));
	}
}
