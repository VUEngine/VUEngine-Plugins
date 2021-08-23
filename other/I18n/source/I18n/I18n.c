/*
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

#include <string.h>
#include <I18n.h>
#include <Game.h>


//---------------------------------------------------------------------------------------------------------
//												DECLARATIONS
//---------------------------------------------------------------------------------------------------------

extern LangROMSpec* __LANGUAGES[];


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
const char* I18n::getText(int string)
{
	// TODO: check if __LANGUAGES is empty
	return 0 <= string ? __LANGUAGES[this->activeLanguage]->language[string] : NULL;
}

/**
 * Set the active language
 * @param languageId	ID of the language to make active
 */
void I18n::setActiveLanguage(u8 languageId)
{
	this->activeLanguage = languageId;

	if(Game::getCurrentState(Game::getInstance()))
	{
		GameState currentGameState = Game::getCurrentState(Game::getInstance());
		GameState::fireEvent(currentGameState, kEventLanguageChanged);
		NM_ASSERT(!isDeleted(currentGameState), "I18n::setActiveLanguage: deleted game state during kEventLanguageChanged");
	}
}

/**
 * Get all registered languages
 *
 * @return		Array of LangSpec pointers
 */
LangSpec * I18n::getLanguages()
{
	return (LangSpec *)__LANGUAGES;
}

/**
 * Retrieves ID of the currently active language
 *
 * @return		ID of currently active language
 */
u8 I18n::getActiveLanguage()
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
	// TODO: check if __LANGUAGES is empty, return "none" if so
	return (char*)__LANGUAGES[this->activeLanguage]->name;
}
