/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef AUTOMATIC_PAUSE_MANAGER_H_
#define AUTOMATIC_PAUSE_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <ListenerObject.h>
#include <GameState.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

/**
 * Shows an indicator on screen when the system power is low
 *
 * @ingroup vuengine-plugins-other
 */
singleton class AutomaticPauseManager : ListenerObject
{
	/// @protectedsection

	// auto pause state
	GameState automaticPauseState;
	// auto pause active flag
	bool isActive;
	// after this many minutes the auto pause kicks in
	uint8 autoPauseDelay;
	// minutes elapsed since last automatic pause
	uint8 elapsedTime;


	/// @publicsection

	/**
	 * Get instance.
	 *
	 * @return	AutomaticPauseManager instance
	 */
	static AutomaticPauseManager getInstance();

	GameState getAutomaticPauseState();
	void setAutomaticPauseState(GameState automaticPauseState);
	void setAutomaticPauseDelay(uint8 automaticPauseDelay);
	bool isActive();

	/**
     * De/activate
     *
     * @param active	Set as active or inactive?
     */
    void setActive(bool active);


	/// @privatesection
}


#endif
