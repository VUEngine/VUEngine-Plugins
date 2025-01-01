/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef AUTOMATIC_PAUSE_MANAGER_H_
#define AUTOMATIC_PAUSE_MANAGER_H_


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <ListenerObject.h>
#include <GameState.h>


//——————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS' DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————

///
/// Class AutomaticPauseManager
///
/// Inherits from ListenerObject
///
/// Manages the automatic pause feature.
singleton class AutomaticPauseManager : ListenerObject
{
	/// @protectedsection

	/// Auto pause state
	GameState automaticPauseState;

	/// Auto pause active flag
	bool isActive;

	/// After this many minutes the auto pause kicks in
	uint8 autoPauseDelay;

	/// Minutes elapsed since last automatic pause
	uint8 elapsedTime;

	/// @publicsection

	/// Method to retrieve the singleton instance
	/// @return AutomaticPauseManager singleton
	static AutomaticPauseManager getInstance();

	/// Set the state that the game must transition to when pausing it.
	/// @param automaticPauseState: State that the game must transition to when pausing it
	void setAutomaticPauseState(GameState automaticPauseState);
	
	/// Retrieve the state that the game transitions to when pausing it.
	/// @return State that the game transitions to when pausing it
	GameState getAutomaticPauseState();

	/// Set the deplay before pausing the game.
	/// @param automaticPauseDelay: Amount of time that must elapse before pausing the game
	void setAutomaticPauseDelay(uint8 automaticPauseDelay);

	/// Activate/deactivate the automatic pause feature.
	/// @param active: If true, the game will pause automatically after the
	/// configured elapsed time
    void setActive(bool active);

	/// Retrieve the activation state for the automatic pause feature.
	/// @return True if the the automatic pause feature is enabled; false otherwise
	bool isActive();
}


#endif
