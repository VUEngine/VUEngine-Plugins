/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LOW_POWER_MANAGER_H_
#define LOW_POWER_MANAGER_H_

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <Clock.h>
#include <ListenerObject.h>

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS'S DECLARATION
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Shows an indicator on screen when the system power is low
singleton class LowPowerManager : ListenerObject
{
	/// @protectedsection

	/// Clock to keep track of how much passed since activation
	Clock clock;

	/// Low power indicator active flag
	bool isActive;

	/// low power indicator showing flag
	bool isShowingIndicator;
	
	/// x position of the low power indicator
	uint8 indicatorXPos;
	
	/// y position of the low power indicator
	uint8 indicatorYPos;
	
	/// number of seconds of receiving the low power signal
	uint8 lowPowerDuration;

	/// @publicsection

	/// Process an event that the instance is listen for.
	/// @param eventFirer: ListenerObject that signals the event
	/// @param eventCode: Code of the firing event
	/// @return False if the listener has to be removed; true to keep it
	override bool onEvent(ListenerObject eventFirer, uint16 eventCode);

	/// De/activate indicator.
	/// @param active	Set as active or inactive?
	void setActive(bool active);

	/// Sets the position of the low power indicator.
	/// @param x: X position (in tiles)
	/// @param y: Y position (in tiles)
	void setPosition(uint8 x, uint8 y);

	/// @privatesection

	/// Class constructor.
	/// @fn 			void LowPowerManager::constructor()
	/// @memberof 	LowPowerManager

	/// Class destructor.
	/// @fn			void LowPowerManager::destructor()
	/// @memberof 	LowPowerManager

	/// @fn			void LowPowerManager::checkLowPower()
	/// @memberof 	LowPowerManager

	/// @fn					void LowPowerManager::onSecondChange(ListenerObject eventFirer)
	/// @memberof 			LowPowerManager
	/// @param eventFirer	ListenerObject that has fired the event
}

#endif
