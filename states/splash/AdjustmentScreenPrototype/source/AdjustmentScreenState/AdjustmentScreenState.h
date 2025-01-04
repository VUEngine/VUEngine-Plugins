/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef ADJUSTMENT_SCREEN_STATE_H_
#define ADJUSTMENT_SCREEN_STATE_H_


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <SplashScreenState.h>


//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

///
/// Class AdjustmentScreenState
///
/// Inherits from SplashScreenState
///
/// Implements a state for adjusting the screen.
dynamic_singleton class AdjustmentScreenState : SplashScreenState
{
	/// @publicsection

	/// Method to retrieve the singleton instance
	/// @return AdjustmentScreenState singleton
	static AdjustmentScreenState getInstance(void);

	/// Prepares the object to enter this state.
	/// @param owner: Object that is entering in this state
	override void enter(void* owner);

	/// Prepares the object to exit this state.
	/// @param owner: Object that is exiting this state
	override void exit(void* owner);

	/// Prepares the object to become inactive in this state.
	/// @param owner: Object that is in this state
	override void suspend(void* owner);

	/// Prepares the object to become active in this state.
	/// @param owner: Object that is in this state
	override void resume(void* owner);

	/// Process the provided user input.
	/// @param userInput: Struct with the current user input information
	override void processUserInput(const UserInput*  userInput);
}

#endif
