/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef I18N_H_
#define I18N_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <ListenerObject.h>
#include <Actor.h>
#include <Events.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' MACROS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

// Handy macros
#define __TRANSLATE(id)				I18n_getText(I18n_getInstance(), id)

// Max length of a font's name
#define __MAX_LANGUAGE_NAME_LENGTH	32

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

enum I18nEvents
{
	kEventLanguageChanged = kEventPluginsFirst + 1
};

/// A Lang Spec
/// @memberof Lang
typedef struct LangSpec
{
	/// Language's name
	char name[__MAX_LANGUAGE_NAME_LENGTH];

	/// Pointer to a representative actor (i.e. flag)
	ActorSpec* actorSpec;

	/// Language strings
	const char** language;

} LangSpec;

/// A Lang spec that is stored in ROM
/// @memberof Sprite
typedef const LangSpec LangROMSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS'S DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class I18n
///
/// Inherits from ListenerObject
///
/// Handles internationalization of text output and thus allows for multiple selectable languages.
singleton class I18n : ListenerObject
{
	/// @protectedsection

	/// Currently active language
	uint8 activeLanguage;

	/// Total amount of registerd languages
	uint8 totalLanguages;

	/// @publicsection

	/// Set the active language.
	/// @param languageId: ID of the language to make active
	void setActiveLanguage(uint8 languageId);

	/// Retrieve the index of the active language.
	/// @return Active language's index
	uint8 getActiveLanguage();

	/// Retrieve the name of the active language.
	/// @return Active language's name
	char* getActiveLanguageName();

	/// Retrieve the number of the registered language.
	/// @return Total count of registered languages
	uint8 getRegistedLanguagesCount();

	/// Get localized string
	/// @param string: The identifier of the string to localize
	/// @return Localized string or NULL if no translation could be found
	const char* getText(int32 string);

}

#endif
