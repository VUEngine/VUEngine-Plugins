/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef AUTOMATIC_PAUSE_SCREEN_STATE_H_
#define AUTOMATIC_PAUSE_SCREEN_STATE_H_


//=========================================================================================================
// INCLUDES
//=========================================================================================================

#include <GameState.h>


//=========================================================================================================
// CLASS' DECLARATION
//=========================================================================================================

///
/// Class AutomaticPauseScreenState
///
/// Inherits from GameState
///
/// Implements a game state for the automatic pause feature.
singleton class AutomaticPauseScreenState : GameState
{
	/// @publicsection

	/// Method to retrieve the singleton instance
	/// @return AutomaticPauseScreenState singleton
	static AutomaticPauseScreenState getInstance();

	/// Prepares the object to enter this state.
	/// @param owner: Object that is entering in this state
	override void enter(void* owner);

	/// Prepares the object to exit this state.
	/// @param owner: Object that is exiting this state
	override void exit(void* owner);

	/// Process the provided user input.
	/// @param userInput: Struct with the current user input information
	override void processUserInput(const UserInput*  userInput);
}


#endif
