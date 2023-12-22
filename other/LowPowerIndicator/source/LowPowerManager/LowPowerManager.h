/**
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef LOW_POWER_MANAGER_H_
#define LOW_POWER_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <ListenerObject.h>


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

/**
 * Shows an indicator on screen when the system power is low
 *
 * @ingroup vuengine-plugins-other
 */
singleton class LowPowerManager : ListenerObject
{
	/// @protectedsection

	// low power indicator active flag
	bool isActive;
	// low power indicator showing flag
	bool isShowingIndicator;
	// x position of the low power indicator
	uint8 indicatorXPos;
	// y position of the low power indicator
	uint8 indicatorYPos;
	// number of seconds of receiving the low power signal
	uint8 lowPowerDuration;


	/// @publicsection

	/**
	 * Get instance.
	 *
	 * @return	LowPowerManager instance
	 */
	static LowPowerManager getInstance();

	/**
     * De/activate indicator
     *
     * @param active	Set as active or inactive?
     */
    void setActive(bool active);

	/**
     * Sets the position of the low power indicator.
     *
     * @param x		X position (in tiles)
     * @param y		Y position (in tiles)
     */
    void setPosition(uint8 x, uint8 y);


	/// @privatesection

	/**
	 * Class constructor.
	 *
	 * @fn 			void LowPowerManager::constructor()
     * @memberof 	LowPowerManager
	 */

	/**
	 * Class destructor.
	 *
	 * @fn			void LowPowerManager::destructor()
     * @memberof 	LowPowerManager
	 */

	/**
	 *
	 *
	 * @fn			void LowPowerManager::checkLowPower()
     * @memberof 	LowPowerManager
	 */

	/**
	 *
	 *
	 * @fn					void LowPowerManager::onSecondChange(ListenerObject eventFirer)
     * @memberof 			LowPowerManager
     * @param eventFirer	ListenerObject that has fired the event
	 */
}


#endif
