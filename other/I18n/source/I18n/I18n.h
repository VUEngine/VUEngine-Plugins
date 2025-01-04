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
#include <Entity.h>
#include <Events.h>



//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' MACRO
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


// handy macros
#define __TRANSLATE(id)				I18n_getText(I18n_getInstance(), id)

// max length of a font's name
#define __MAX_LANGUAGE_NAME_LENGTH	32


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DATA
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

enum I18nEvents
{
	kEventLanguageChanged = kEventEngineLast + 1
};

/*
 * A language spec
 * @memberof I18n
 */
typedef struct LangSpec
{
	/// language name
	char name[__MAX_LANGUAGE_NAME_LENGTH];

	/// pointer to a representative entity (i.e. flag)
	EntitySpec* entitySpec;

	/// language strings
	const char** language;

} LangSpec;

/*
 * A LangSpec that is stored in ROM
 * @memberof I18n
 */
typedef const LangSpec LangROMSpec;

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS'S DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Handles internationalization of text output and thus allows for multiple selectable languages.
singleton class I18n : ListenerObject
{
	// Currently active language
	uint8 activeLanguage;
	uint8 totalLanguages;

	/// @publicsection
	static I18n getInstance();
	uint8 getActiveLanguage();
	char* getActiveLanguageName();
	uint8 getActiveLanguagesCount();
	LangSpec * getLanguages();
	const char* getText(int32 string);
	void setActiveLanguage(uint8 languageId);
}


#endif
