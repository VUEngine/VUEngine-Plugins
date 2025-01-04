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

#include <Utilities.h>
#include <VUEngine.h>

#include "I18n.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// DECLARATIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

extern LangROMSpec* _languages[];

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS'S PUBLIC METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void I18n::setActiveLanguage(uint8 languageId)
{
	if(this->totalLanguages < languageId)
	{
		return;
	}

	this->activeLanguage = languageId;

	if(VUEngine::getCurrentState(VUEngine::getInstance()))
	{
		GameState currentGameState = VUEngine::getCurrentState(VUEngine::getInstance());
		GameState::fireEvent(currentGameState, kEventLanguageChanged);
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

uint8 I18n::getActiveLanguage()
{
	return this->activeLanguage;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

char* I18n::getActiveLanguageName()
{
	// TODO: check if _languages is empty, return "none" if so
	return (char*)_languages[this->activeLanguage]->name;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

uint8 I18n::getRegistedLanguagesCount()
{
	uint8 count = 0;

	for(; NULL != _languages[count]; count++);

	return count;
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

const char* I18n::getText(int32 string)
{
	if(0 == this->totalLanguages)
	{
		return "No available languages";
	}

	if(NULL == _languages[this->activeLanguage])
	{
		return "Corrupted language";
	}

	if(NULL == _languages[this->activeLanguage]->language)
	{
		return "Empty language";
	}

	// TODO: check if _languages is empty
	return 0 <= string ? _languages[this->activeLanguage]->language[string] : "String not found";
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS'S PRIVATE METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void I18n::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	this->activeLanguage = 0;

	for(this->totalLanguages = 0; NULL != _languages[this->totalLanguages]; this->totalLanguages++);

	if(10 < this->totalLanguages)
	{
		this->totalLanguages = 0;
	}
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void I18n::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
