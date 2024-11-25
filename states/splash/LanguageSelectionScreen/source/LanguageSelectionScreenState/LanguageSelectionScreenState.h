/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LANGUAGE_SELECTION_SCREEN_STATE_H_
#define LANGUAGE_SELECTION_SCREEN_STATE_H_


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <SplashScreenState.h>
#include <OptionsSelector.h>


//=========================================================================================================
// CLASS' DECLARATION
//=========================================================================================================

///
/// Class LanguageSelectionScreenState
///
/// Inherits from SplashScreenState
///
/// Implements a splash screen that allows the user to select a language.
dynamic_singleton class LanguageSelectionScreenState: SplashScreenState
{
	/// @protectedsection

	/// Entity for the selection cursor
	Entity flagCursorEntity;

	/// Selector for the language
	OptionsSelector languageSelector;

	/// Index of the selected language
	uint8 selection;

	/// With of the flags' images
	uint8 flagsTotalHalfWidth;

	/// @publicsection

	/// Method to retrieve the singleton instance
	/// @return LanguageSelectionScreenState singleton
	static LanguageSelectionScreenState getInstance();

	/// Prepares the object to enter this state.
	/// @param owner: Object that is entering in this state
	override void enter(void* owner);

	/// Process the provided user input.
	/// @param userInput: Struct with the current user input information
	override void processUserInput(const UserInput* userInput);

	/// Print any text specific to each splash screen state type.
	override void print();
}


#endif
