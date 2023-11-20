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

#include <I18n.h>
#include <Utilities.h>
#include <VUEngine.h>

#include <string.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern LangROMSpec* _languages[];


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

/// Get instance
/// @fn			I18n::getInstance()
/// @memberof	I18n
/// @public
/// @return		I18n instance


/**
 * Class constructor
 *
 * @private
 */
void I18n::constructor()
{
	Base::constructor();

	this->activeLanguage = 0;

	for(this->totalLanguages = 0; NULL != _languages[this->totalLanguages]; this->totalLanguages++);

	if(10 < this->totalLanguages)
	{
		this->totalLanguages = 0;
	}
}

/**
 * Class destructor
 */
void I18n::destructor()
{
	// allow a new construct
	Base::destructor();
}

/**
 * Get localized string
 *
 * @param string	The identifier of the string to localize
 * @return 			localized string or NULL if no translation could be found
 */
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

/**
 * Set the active language
 * @param languageId	ID of the language to make active
 */
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

/**
 * Get all registered languages
 *
 * @return		Array of LangSpec pointers
 */
LangSpec * I18n::getLanguages()
{
	return (LangSpec *)_languages;
}

/**
 * Retrieves ID of the currently active language
 *
 * @return		ID of currently active language
 */
uint8 I18n::getActiveLanguage()
{
	return this->activeLanguage;
}

/**
 * Retrieves name of the currently active language
 *
 * @return	Name of currently active language
 */
char* I18n::getActiveLanguageName()
{
	// TODO: check if _languages is empty, return "none" if so
	return (char*)_languages[this->activeLanguage]->name;
}

/**
 * Retrieves the number of registered languages
 *
 * @return		ID of currently active language
 */
uint8 I18n::getActiveLanguagesCount()
{
	uint8 count = 0;

	for(; NULL != _languages[count]; count++);

	return count;
}