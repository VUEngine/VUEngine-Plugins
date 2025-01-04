/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef SPLASH_SCREEN_STATE_H_
#define SPLASH_SCREEN_STATE_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <GameState.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Class SplashScreenState
///
/// Inherits from GameState
///
/// Implements a simple generic base class for splash screens.
abstract class SplashScreenState : GameState
{
	/// @protectedsection

	/// State to enter after this one
	GameState nextState;

	/// spec of screen's stage
	StageSpec* stageSpec;

	/// Class' constructor
	void constructor();

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

	/// Process a Telegram sent to an object that is in this state.
	/// @param owner: Object that is in this state
	/// @param telegram: Telegram to process
	override bool processMessage(void* owner, Telegram telegram);

	/// Process the provided user input.
	/// @param userInput: Struct with the current user input information
	override void processUserInput(const UserInput*  userInput);

	/// Set the next state to load.
	/// @param nextState: Next state to load
	void setNextState(GameState nextState);

	/// Load the next state if any
	void loadNextState();

	/// Print any text specific to each splash screen state type.
	virtual void print();
}

#endif
