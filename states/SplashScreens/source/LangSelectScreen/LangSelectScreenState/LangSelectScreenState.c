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
#include <I18n.h>
#include <LangSelectScreenState.h>
#include <Languages.h>
#include <KeyPadManager.h>
#ifdef __SAVE_DATA_MANAGER_ENABLED
#include <SaveDataManager.h>
#endif
#include <SplashScreensConfig.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern StageROMDef LANGUAGE_SELECTION_SCREEN_STAGE_ST;
extern LangROMDef* __LANGUAGES[];


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void LangSelectScreenState::constructor()
{
	Base::constructor();

	// init members
	this->stageDefinition = (StageDefinition*)&LANGUAGE_SELECTION_SCREEN_STAGE_ST;
	this->languageSelector = NULL;
}

void LangSelectScreenState::destructor()
{
	delete this->languageSelector;

	// destroy base
	Base::destructor();
}

void LangSelectScreenState::processUserInput(UserInput userInput)
{
	if(userInput.pressedKey & (K_LU | K_RU))
	{
		OptionsSelector::selectPrevious(this->languageSelector);
	}
	else if(userInput.pressedKey & (K_LD | K_RD))
	{
		OptionsSelector::selectNext(this->languageSelector);
	}
	else if(userInput.pressedKey & (K_A | K_STA))
	{
		int selectedLanguage = OptionsSelector::getSelectedOption(this->languageSelector);
		I18n::setActiveLanguage(I18n::getInstance(), selectedLanguage);
		#ifdef __SAVE_DATA_MANAGER_ENABLED
		SaveDataManager::setLanguage(SaveDataManager::getInstance(), selectedLanguage);
		#endif
		SplashScreenState::loadNextState(SplashScreenState::safeCast(this));
	}
}

void LangSelectScreenState::print()
{
	// create options selector and populate with language names
	this->languageSelector = new OptionsSelector(1, 8, __LANGUAGE_SELECTION_SCREEN_OPTIONS_FONT);
	VirtualList languageNames = new VirtualList();
	u8 activeLanguage = I18n::getActiveLanguage(I18n::getInstance());
	int i = 0;
	for(; __LANGUAGES[i]; i++)
	{
		I18n::setActiveLanguage(I18n::getInstance(), i);

		Option* option = new Option;
		option->value = (char*)I18n::getActiveLanguageName(I18n::getInstance());
		option->type = kString;
		VirtualList::pushBack(languageNames, option);
	}
	OptionsSelector::setOptions(this->languageSelector, languageNames);
	delete languageNames;

	// get active language from sram
	#ifdef __SAVE_DATA_MANAGER_ENABLED
	activeLanguage = SaveDataManager::getLanguage(SaveDataManager::getInstance());
	#endif
	I18n::setActiveLanguage(I18n::getInstance(), activeLanguage);

	// print header
	FontSize size = Printing::getTextSize(Printing::getInstance(), __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT, __LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT);
	u8 strHeaderXPos = (__HALF_SCREEN_WIDTH_IN_CHARS) - (size.x >> 1);
	Printing::text(
		Printing::getInstance(),
		__LANGUAGE_SELECTION_SCREEN_TITLE_TEXT,
		strHeaderXPos,
		8,
		__LANGUAGE_SELECTION_SCREEN_TITLE_TEXT_FONT
	);

	// print options
	OptionsSelector::printOptions(this->languageSelector, strHeaderXPos, 9 + size.y);
	OptionsSelector::setSelectedOption(this->languageSelector, activeLanguage);
}

