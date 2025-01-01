/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef AUTOMATIC_PAUSE_SELECTION_SCREEN_STATE_H_
#define AUTOMATIC_PAUSE_SELECTION_SCREEN_STATE_H_


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <SplashScreenState.h>


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

///
/// Class AutomaticPauseSelectionScreenState
///
/// Inherits from SplashScreenState
///
/// Implements a splash screen that allows the user to turn Automatic Pause on or off.
dynamic_singleton class AutomaticPauseSelectionScreenState: SplashScreenState
{
	/// @protectedsection

	/// Status of the automatic pause feature
	bool selection;

	/// @publicsection

	/// Method to retrieve the singleton instance
	/// @return AdjustmentScreenState singleton
	static AutomaticPauseSelectionScreenState getInstance();

	/// Process the provided user input.
	/// @param userInput: Struct with the current user input information
	override void processUserInput(const UserInput* userInput);

	/// Print any text specific to each splash screen state type.
	override void print();
}

#endif
