/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef ALIGNMENT_CHECK_SCREEN_STATE_H_
#define ALIGNMENT_CHECK_SCREEN_STATE_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <SplashScreenState.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class AlignmentCheckScreenState
///
/// Inherits from SplashScreenState
///
/// Implements a recreation of Nintendo's official alignment check screen 
/// that can be used to check if the console's screens are out of alignment 
/// and need to be repaired.
dynamic_singleton class AlignmentCheckScreenState : SplashScreenState
{
	/// @publicsection

	/// Method to get the singleton instance
	/// @return AlignmentCheckScreenState singleton
	static AlignmentCheckScreenState getInstance();

	/// Prepares the object to enter this state.
	/// @param owner: Object that is entering in this state
	override void enter(void* owner);

	/// Process the provided user input.
	/// @param userInput: Struct with the current user input information
	override void processUserInput(const UserInput*  userInput);
}

#endif
