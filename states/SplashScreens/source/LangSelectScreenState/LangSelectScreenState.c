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

#include <Game.h>
#include <Camera.h>
#include <Printing.h>
#include <MessageDispatcher.h>
#include <LangSelectScreenState.h>
#include <Languages.h>
#include <KeypadManager.h>
#include <SoundManager.h>
#include <SaveDataManager.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMSpec LANGUAGE_SELECTION_SCREEN_STAGE_ST;
extern LangROMSpec* __LANGUAGES[];
extern EntitySpec FLAG_CURSOR_EN;
extern EntitySpec FLAG_UNKNOWN_EN;
extern const u16 SPLASH_SCREENS_OPTION_SELECT_SND[];
extern const u16 SPLASH_SCREENS_OPTION_CONFIRM_SND[];


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void LangSelectScreenState::constructor()
{
	Base::constructor();

	// init members
	this->stageSpec = (StageSpec*)&LANGUAGE_SELECTION_SCREEN_STAGE_ST;
	this->flagCursorEntity = NULL;
	this->languageSelector = NULL;
	this->selection = 0;
	this->flagsTotalHalfWidth = 0;
}

void LangSelectScreenState::destructor()
{
	if(this->languageSelector)
	{
		delete this->languageSelector;
	}

	// destroy base
	Base::destructor();
}

void LangSelectScreenState::processUserInput(UserInput userInput)
{
	if(userInput.pressedKey & (K_LU | K_RU | K_LL | K_RL))
	{
		LangSelectScreenState::select(this, false);
	}
	else if(userInput.pressedKey & (K_LD | K_RD | K_LR | K_RR))
	{
		LangSelectScreenState::select(this, true);
	}
	else if(userInput.pressedKey & (K_A | K_STA))
	{
		// play sound
		Vector3D position = {192, 112, 0};
		SoundManager::playFxSound(SoundManager::getInstance(), SPLASH_SCREENS_OPTION_CONFIRM_SND, position);

		SplashScreenState::loadNextState(SplashScreenState::safeCast(this));
	}
}

void LangSelectScreenState::enter(void* owner)
{
	Base::enter(this, owner);

	Object saveDataManager = Game::getSaveDataManager(Game::getInstance());

	// get active language from sram
	u8 activeLanguage = I18n::getActiveLanguage(I18n::getInstance());
	if(saveDataManager)
	{
		activeLanguage = SaveDataManager::getLanguage(saveDataManager);
	}
	I18n::setActiveLanguage(I18n::getInstance(), activeLanguage);
	this->selection = activeLanguage;

	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 0)

		// create options selector and populate with language names
		this->languageSelector = new OptionsSelector(1, 8, __LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);
		VirtualList languageNames = new VirtualList();
		u8 optionsWidth = 0;
		int i = 0;
		for(; __LANGUAGES[i]; i++)
		{
			Option* option = new Option;
			option->value = (char*)__LANGUAGES[i]->name;
			option->type = kString;
			VirtualList::pushBack(languageNames, option);

			FontSize strOptionSize = Printing::getTextSize(Printing::getInstance(), option->value, __LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);
			optionsWidth = (strOptionSize.x > optionsWidth) ? strOptionSize.x : optionsWidth;
		}
		OptionsSelector::setOptions(this->languageSelector, languageNames);
		delete languageNames;

		// print options
		OptionsSelector::printOptions(this->languageSelector, (__HALF_SCREEN_WIDTH_IN_CHARS) - (optionsWidth >> 1), 10);
		OptionsSelector::setSelectedOption(this->languageSelector, activeLanguage);

		LangSelectScreenState::printSelection(this);

	#endif
	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 1)

		// add flags to stage
		this->flagsTotalHalfWidth = LangSelectScreenState::getFlagsTotalHalfWidth(this);
		u8 i = 0;
		this->flagCursorEntity = LangSelectScreenState::addFlagToStage(this, &FLAG_CURSOR_EN, 0);
		for(i = 0; __LANGUAGES[i]; i++)
		{
			// add flag
			EntitySpec* entitySpec = (__LANGUAGES[i]->entitySpec != NULL)
				? __LANGUAGES[i]->entitySpec
				: &FLAG_UNKNOWN_EN;
			LangSelectScreenState::addFlagToStage(this, entitySpec, i);
		}

		LangSelectScreenState::printSelection(this);

	#endif
}

void LangSelectScreenState::print()
{
	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 0)

		// print header
		FontSize strHeaderSize = Printing::getTextSize(Printing::getInstance(), __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
		u8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strHeaderSize.x >> 1);
		u8 strHeaderYPos = 9 - strHeaderSize.y;
		Printing::text(Printing::getInstance(), "                                                ", 0, strHeaderYPos, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
		Printing::text(Printing::getInstance(), __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT, strHeaderXPos, strHeaderYPos, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);

	#endif
	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 1)

		// print header
		FontSize strHeaderSize = Printing::getTextSize(Printing::getInstance(), __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
		u8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strHeaderSize.x >> 1);
		u8 strHeaderYPos = 11 - strHeaderSize.y;
		Printing::text(Printing::getInstance(), "                                                ", 0, strHeaderYPos, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
		Printing::text(Printing::getInstance(), __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT, strHeaderXPos, strHeaderYPos, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);

		// print language
		char* strLanguageName = I18n::getActiveLanguageName(I18n::getInstance());
		FontSize strLanguageNameSize = Printing::getTextSize(Printing::getInstance(), strLanguageName, __LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);
		int strLanguageNameXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (strLanguageNameSize.x >> 1);
		int strLanguageNameYPos = ((LangSelectScreenState::getFlagYPosition(this) + __LANGUAGE_SELECTION_SCREEN_IMAGE_HEIGHT) >> 3) - 1;
		Printing::text(Printing::getInstance(), "                                                ", 0, strLanguageNameYPos, __LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);
		Printing::text(Printing::getInstance(), strLanguageName, strLanguageNameXPos, strLanguageNameYPos, __LANGUAGE_SELECTION_SCREEN_LANGUAGE_NAME_FONT);

	#endif
}

void LangSelectScreenState::printSelection()
{
	LangSelectScreenState::print(this);

	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 1)

		// set cursor position
		Vector3D position =
		{
			__PIXELS_TO_METERS(LangSelectScreenState::getFlagXPosition(this, this->selection)),
			__PIXELS_TO_METERS(LangSelectScreenState::getFlagYPosition(this)),
			0,
		};
		Entity::setLocalPosition(this->flagCursorEntity, &position);

	#endif
}

void LangSelectScreenState::select(bool next)
{
	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 0)
		if(next)
		{
			OptionsSelector::selectNext(this->languageSelector);
		}
		else
		{
			OptionsSelector::selectPrevious(this->languageSelector);
		}
		this->selection = OptionsSelector::getSelectedOption(this->languageSelector);
	#endif
	#if(__LANGUAGE_SELECTION_SCREEN_VARIANT == 1)
		u8 numLangs = LangSelectScreenState::getNumLangs(this);
		if(next)
		{
			this->selection = (this->selection < (numLangs - 1)) ? this->selection + 1 : 0;
		}
		else
		{
			this->selection = (this->selection > 0) ? this->selection - 1 : (numLangs - 1);
		}
	#endif

	LangSelectScreenState::persistChoice(this);
	LangSelectScreenState::printSelection(this);

	// play sound
	Vector3D position = {192, 112, 0};
	SoundManager::playFxSound(SoundManager::getInstance(), SPLASH_SCREENS_OPTION_SELECT_SND, position);
}

void LangSelectScreenState::persistChoice()
{
	Object saveDataManager = Game::getSaveDataManager(Game::getInstance());

	I18n::setActiveLanguage(I18n::getInstance(), this->selection);
	if(saveDataManager)
	{
		SaveDataManager::setLanguage(saveDataManager, this->selection);
	}
}

u8 LangSelectScreenState::getNumLangs()
{
	u8 i, numLangs = 0;
	for(i = 0; __LANGUAGES[i]; i++)
	{
		numLangs++;
	}

	return numLangs;
}

u8 LangSelectScreenState::getFlagsTotalHalfWidth()
{
	return ((LangSelectScreenState::getNumLangs(this) - 1) * (__LANGUAGE_SELECTION_SCREEN_IMAGE_WIDTH)) >> 1;
}

Entity LangSelectScreenState::addFlagToStage(EntitySpec* entitySpec, u8 position)
{
	PositionedEntity flagPositionedEntity = {
		entitySpec,
		{
			LangSelectScreenState::getFlagXPosition(this, position),
			LangSelectScreenState::getFlagYPosition(this),
			0,
			0,
		},
		0, NULL, NULL, NULL, false
	};

	return Stage::addChildEntity(Game::getStage(Game::getInstance()), &flagPositionedEntity, true);
}

int LangSelectScreenState::getFlagXPosition(u8 position)
{
	return 192 - this->flagsTotalHalfWidth + (position * (__LANGUAGE_SELECTION_SCREEN_IMAGE_WIDTH));
}

int LangSelectScreenState::getFlagYPosition()
{
	return 96 + ((__LANGUAGE_SELECTION_SCREEN_IMAGE_HEIGHT) >> 1);
}
